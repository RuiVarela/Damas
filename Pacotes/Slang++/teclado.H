/** \file teclado.H 

    Ficheiro de interface do m�dulo teclados.  Define a classe Slang::Teclado
    e outras classes associadas. 

    \todo Tentar escrever pelo menos testes elementares para as ferramentas
    deste m�dulo.

    \ingroup teclados */
#ifndef SLANG_TECLADO_H
#define SLANG_TECLADO_H

namespace Slang {

    /** \defgroup teclados Ferramentas de teclado

	M�dulo correspondente ao ficheiro Slang++/teclado.H. Cont�m ferramentas
	para lidar com o teclado. */

    /** \class Tecla teclado.H Slang++/teclado.H

	Representa teclas premidas.  As teclas podem corresponder a caracteres
        (e.g., 'a', 'x', '1', '.') ou a teclas de controlo (e.g., 'delete',
        'home', etc.). Nem todas as teclas s�o reconhecidas: depende da forma
        como o S-Lang lida com cada terminal.

	\ingroup teclados */
    class Tecla {
    public:

        /** Representa as v�rias teclas que podem ser premidas.  N�o s�o
            enumerados explicitamente os caracteres normais, mas os seus
            valores podem ser representados neste tipo enumerado.  O par de
            tipos Tecla::TeclaEnum e Tecla permite usar uma classe como se de
            um tipo enumerado se tratasse.  H� convers�es impl�citas entre os
            dois tipos.  Al�m disso a classe proporciona algumas opera��es
            �teis. */
        enum TeclaEnum {
            nula = 0,		///< Caractere nulo.
	    ctrl_a = 1,         ///< 'ctrl-a'.
	    ctrl_b = 2,         ///< 'ctrl-b'. 
	    ctrl_c = 3,         ///< 'ctrl-c'. 
	    ctrl_d = 4,         ///< 'ctrl-d'. 
	    ctrl_e = 5,         ///< 'ctrl-e'. 
	    ctrl_f = 6,         ///< 'ctrl-f'. 
	    ctrl_g = 7,         ///< 'ctrl-g'. 
	    ctrl_h = 8,         ///< 'ctrl-h'. 
	    ctrl_i = 9,         ///< 'ctrl-i'. 
	    ctrl_j = 10,         ///< 'ctrl-j'.
	    ctrl_k = 11,         ///< 'ctrl-k'.
	    ctrl_l = 12,         ///< 'ctrl-l'.
	    ctrl_m = 13,         ///< 'ctrl-m'.
	    ctrl_n = 14,         ///< 'ctrl-n'.
	    ctrl_o = 15,         ///< 'ctrl-o'.
	    ctrl_p = 16,         ///< 'ctrl-p'.
	    ctrl_q = 17,         ///< 'ctrl-q'.
	    ctrl_r = 18,         ///< 'ctrl-r'.
	    ctrl_s = 19,         ///< 'ctrl-s'.
	    ctrl_t = 20,         ///< 'ctrl-t'.
	    ctrl_u = 21,         ///< 'ctrl-u'.
	    ctrl_v = 22,         ///< 'ctrl-v'.
	    ctrl_w = 23,         ///< 'ctrl-w'.
	    ctrl_x = 24,         ///< 'ctrl-x'.
	    ctrl_y = 25,         ///< 'ctrl-y'.
	    ctrl_z = 26,         ///< 'ctrl-z'.
            refresca = 12,	///< Refrescar ('ctrl-l').
            cima = 0x101,	///< Ir para cima.
            baixo = 0x102,	///< Ir para baixo.
            esquerda = 0x103,	///< Ir para a esquerda.
            direita = 0x104,	///< Ir para a direita.
            pagina_anterior = 0x105, ///< Passar � p�gina anterior.
            pagina_seguinte = 0x106, ///< Passar � p�gina seguinte.
            casa = 0x107,	///< Voltar a casa.
            fim = 0x108,	///< Ir para o fim.
            a1 = 0x109,
            a3 = 0x10A,
            b2 = 0x10B,
            c1 = 0x10C,
            c3 = 0x10D,
            refaz = 0x10E,	///< Refazer (s� em alguns teclados).
            desfaz = 0x10F,	///< Desfazer (s� em alguns teclados).
            apaga_para_tras = 0x110, ///< Apaga para tr�s.
            entrada = 0xD,	///< Dar entrada.
            // entrada = 0x111, enter?  N�o funcionou!
            insere = 0x112,	///< Inserir.
            apaga = 0x113,	///< Apagar.
            F0 = 0x200,
            F1 = 0x201,		///< 'F1'.
            F2 = 0x202,		///< 'F2'.
            F3 = 0x203,		///< 'F3'.
            F4 = 0x204,		///< 'F4'.
            F5 = 0x205,		///< 'F5'.
            F6 = 0x206,		///< 'F6'.
            F7 = 0x207,		///< 'F7'.
            F8 = 0x208,		///< 'F8'.
            F9 = 0x209,		///< 'F9'.
            F10 = 0x20A,	///< 'F10'.
            F11 = 0x20B,	///< 'F11'.
            F12 = 0x20C,	///< 'F12'.
            erro = 0xFFFF	///< Valor em caso de erro.
        };

        ///@name Construtores
        //@{

        /** Constr�i nova tecla a partir do valor enumerado correspondente.  
	    Define convers�o impl�cita a partir de Tecla::TeclaEnum). 

	    \pre V.

	    \post TeclaEnum(*this) = tecla. */
        Tecla(TeclaEnum tecla);

	//@}

        ///@name Conversores
        //@{

        /** Devolve a convers�o da tecla no valor enumerado correspondente.  
	    Define convers�o impl�cita para Tecla::TeclaEnum.

	    \pre V.

	    \post TeclaEnum = valor do enumerado correspondente � tecla. */
        operator TeclaEnum () const;

