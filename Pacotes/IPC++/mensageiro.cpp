/** \file mensageiro.C

    Ficheiro de implementa��o do m�dulo mensageiros. Define classes
    que permitem comunicar entre processos de uma forma simples.

    \ingroup mensageiros */
#include <cassert>

#include <IPC++/mensageiro.H>

IPC::Mensageiro::Mensageiro(key_t const chave)
{
    assert(not existe_instancia);

    existe_instancia = true;

    // Obten��o de PID do processo corrente e do UID do utilizador.
    meu_PID = int(getpid());
    meu_UID = int(getuid());

    estabeleceSemaforoDeAcesso(chave);

    entraEmAcessoExclusivo();

    estabeleceCaixaDoCorreio(chave);

    try {
	
	/* Tenta ler PID de um servidor do canal 1, que � o canal onde
	   os servidores se registam.  Se a leitura falhar, n�o existe
	   servidor registado, pelo que o corrente processo se
	   assumir� como servidor. Note-se que esta utiliza��o de
	   excep��es como substitutos de instru��es de selec��o n�o �
	   boa ideia em geral. */
	PID_do_outro = leBasicoInt(1, false);

	saiDeAcessoExclusivo();
	
	/* Encontrou registo de vervidor.  Nesse caso �
	   cliente. */
	sou_um_servidor = false;

	// Depois escreve o seu PID no canal do servidor */
	escreveBasicoInt(PID_do_outro, meu_PID);
	
    } catch(Erro) {
	
	/* N�o encontrou registo de servidor.  Nesse caso �
	   servidor e espera por um cliente. */
	sou_um_servidor = true;
	
	/* O servidor regista a exist�ncia de actividade
	   escrevendo uma mensagem irrelevante no canal 2, que
	   � usado pelos servidores para saberem se a caixa do
	   correio deve ser eliminada quando eles terminam a
	   execu��o. */
	escreveBasicoInt(2, 0);
	
	/* O servidor escreve o seu PID no canal 1. */
	escreveBasicoInt(1, meu_PID);
	
	saiDeAcessoExclusivo();

	/* Depois fica � espera do PID do cliente mas j� no
	   seu pr�prio canal. */
	PID_do_outro = leBasicoInt(meu_PID);
    }

    // Envia o UID ao "outro".
    escreveBasicoInt(PID_do_outro, meu_UID);

    // Recebe o UID do "outro".
    UID_do_outro = leBasicoInt(meu_PID);
}

IPC::Mensageiro::~Mensageiro() 
{
    try {
	if(sou_um_servidor) {

	    /* Se � servidor espera por fim do cliente antes de
	       terminar em paz. */
	    std::string mensagem;
	    while((mensagem = leBasico(meu_PID)) != "TeRmInEi")
		;
		
	    entraEmAcessoExclusivo();

	    /* Servidor elimina um marcador de exist�ncia de
	       actividade. */
	    leBasicoInt(2);

	    /* Se n�o h� nenhum marcador de exist�ncia de actividade,
	       remove a caixa do correio e o respectivo sem�foro. Ver mais
	       acima nota acerca de blocos de tentativa para substituir
	       instru��es de selec��o. */
	    try {
		leBasicoInt(2, false);
		escreveBasicoInt(2, 0);
	    } catch(Erro) {
		removeCaixaDoCorreio();
	    }

		saiDeAcessoExclusivo();
	} else {
	    // Clientes avisam servidores que v�o terminar.
	    escreveBasico(PID_do_outro, "TeRmInEi");
	}
    } catch(Erro) {
	/* Se houve erro, ignorar...  Excep��es em destrutores s�o
	   m� ideia.  Deixar uma caixa do correio criada n�o
	   incomoda muito... */
    }
}

std::string IPC::Mensageiro::leBasico(int const tipo, 
				      bool const deve_esperar) const
{
    typedef std::string::size_type Tamanho;

    int tipo_de_leitura = deve_esperar ? 0 : IPC_NOWAIT;

    // Receber tamanho da mensagem:
    msgbuf *mensagem_ipc = 
	static_cast<msgbuf*>(malloc(sizeof(long) + sizeof(Tamanho)));

    if(msgrcv(identificador_da_caixa_do_correio, 
	      mensagem_ipc, sizeof(Tamanho), tipo, tipo_de_leitura) == -1)
	throw Erro();

    Tamanho tamanho;
    memcpy(static_cast<void*>(&tamanho), 
	   static_cast<void*>(mensagem_ipc->mtext),
	   sizeof(Tamanho));

    free(mensagem_ipc);

    // Receber memsagem:
    mensagem_ipc = 
	static_cast<msgbuf*>(malloc(sizeof(long) + tamanho + 1));

    if(msgrcv(identificador_da_caixa_do_correio, 
	      mensagem_ipc, tamanho + 1, tipo, tipo_de_leitura) == -1)
	throw Erro();

    std::string mensagem = mensagem_ipc->mtext;

    free(mensagem_ipc);

    return mensagem;
}

