/** \file teclado.H 

    Ficheiro de interface do módulo teclados.  Define a classe Slang::Teclado
    e outras classes associadas. 

    \todo Tentar escrever pelo menos testes elementares para as ferramentas
    deste módulo.

    \ingroup teclados */
#ifndef SLANG_TECLADO_H
#define SLANG_TECLADO_H

namespace Slang {

    /** \defgroup teclados Ferramentas de teclado

	Módulo correspondente ao ficheiro Slang++/teclado.H. Contém ferramentas
	para lidar com o teclado. */

    /** \class Tecla teclado.H Slang++/teclado.H

	Representa teclas premidas.  As teclas podem corresponder a caracteres
        (e.g., 'a', 'x', '1', '.') ou a teclas de controlo (e.g., 'delete',
        'home', etc.). Nem todas as teclas são reconhecidas: depende da forma
        como o S-Lang lida com cada terminal.

	\ingroup teclados */
    class Tecla {
    public:

        /** Representa as várias teclas que podem ser premidas.  Não são
            enumerados explicitamente os caracteres normais, mas os seus
            valores podem ser representados neste tipo enumerado.  O par de
            tipos Tecla::TeclaEnum e Tecla permite usar uma classe como se de
            um tipo enumerado se tratasse.  Há conversões implícitas entre os
            dois tipos.  Além disso a classe proporciona algumas operações
            úteis. */
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
            pagina_anterior = 0x105, ///< Passar à página anterior.
            pagina_seguinte = 0x106, ///< Passar à página seguinte.
            casa = 0x107,	///< Voltar a casa.
            fim = 0x108,	///< Ir para o fim.
            a1 = 0x109,
            a3 = 0x10A,
            b2 = 0x10B,
            c1 = 0x10C,
            c3 = 0x10D,
            refaz = 0x10E,	///< Refazer (só em alguns teclados).
            desfaz = 0x10F,	///< Desfazer (só em alguns teclados).
            apaga_para_tras = 0x110, ///< Apaga para trás.
            entrada = 0xD,	///< Dar entrada.
            // entrada = 0x111, enter?  Não funcionou!
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

        /** Constrói nova tecla a partir do valor enumerado correspondente.  
	    Define conversão implícita a partir de Tecla::TeclaEnum). 

	    \pre V.

	    \post TeclaEnum(*this) = tecla. */
        Tecla(TeclaEnum tecla);

	//@}

        ///@name Conversores
        //@{

        /** Devolve a conversão da tecla no valor enumerado correspondente.  
	    Define conversão implícita para Tecla::TeclaEnum.

	    \pre V.

	    \post TeclaEnum = valor do enumerado correspondente à tecla. */
        operator TeclaEnum () const;

        /** Devolve conversão da tecla para char.

	    \pre eChar().

	    \post comoChar = caractere correspondente à tecla representada. */
        char comoChar() const;

	//@}

        ///@name Predicados
        //@{

        /** Indica se a tecla é de deslocamento (i.e., seta para a esquerda,
	    direita, cima ou baixo). 

	    \pre V.

	    \post eDeDeslocamento = tecla representada é seta de
	    deslocamento. */
        bool eDeDeslocamento() const;

        /** Indica se a tecla for é um caractere.

	    \pre V.
	    \post eChar = tecla representada é um caractere. */
        bool eChar() const;

	//@}

    private:
        TeclaEnum tecla;
    };

