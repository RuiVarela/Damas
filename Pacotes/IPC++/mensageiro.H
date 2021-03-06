/** \file mensageiro.H 
    
    Ficheiro de interface do m�dulo mensageiros. Define a classe
    IPC::Mensageiro.

    \ingroup mensageiros */
#ifndef IPC_MENSAGEIRO_H
#define IPC_MENSAGEIRO_H

#include <string>

#include <Erros/erros.H>
#include <Utilitarios/cadeia.H>

extern "C" {
    #include <sys/msg.h>
    #include <sys/sem.h>
    #include <unistd.h>
    #include <pwd.h>
}

namespace IPC {

    /** \defgroup mensageiros Mensageiros entre processos

        M�dulo correspondente ao ficheiro IPC++/mensageiro.H. Cont�m
        ferramentas para comunicar entre processos via mensageiros. */

    /** \class Erro mensageiro.H IPC++/mensageiro.H

        Representa as excep��es da biblioteca IPC++.

	\ingroup mensageiros */
    class Erro : public Erros::Erro {
    public:
        /** Constr�i um erro guardando a mensagem de erro recebida como
            par�metro. */
	Erro(std::string const& mensagem);

	/** Constr�i excep��o usando mensagem de erro padr�o correspondente ao
	    �ltimo erro IPC ocorrido. */
	Erro();

    private:
	std::string mensagem;
    };

    /** \class Mensageiro mensageiro.H IPC++/mensageiro.H 

	Classe cuja �nica inst�ncia (em cada processo) representa um
        mensageiro entre o processo em causa e um outro na mesma m�quina.
        Esta classe � um solit�o!  A ideia � que um processo com uma inst�ncia
        desta classe fica em comunica��o com outro com outra inst�ncia da
        mesma classe.  A selec��o do outro processo � feita automaticamente,
        de acordo com as disponibilidades.  A ideia � permitir a comunica��o
        entre dois processos do mesmo jogo, sendo que os jogadores n�o t�m
        controlo sobre que ser� o seu opositor. 

        Nas descri��es usa-se o termo "eu" para indicar o processo corrente, e
        "outro" para indicar o processo a que o "eu" est� emparelhado pelo
        mensageiro.
        
        A comunica��o faz-se enviando e recebendo mensagens.  As mensagens
        enviadas e recebidas s�o de qualquer tipo para o qual:
	-# estejam definido os operadores << e >> para ostream e istream,
	respectivamente; 
	-# tenham definido um construtor por omiss�o; e
	-# tenham definido um cnstrutor por c�pia.

        N�o existe, para j�, nenhuma forma de indagar se h� alguma mensagem
        dispon�vel para ser recebida e muito menos saber o seu tipo.  O
        protocolo entre os processos � que tem de garantir que os processos
        recebem tantas mensagens quantas as enviadas pelo outro, enviam tantas
        mensagens quantas as recebidas pelo outro, e que as mensagens enviadas
        e recebidas t�m tipos compat�veis.

        A classe � simples de usar.  Por exemplo, suponha que se pretendia
        fazer um pequeno jogo em que ganha quem gerar um n�mero aleat�rio
        maior.  Poder-se-ia escrever o seguinte programa:

	\include mensageiro1.C

	\invariant meu_PID = int(getpid()) e meu_UID = int(getuid()) e
	PID_do_outro = PID do "outro" e UID_do_outro = UID do "outro" e
	0 <= identificador_da_caixa_do_correio e 0 <=
	identificador_do_semaforo.

	\ingroup mensageiros */
    class Mensageiro {
    public:
        /** Contr�i um novo mensageiro.  Podem-se criar mensageiros de dois
            tipos: restritos ou n�o restritos.  O primeiro tipo consegue-se
            n�o passando qualquer argumento ao construtor e restringe o
            emparelhamento dos processos a processos do mesmo utilizador.  O
            segundo tipo � mais geral, pois permite o emparelhamento de
            processos de utilizadores arbitr�rios da mesma m�quina, mas exige
            a passagem de uma chave ipc que deve ser �nica para cada tipo de
            aplica��o prevista (por uma quest�o de compatibilidade de
            protocolos de comunica��o). 

	    \pre V.

	    \post O mensageiro est� constru�do e ligado a um mensageiro de
	    outro processo. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
        Mensageiro(key_t const chave = getuid());

        /** Destr�i o mensageiro, destruindo a caixa do correio criada se for
	    o �ltimo mensageiro em exist�ncia.

	    \pre V. */
        ~Mensageiro();

        /** Devolve um identificador �nico para o processo, que consiste no
            nome do utilizador seguido do n�mero do processo. 

	    \pre V.

	    \post meuIdentificador = "UN + (PID)", onde UN � o nome do
	    utilizador e PID � o n�mero do processo. */
        std::string meuIdentificador() const;