        /** Devolve convers�o da tecla para char.

	    \pre eChar().

	    \post comoChar = caractere correspondente � tecla representada. */
        char comoChar() const;

	//@}

        ///@name Predicados
        //@{

        /** Indica se a tecla � de deslocamento (i.e., seta para a esquerda,
	    direita, cima ou baixo). 

	    \pre V.

	    \post eDeDeslocamento = tecla representada � seta de
	    deslocamento. */
        bool eDeDeslocamento() const;

        /** Indica se a tecla for � um caractere.

	    \pre V.
	    \post eChar = tecla representada � um caractere. */
        bool eChar() const;

	//@}

    private:
        TeclaEnum tecla;
    };

    /** \class Teclado teclado.H Slang++/teclado.H

	Representa o teclado.  Esta classe � um solit�o, pois admite-se n�o
	haver sen�o um teclado.

	A classe Teclado permite obter informa��o acerca da press�o de teclas.
	Para isso usa-se a opera��o teclaLida(), que devolve uma inst�ncia
	da classe Tecla.  Esta fun��o n�o deve ser utilizada sem que haja uma
	tecla lida (i.e., sem que antes se tenha recorrido � opera��o
	leProximaTeclaDisponivel()).

	A opera��o leProximaTeclaDisponivel() l� a pr�xima tecla dispon�vel,
	i.e., a primeira das teclas premidas que ainda n�o foram lidas.  S�
	deve ser utilizada se houver uma tecla dispon�vel para leitura, a n�o
	ser que se pretenda que o programa p�re a execu��o enquanto espera que
	o utilizador pressione uma tecla.

	Para verificar se o utilizador pressionou numa tecla, existe o
	predicado haTeclaDisponivel().  Este predicado tem como argumento o
	n�mero de d�cimos de segundo que se deve esperar pela press�o de uma
	tecla.  Se o predicado for usado num ciclo, n�o se deve usar o valor
	zero como argumento, pois pode tornar o sistema muito lento (10
	d�cimos de segundo � um valor aceit�vel para o argumento desta fun��o
	nessas circunst�ncias).

	A opera��o descartaTeclasDisponiveis() permite descartar as teclas que
	foram pressionadas pelo utilizador anteriormente e ainda n�o foram
	lidas e passar a considerar apenas as teclas que forem pressionadas a
	partir desse instante.

	� definida uma vari�vel global chamada #teclado da classe Teclado, de
	modo que n�o � necess�rio, nem permitido, criar nenhuma vari�vel deste
	tipo nos programas que fazem uso desta biblioteca, podendo-se utilizar
	directamente a vari�vel #teclado (como acontece no caso do canal
	#cin).

	Uma inst�ncia da classe Tecla pode ser uma tecla especial (definidas
	no enumerado Tecla::TeclaEnum) ou um caractere normal. � poss�vel
	verificar se o valor armazenado numa inst�ncia da classe Tecla � um
	deslocamento ou um caracter normal atrav�s dos predicados
	Tecla::eDeslocamento() e Tecla::eChar().

	\b Exemplo

	O programa que se segue captura todas as teclas premidas at�
	ser premido o caracter 's'.  Se forem deslocamentos, procede
	ao deslocamento respectivo do cursor.  Se forem caracteres,
	escreve-os no ecr�.  Se a tecla pressionada corresponder a um
	caractere que n�o se pode imprimir no ecr�, � mostrada uma
	mensagem adequada.  Se for outra tecla aparece outra mensagem
	apropriada.

	\include teclado1.C

	\ingroup teclados */
    class Teclado {
    public:

        ///@name Construtores
        //@{

	/** Constr�i um novo teclado.  Encarrega-se de inicializar o "keyboard
	    interface" do S-Lang.

	    \pre N�o pode haver mais nenhum teclado definido. */
        Teclado();

	/** Destr�i o teclado.  Encarrega-se de re-iniciar o "keyboard
	    interface" do S-Lang, que volta ao estado em que estava antes de o
	    teclado ter sido constru�do.

	    \pre V. */
        ~Teclado();

	//@}

        ///@name Inspectores
        //@{

        /** Devolve a �ltima tecla lida.

	    \pre V.

	    \post teclaLida() = �ltima tecla lida ou Tecla::nula, caso ainda
	    n�o tenha sido lida nenhuma tecla. */
        Tecla teclaLida() const;

	//@}

        ///@name Predicados
        //@{

        /** Indica se alguma tecla est� dispon�vel para leitura.  Desiste ao
	    fim do tempo passado como argumento (em d�cimos de segundo).

	    \pre 0 <= decimos_de_segundo. 

	    \post haTeclaDisponivel = est� dispon�vel uma tecla para
	    leitura. */
        bool haTeclaDisponivel(int decimos_de_segundo = 0) const;

	//@}

        ///@name Modificadores
        //@{

        /** L� a primeira das teclas premidas e ainda n�o lidas.  Se nenhuma
	    tecla tiver sido premida, espera que tal aconte�a.

	    \pre V.

	    \post teclaLida() = tecla lida pela opera��o. */
        void leProximaTeclaDisponivel();

        /** Descarta todas as teclas premidas e ainda n�o lidas.  N�o afecta a
	    �ltima tecla lida.

	    \pre V.

	    \post nao haTeclaDisponivel(). */
        void descartaTeclasDisponiveis();

	//@}

    private:
	Tecla tecla_lida;
        static bool existe_instancia;
    };

    /** \relates Teclado

         Representa o teclado.  Substitui a vari�vel global #cin usada
	 normalmente para ler do teclado. 

	\ingroup teclados  */
    extern Teclado teclado;
}

#include "teclado_impl.H"

#endif // SLANG_TECLADO_H
