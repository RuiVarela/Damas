/** \file mensageiro.H 
    
    Ficheiro de interface do módulo mensageiros. Define a classe
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

        Módulo correspondente ao ficheiro IPC++/mensageiro.H. Contém
        ferramentas para comunicar entre processos via mensageiros. */

    /** \class Erro mensageiro.H IPC++/mensageiro.H

        Representa as excepções da biblioteca IPC++.

	\ingroup mensageiros */
    class Erro : public Erros::Erro {
    public:
        /** Constrói um erro guardando a mensagem de erro recebida como
            parâmetro. */
	Erro(std::string const& mensagem);

	/** Constrói excepção usando mensagem de erro padrão correspondente ao
	    último erro IPC ocorrido. */
	Erro();

    private:
	std::string mensagem;
    };

    /** \class Mensageiro mensageiro.H IPC++/mensageiro.H 

	Classe cuja única instância (em cada processo) representa um
        mensageiro entre o processo em causa e um outro na mesma máquina.
        Esta classe é um solitão!  A ideia é que um processo com uma instância
        desta classe fica em comunicação com outro com outra instância da
        mesma classe.  A selecção do outro processo é feita automaticamente,
        de acordo com as disponibilidades.  A ideia é permitir a comunicação
        entre dois processos do mesmo jogo, sendo que os jogadores não têm
        controlo sobre que será o seu opositor. 

        Nas descrições usa-se o termo "eu" para indicar o processo corrente, e
        "outro" para indicar o processo a que o "eu" está emparelhado pelo
        mensageiro.
        
        A comunicação faz-se enviando e recebendo mensagens.  As mensagens
        enviadas e recebidas são de qualquer tipo para o qual:
	-# estejam definido os operadores << e >> para ostream e istream,
	respectivamente; 
	-# tenham definido um construtor por omissão; e
	-# tenham definido um cnstrutor por cópia.

        Não existe, para já, nenhuma forma de indagar se há alguma mensagem
        disponível para ser recebida e muito menos saber o seu tipo.  O
        protocolo entre os processos é que tem de garantir que os processos
        recebem tantas mensagens quantas as enviadas pelo outro, enviam tantas
        mensagens quantas as recebidas pelo outro, e que as mensagens enviadas
        e recebidas têm tipos compatíveis.

        A classe é simples de usar.  Por exemplo, suponha que se pretendia
        fazer um pequeno jogo em que ganha quem gerar um número aleatório
        maior.  Poder-se-ia escrever o seguinte programa:

	\include mensageiro1.C

	\invariant meu_PID = int(getpid()) e meu_UID = int(getuid()) e
	PID_do_outro = PID do "outro" e UID_do_outro = UID do "outro" e
	0 <= identificador_da_caixa_do_correio e 0 <=
	identificador_do_semaforo.

	\ingroup mensageiros */
    class Mensageiro {
    public:
        /** Contrói um novo mensageiro.  Podem-se criar mensageiros de dois
            tipos: restritos ou não restritos.  O primeiro tipo consegue-se
            não passando qualquer argumento ao construtor e restringe o
            emparelhamento dos processos a processos do mesmo utilizador.  O
            segundo tipo é mais geral, pois permite o emparelhamento de
            processos de utilizadores arbitrários da mesma máquina, mas exige
            a passagem de uma chave ipc que deve ser única para cada tipo de
            aplicação prevista (por uma questão de compatibilidade de
            protocolos de comunicação). 

	    \pre V.

	    \post O mensageiro está construído e ligado a um mensageiro de
	    outro processo. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
        Mensageiro(key_t const chave = getuid());

        /** Destrói o mensageiro, destruindo a caixa do correio criada se for
	    o último mensageiro em existência.

	    \pre V. */
        ~Mensageiro();

        /** Devolve um identificador único para o processo, que consiste no
            nome do utilizador seguido do número do processo. 

	    \pre V.

	    \post meuIdentificador = "UN + (PID)", onde UN é o nome do
	    utilizador e PID é o número do processo. */
        std::string meuIdentificador() const;

        /** Devolve o identificador único do outro processo, com o qual o
            corrente está emparelhado através do mensageiro. 
	
	    \pre O processo do "outro" tem de existir.

	    \post identificadorDoOutro = "UN + (PID)", onde UN é o nome do
	    utilizador do "outro" e PID é o número do processo do "outro". */
        std::string identificadorDoOutro() const;

	/** Lê uma nova mensagem vinda do "outro".  Espera pela mensagem a ler
	    se não estiver nenhuma mensagem disponível. 
	    
	    \pre V.

	    \post Há uma mensagem lida. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	void leMensagem();

	/** Devolve a mensagem lida na forma de um valor do tipo \a Tipo.  É
	    um erro se o tipo indicado não corresponder ao tipo do valor
	    enviado pelo "outro".

	    \pre Há uma mensagem lida.

	    \post mensagemLida = mensagem enviada pelo "outro".

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos ou no caso de o tipo especificado ser incompatível
	    com a mensagem lida. */ 
	template <typename Tipo>
	Tipo const mensagemLida() const;

	/** Envia uma mensagem correspondente a um valor do tipo Tipo (versão
	    para variáveis).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Tipo>
	void envia(Tipo& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo Tipo (versão
	    para constantes e valores temporários).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Tipo>
	void envia(Tipo const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    clássica de caracteres (versão para ponteiros simples).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Char>
	void envia(Char*& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    clássica de caracteres (versão para ponteiros para caracteres
	    constantes).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Char>
	void envia(Char const*& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    clássica de caracteres (versão para ponteiros constantes).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Char>
	void envia(Char* const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    clássica de caracteres (versão para ponteiros constantes para
	    caracteres constantes).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
	    entre processos. */
	template <typename Char>
	void envia(Char const* const& mensagem) const;

	/** Envia uma mensagem correspondente a um valor do tipo cadeia
	    clássica de caracteres (versão para matrizes de caracteres).

	    \pre V.

	    \post Está disponível para o "outro" uma nova mensagem. 

	    \exception IPC::Erro no caso de haver erro na API de comunicação
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

	// Assim ninguém pode invocar o construtor por cópia...
	Mensageiro(Mensageiro const&);

	// ...nem a atribuição por cópia:
	Mensageiro& operator =(Mensageiro const&);

	// Lê uma mensagem consistindo num inteiro, sem verificação do tipo e
	// com ou sem espera, consoante o valor do argumento.  É uma rotina
	// dois em um, mas é usada apenas internamente.  O tipo é o tipo usado
	// para discriminar entre filas de espera da caixa do correio.
	int leBasicoInt(int const tipo, bool const deve_esperar = true) const;

	// Lê uma mensagem nua (i.e., lê uma cadeia de caracteres
	// directamente, sem interpretação), com ou sem espera, consoante o
	// valor do argumento.  É uma rotina dois em um, mas é usada apenas
	// internamente.  O tipo é o tipo usado para discriminar entre filas
	// de espera da caixa do correio.
        std::string leBasico(int const tipo, 
			     bool const deve_esperar = true) const;

	// Escreve uma mensagem consistindo simplemente num inteiro, sem
	// indicação do tipo.  O tipo é o tipo usado para discriminar entre
	// filas de espera da caixa do correio.
        void escreveBasicoInt(int const tipo, int const valor);

	// Escreve uma mensagem nua.  O tipo é o tipo usado para discriminar
	// entre filas de espera da caixa do correio.
        void escreveBasico(int const tipo, std::string const& mensagem) const;

	// Estabelece uma nova nova caixa do correio (ou liga-se a uma caixa
	// do correio existente).  Usa a chave IPC dada.
	void estabeleceCaixaDoCorreio(key_t const chave);

	// Remove a caixa do correio.
	void removeCaixaDoCorreio();

	// Estabelece o semáforo de acesso à caixa do correio (ou liga-se um
	// semáforo já existente).  Usa a chave IPC dada.
	void estabeleceSemaforoDeAcesso(key_t const chave);

	// Inicia um período de acesso exclusivo à caixa do correio.  Útil
	// durante o protocolo de início de conversação entre os mensageiros.
	void entraEmAcessoExclusivo() const;

	// Termina um período de acesso exclusivo à caixa do correio.  Útil
	// durante o protocolo de início de conversação entre os mensageiros.
	void saiDeAcessoExclusivo() const;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = meu_PID = int(getpid()) e meu_UID =
	    int(getuid()) e 0 <= identificador_da_caixa_do_correio e 0 <=
	    identificador_do_semaforo. */
	bool cumpreInvariante() const;
    };
}

#include <IPC++/mensageiro_impl.H>

#endif //IPC_MENSAGEIRO_H