    /** \class Teclado teclado.H Slang++/teclado.H

	Representa o teclado.  Esta classe é um solitão, pois admite-se não
	haver senão um teclado.

	A classe Teclado permite obter informação acerca da pressão de teclas.
	Para isso usa-se a operação teclaLida(), que devolve uma instância
	da classe Tecla.  Esta função não deve ser utilizada sem que haja uma
	tecla lida (i.e., sem que antes se tenha recorrido à operação
	leProximaTeclaDisponivel()).

	A operação leProximaTeclaDisponivel() lê a próxima tecla disponível,
	i.e., a primeira das teclas premidas que ainda não foram lidas.  Só
	deve ser utilizada se houver uma tecla disponível para leitura, a não
	ser que se pretenda que o programa páre a execução enquanto espera que
	o utilizador pressione uma tecla.

	Para verificar se o utilizador pressionou numa tecla, existe o
	predicado haTeclaDisponivel().  Este predicado tem como argumento o
	número de décimos de segundo que se deve esperar pela pressão de uma
	tecla.  Se o predicado for usado num ciclo, não se deve usar o valor
	zero como argumento, pois pode tornar o sistema muito lento (10
	décimos de segundo é um valor aceitável para o argumento desta função
	nessas circunstâncias).

	A operação descartaTeclasDisponiveis() permite descartar as teclas que
	foram pressionadas pelo utilizador anteriormente e ainda não foram
	lidas e passar a considerar apenas as teclas que forem pressionadas a
	partir desse instante.

	É definida uma variável global chamada #teclado da classe Teclado, de
	modo que não é necessário, nem permitido, criar nenhuma variável deste
	tipo nos programas que fazem uso desta biblioteca, podendo-se utilizar
	directamente a variável #teclado (como acontece no caso do canal
	#cin).

	Uma instância da classe Tecla pode ser uma tecla especial (definidas
	no enumerado Tecla::TeclaEnum) ou um caractere normal. É possível
	verificar se o valor armazenado numa instância da classe Tecla é um
	deslocamento ou um caracter normal através dos predicados
	Tecla::eDeslocamento() e Tecla::eChar().

	\b Exemplo

	O programa que se segue captura todas as teclas premidas até
	ser premido o caracter 's'.  Se forem deslocamentos, procede
	ao deslocamento respectivo do cursor.  Se forem caracteres,
	escreve-os no ecrã.  Se a tecla pressionada corresponder a um
	caractere que não se pode imprimir no ecrã, é mostrada uma
	mensagem adequada.  Se for outra tecla aparece outra mensagem
	apropriada.

	\include teclado1.C

	\ingroup teclados */
    class Teclado {
    public:

        ///@name Construtores
        //@{

	/** Constrói um novo teclado.  Encarrega-se de inicializar o "keyboard
	    interface" do S-Lang.

	    \pre Não pode haver mais nenhum teclado definido. */
        Teclado();

	/** Destrói o teclado.  Encarrega-se de re-iniciar o "keyboard
	    interface" do S-Lang, que volta ao estado em que estava antes de o
	    teclado ter sido construído.

	    \pre V. */
        ~Teclado();

	//@}

        ///@name Inspectores
        //@{

        /** Devolve a última tecla lida.

	    \pre V.

	    \post teclaLida() = última tecla lida ou Tecla::nula, caso ainda
	    não tenha sido lida nenhuma tecla. */
        Tecla teclaLida() const;

	//@}

        ///@name Predicados
        //@{

        /** Indica se alguma tecla está disponível para leitura.  Desiste ao
	    fim do tempo passado como argumento (em décimos de segundo).

	    \pre 0 <= decimos_de_segundo. 

	    \post haTeclaDisponivel = está disponível uma tecla para
	    leitura. */
        bool haTeclaDisponivel(int decimos_de_segundo = 0) const;

	//@}

        ///@name Modificadores
        //@{

        /** Lê a primeira das teclas premidas e ainda não lidas.  Se nenhuma
	    tecla tiver sido premida, espera que tal aconteça.

	    \pre V.

	    \post teclaLida() = tecla lida pela operação. */
        void leProximaTeclaDisponivel();

        /** Descarta todas as teclas premidas e ainda não lidas.  Não afecta a
	    última tecla lida.

	    \pre V.

	    \post nao haTeclaDisponivel(). */
        void descartaTeclasDisponiveis();

	//@}

    private:
	Tecla tecla_lida;
        static bool existe_instancia;
    };

    /** \relates Teclado

         Representa o teclado.  Substitui a variável global #cin usada
	 normalmente para ler do teclado. 

	\ingroup teclados  */
    extern Teclado teclado;
}

#include "teclado_impl.H"

#endif // SLANG_TECLADO_H