        /** Devolve o identificador �nico do outro processo, com o qual o
            corrente est� emparelhado atrav�s do mensageiro. 
	
	    \pre O processo do "outro" tem de existir.

	    \post identificadorDoOutro = "UN + (PID)", onde UN � o nome do
	    utilizador do "outro" e PID � o n�mero do processo do "outro". */
        std::string identificadorDoOutro() const;

	/** L� uma nova mensagem vinda do "outro".  Espera pela mensagem a ler
	    se n�o estiver nenhuma mensagem dispon�vel. 
	    
	    \pre V.

	    \post H� uma mensagem lida. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	void leMensagem();

	/** Devolve a mensagem lida na forma de um valor do tipo \a Tipo.  �
	    um erro se o tipo indicado n�o corresponder ao tipo do valor
	    enviado pelo "outro".

	    \pre H� uma mensagem lida.

	    \post mensagemLida = mensagem enviada pelo "outro".

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos ou no caso de o tipo especificado ser incompat�vel
	    com a mensagem lida. */ 
	template <typename Tipo>
	Tipo const mensagemLida() const;

	/** Envia uma mensagem correspondente a um valor do tipo Tipo (vers�o
	    para vari�veis).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Tipo>
	void envia(Tipo& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo Tipo (vers�o
	    para constantes e valores tempor�rios).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Tipo>
	void envia(Tipo const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    cl�ssica de caracteres (vers�o para ponteiros simples).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Char>
	void envia(Char*& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    cl�ssica de caracteres (vers�o para ponteiros para caracteres
	    constantes).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Char>
	void envia(Char const*& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    cl�ssica de caracteres (vers�o para ponteiros constantes).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Char>
	void envia(Char* const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    cl�ssica de caracteres (vers�o para ponteiros constantes para
	    caracteres constantes).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Char>
	void envia(Char const* const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    cl�ssica de caracteres (vers�o para matrizes de caracteres).

	    \pre V.

	    \post Est� dispon�vel para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunica��o
	    entre processos. */
	template <typename Char, int dimensao>
	inline void envia(Char const (& mensagem)[dimensao]) const;

    private:
	std::string tipo_dos_dados;
	std::string mensagem;
        int meu_PID;
        int PID_do_outro;
        int meu_UID;
        int UID_do_outro;
        int identificador_da_caixa_do_correio;
        int identificador_do_semaforo;
        bool sou_um_servidor;
	static bool existe_instancia;

	// Assim ningu�m pode invocar o construtor por c�pia...
	Mensageiro(Mensageiro const&);

	// ...nem a atribui��o por c�pia:
	Mensageiro& operator =(Mensageiro const&);

	// L� uma mensagem consistindo num inteiro, sem verifica��o do tipo e
	// com ou sem espera, consoante o valor do argumento.  � uma rotina
	// dois em um, mas � usada apenas internamente.  O tipo � o tipo usado
	// para discriminar entre filas de espera da caixa do correio.
	int leBasicoInt(int const tipo, bool const deve_esperar = true) const;

	// L� uma mensagem nua (i.e., l� uma cadeia de caracteres
	// directamente, sem interpreta��o), com ou sem espera, consoante o
	// valor do argumento.  � uma rotina dois em um, mas � usada apenas
	// internamente.  O tipo � o tipo usado para discriminar entre filas
	// de espera da caixa do correio.
        std::string leBasico(int const tipo, 
			     bool const deve_esperar = true) const;

	// Escreve uma mensagem consistindo simplemente num inteiro, sem
	// indica��o do tipo.  O tipo � o tipo usado para discriminar entre
	// filas de espera da caixa do correio.
        void escreveBasicoInt(int const tipo, int const valor);

	// Escreve uma mensagem nua.  O tipo � o tipo usado para discriminar
	// entre filas de espera da caixa do correio.
        void escreveBasico(int const tipo, std::string const& mensagem) const;

	// Estabelece uma nova nova caixa do correio (ou liga-se a uma caixa
	// do correio existente).  Usa a chave IPC dada.
	void estabeleceCaixaDoCorreio(key_t const chave);

	// Remove a caixa do correio.
	void removeCaixaDoCorreio();

	// Estabelece o sem�foro de acesso � caixa do correio (ou liga-se um
	// sem�foro j� existente).  Usa a chave IPC dada.
	void estabeleceSemaforoDeAcesso(key_t const chave);

	// Inicia um per�odo de acesso exclusivo � caixa do correio.  �til
	// durante o protocolo de in�cio de conversa��o entre os mensageiros.
	void entraEmAcessoExclusivo() const;

	// Termina um per�odo de acesso exclusivo � caixa do correio.  �til
	// durante o protocolo de in�cio de conversa��o entre os mensageiros.
	void saiDeAcessoExclusivo() const;

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = meu_PID = int(getpid()) e meu_UID =
	    int(getuid()) e 0 <= identificador_da_caixa_do_correio e 0 <=
	    identificador_do_semaforo. */
	bool cumpreInvariante() const;
    };
}

#include <IPC++/mensageiro_impl.H>

#endif //IPC_MENSAGEIRO_H