void IPC::Mensageiro::escreveBasico(int const tipo, 
				    std::string const& mensagem) const
{
    typedef std::string::size_type Tamanho;

    // Enviar tamanho da mensagem:
    msgbuf *mensagem_ipc = 
	static_cast<msgbuf*>(malloc(sizeof(long) + sizeof(Tamanho)));

    mensagem_ipc->mtype = tipo;
    Tamanho tamanho = mensagem.size();
    memcpy(static_cast<void*>(mensagem_ipc->mtext),
	   static_cast<void*>(&tamanho), sizeof(Tamanho));

    if(msgsnd(identificador_da_caixa_do_correio, 
	      mensagem_ipc, sizeof(Tamanho), IPC_NOWAIT) == -1)
	throw Erro();

    free(mensagem_ipc);

    // Enviar memsagem:
    mensagem_ipc = 
	static_cast<msgbuf*>(malloc(sizeof(long) + tamanho + 1));

    mensagem_ipc->mtype = tipo;
    strcpy(mensagem_ipc->mtext, mensagem.c_str());

    if(msgsnd(identificador_da_caixa_do_correio, 
	      mensagem_ipc, tamanho + 1, IPC_NOWAIT) == -1)
	throw Erro();

    free(mensagem_ipc);
}

void IPC::Mensageiro::estabeleceSemaforoDeAcesso(key_t const chave)
{
#if defined(__GNU_LIBRARY__) and not defined(_SEM_SEMUN_UNDEFINED)
    // A uni�o semun � definida pela inclus�o de <sys/sem.h>
#else
    // Caso contr�rio tem de se definir a uni�o explicitamente:
    union semun {
	int val;                    /* value for SETVAL */
	struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
	unsigned short int *array;  /* array for GETALL, SETALL */
	struct seminfo *__buf;      /* buffer for IPC_INFO */
    };
#endif
    
    int permissoes = (chave == key_t(getuid()))? 0660 : 0666;

    // Cria��o de sem�foro de acesso � caixa do correio/obten��o de
    // identificador de sem�foro de acesso � caixa do correio existente:
    identificador_do_semaforo = 
	semget(chave, 1, IPC_CREAT | IPC_EXCL | permissoes);
    if(identificador_do_semaforo == -1)
	if(errno == EEXIST) {
	    identificador_do_semaforo = semget(chave, 1, 0);
	    if(identificador_do_semaforo == -1)
		throw Erro();
	} else
	    throw Erro();
    else {
	semun ctl_arg;
	ctl_arg.val = 1;
	
	if(semctl(identificador_do_semaforo, 0, SETVAL, ctl_arg) == -1)
	    throw Erro();
    }
}

bool IPC::Mensageiro::existe_instancia = false;


#ifdef TESTE

#include <iostream>

extern "C" {
#include <unistd.h>
}

using namespace std;
using namespace IPC;

int main() 
{
    fork();

    try {
	Mensageiro mensageiro;
	
	mensageiro.envia("ol�");

	mensageiro.envia(string("ol�t"));

	string s1 = "ol�";
	mensageiro.envia(s1);
	
	string const s2 = "ol�";
	mensageiro.envia(s2);

	char* s3 = "ol�";
	mensageiro.envia(s3);
	
	char const* s4 = "ol�1";
	mensageiro.envia(s4);
	
	char* const s5 = "ol�2";
	mensageiro.envia(s5);
	
	char const* const s6 = "ol�3";
	mensageiro.envia(s6);

	mensageiro.envia(1.0);
	
	double x1 = 2.0;
	mensageiro.envia(x1);

	double const x2 = 3.0;
	mensageiro.envia(x2);

	mensageiro.envia(1);
	
	int i1 = 2;
	mensageiro.envia(i1);

	int const i2 = 3;
	mensageiro.envia(i2);

	mensageiro.envia('a');

	char c1 = 'b';
	mensageiro.envia(c1);

	char const c2 = 'c';
	mensageiro.envia(c2);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�t");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�1");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�2");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<string>() == "ol�3");

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<double>() == 1.0);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<double>() == 2.0);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<double>() == 3.0);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<int>() == 1);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<int>() == 2);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<int>() == 3);

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<char>() == 'a');

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<char>() == 'b');

	mensageiro.leMensagem();
	assert(mensageiro.mensagemLida<char>() == 'c');
    } catch(IPC::Erro& erro) {
	cerr << string(erro) << endl;
	assert(false);
    }
}

#endif // TESTE
