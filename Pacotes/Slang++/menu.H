/** \file menu.H 

    Ficheiro de interface do m�dulo menus. Define classes que permitem usar
    menus.

    \ingroup menus */
#ifndef SLANG_MENU_H
#define SLANG_MENU_H

#include <vector>
#include <string>

#include <Slang++/ecra.H>

namespace Slang {

    /** \defgroup menus Ferramentas de menus
	M�dulo correspondente ao ficheiro Slang++/menu.H. Cont�m ferramentas
	para criar e executar v�rios tipos de menus e caixas de di�logo
	simples. 

	Os v�rios tipos de menus s�o exemplificados no programa abaixo:

	\include exemplo2.C */

    /** \class ApendiceComCor menu.H Slang++/menu.H

	Define ferramentas relacionadas com cores para os menus que as
	possuirem. 
        
        S�o definidas cores para a borda, o t�tulo, os itens e o item corrente 
        do menu.  As cores usadas s�o (por omiss�o):
        
        -# borda: preto sobre branco (ou cinzento).
        -# t�tulo: vermelho sobre branco (ou cinzento).
        -# itens: preto sobre branco (ou cinzento).
        -# item corrente: amarelo sobre azul.

        Um ap�ndice serve para equipar outras classes de ferramentas mais ou
        menos avulsas.  Estas classes s�o conhecidas tamb�m por
        <em>mixin</em>.

	\invariant V.

	\ingroup menus */
    class ApendiceComCor {
    protected:
        ///@name Construtores
        //@{

        /** Constr�i um novo ap�ndice com cor, atribuindo cores por omiss�o.
	    
            \pre V. 

	    \post objectoCorDaBorda().corDoTexto() = preto e
	    objectoCorDaBorda().corDoFundo() = branco e
	    objectoCorDoTitulo().corDoTexto() = vermelho e 
	    objectoCorDoTitulo().corDoFundo() = branco e
	    objectoCorDosItens().corDoTexto() = preto e 
	    objectoCorDosItens().corDoFundo() = branco e 
	    objectoCorDoItemCorrente().corDoTexto() = amarelo e 
	    objectoCorDoItemCorrente().corDoFundo() = azul. */
        ApendiceComCor();

        /** Destr�i um ap�ndice com cor.

	    \pre V. */
        ~ApendiceComCor();

	//@}
        
        ///@name Inspectores
        //@{

        /** Devolve o objecto cor da borda.
	    
	    \pre V.

	    \post objectoCorDaBorda � o objecto cor usado para representar a
	    borda do menu. */
        Ecra::ObjectoCor const& objectoCorDaBorda() const;

        /** Devolve o objecto cor do t�tulo.
	    
	    \pre V.

	    \post objectoCorDoTitulo � o objecto cor usado para representar o
	    t�tulo do menu. */
        Ecra::ObjectoCor const& objectoCorDoTitulo() const;

        /** Devolve o objecto cor dos itens.
	    
	    \pre V.

	    \post objectoCorDosItens � o objecto cor usado para representar os
	    itens do menu. */
        Ecra::ObjectoCor const& objectoCorDosItens() const;

        /** Devolve o objecto cor do item corrente.
	    
	    \pre V.

	    \post objectoCorDoItemCorrente � o objecto cor usado para
	    representar o item corrente do menu. */
        Ecra::ObjectoCor const& objectoCorDoItemCorrente() const;

        //@}

        ///@name Modificadores
        //@{

        /** Devolve o objecto cor da borda.
	    
	    \pre V.

	    \post objectoCorDaBorda � o objecto cor usado para representar a
	    borda do menu. */
        Ecra::ObjectoCor& objectoCorDaBorda();

        /** Devolve o objecto cor do t�tulo.
	    
	    \pre V.

	    \post objectoCorDoTitulo � o objecto cor usado para representar o
	    t�tulo do menu. */
        Ecra::ObjectoCor& objectoCorDoTitulo();

        /** Devolve o objecto cor dos itens.
	    
	    \pre V.

	    \post objectoCorDosItens � o objecto cor usado para representar os
	    itens do menu. */
        Ecra::ObjectoCor& objectoCorDosItens();

        /** Devolve o objecto cor do item corrente.
	    
	    \pre V.

	    \post objectoCorDoItemCorrente � o objecto cor usado para
	    representar o item corrente do menu. */
        Ecra::ObjectoCor& objectoCorDoItemCorrente();

        //@}

    private:
        Ecra::ObjectoCor objecto_cor_da_borda;
        Ecra::ObjectoCor objecto_cor_do_titulo;
        Ecra::ObjectoCor objecto_cor_dos_itens;
        Ecra::ObjectoCor objecto_cor_do_item_corrente;

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;
    };

    /** \class Menu menu.H Slang++/menu.H

        Classe abstracta que representa a interface b�sica de todos os menus. 

	\invariant titulo <> "" e eImprimivel(titulo)..

	\ingroup menus */
    class Menu {
    public:
        ///@name Construtores
        //@{

        /** Constr�i um novo menu com o t�tulo dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit Menu(std::string const& titulo);

        /** Destrutor abstracto marca uma classe abstracta.

	\pre V. */
        virtual ~Menu() = 0;

	//@}

        ///@name Inspectores
        //@{

        /** Devolve o t�tulo do menu.

	    \pre V.

	    \post titulo = t�tulo do menu. */
        std::string titulo() const;

	/** Devolve a op��o actual do menu (o primeiro item do menu tem n�mero
            0).
	
	    \pre V.
	    
	    \post opcaoActual = op��o actual do menu. */
        virtual int opcaoActual() const = 0;

	//@}

        ///@name Interac��o com o utilizador
        //@{

        /** Executa o menu, i.e., interage com o utilizador do programa.

	    \pre V.

	    \post opcaoActual() � a �ltima op��o escolhida pelo utilizador. */
        virtual void interage() = 0;

	//@}

    private:
        std::string titulo_;

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = (titulo <> "" e eImprimivel(titulo)). */
	bool cumpreInvariante() const;
    };

    /** \class MenuComCor menu.H Slang++/menu.H

	Classe abstracta que define a interface b�sica de todos os menus com
	cores.  A parte das cores � herdada do ap�ndice ApendiceComCor. 

	\ingroup menus */
    class MenuComCor: public Menu, protected ApendiceComCor {
    public:
        ///@name Construtores
        //@{

        /** Constr�i um novo menu com o t�tulo dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuComCor(std::string const& titulo);

        /** Destrutor abstracto marca uma classe abstracta.

	\pre V. */
	virtual ~MenuComCor() = 0;

	//@}
    };

    /** \class MenuSimples menu.H Slang++/menu.H
	Representa menus simples, que consistem numa sequ�ncia de itens.

        O programa abaixo mostra um menu simples no ecr� e escreve a op��o que
        for pressionada at� ser seleccionada a op��o "Basar":

        \include menu1.C 

	O mesmo exemplo poderia ser escrito com mais simplicidade se n�o se
	precisasse de acedar �s op��es do menu individualmente:

	\include menu2.C

	\invariant 1 <= numero_de_itens e itens.size() == numero_de_itens e (Q
	j : 0 <= j < numero_de_itens : eImprimivel(itens[j])) e
	comprimento_maximo_dos_itens = max((M j: 0 <= j < numero_de_itens :
	itens[j].size()), titulo().length() e 0 <= opcao_corrente <
	numero_de_itens.

	\ingroup menus */
    class MenuSimples : public MenuComCor {
    public:
        ///@name Construtores
        //@{

        /** Constr�i um menu simples com o t�tulo dado e com os itens cujo
            texto � dado na forma de uma matriz cl�ssica de cadeias de
            caracteres.

	    \pre titulo <> "" e eImprimivel(titulo) e
	    1 <= numero_de_itens e itens tem numero_de_itens elementos  e 
	    (Q j : 0 <= j < numero_de_itens : eImprimivel(itens[j])).

	    \post titulo() = titulo. */
        MenuSimples(std::string const& titulo, 
                    std::string const itens[], 
                    int const numero_de_itens);

        /** Constr�i um menu simples com o t�tulo dado e com os itens cujo
            texto � dado na forma de uma cadeia de caracteres onde os itens
            s�o terminados por '\\n'.

	    \pre titulo <> "" e eImprimivel(titulo) e itens tem pelo menos um
	    item e os itens em itens s�o todos imprim�veis.

	    \post titulo() = titulo. */
        MenuSimples(std::string const& titulo, 
                    std::string const& itens);

	//@}

        ///@name Inspectores
        //@{

	/** Devolve a op��o actual do menu (o primeiro item do menu tem n�mero
            0).
	
	    \pre V.
	    
	    \post opcaoActual = op��o actual do menu, i.e, a �ltima op��o
	    escolhida pelo utilizador. */
        virtual int opcaoActual() const;

	//@}

        ///@name Interface com o utilizador
        //@{

        /** Executa o menu, i.e., interage com o utilizador do programa.

	    \pre V.

	    \post opcaoActual() � a �ltima op��o escolhida pelo utilizador. */
        virtual void interage();

	//@}

    private:
        std::vector<std::string> itens;
        int numero_de_itens;
        std::string::size_type comprimento_maximo_dos_itens;
        Posicao posicao;
        Dimensao dimensao;
        int opcao_corrente;

	// Calcula dimens�o do menu:
        void calculaDimensao();

	// Calcula posicao do menu:
        void calculaPosicao();

	// Desenha o item com o n�mero dado:
        void desenhaItem(int numero_do_item) const;

	// Desenha o menu completo:
        void desenha() const;

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = (1 <= numero_de_itens e itens.size() =
	    numero_de_itens e (Q j : 0 <= j < numero_de_itens :
	    eImprimivel(itens[j])) e comprimento_maximo_dos_itens = max((M j:
	    0 <= j < numero_de_itens : itens[j].size()), titulo().length()) e
	    0 <= opcao_corrente < numero_de_itens). */
	bool cumpreInvariante() const;
    };

    /** \class MenuDeCores menu.H Slang++/menu.H

	Representa menus de selec��o das cores b�sicas us�veis no ecr�. 

	\ingroup menus */
    class MenuDeCores : public MenuSimples {
    public:
        ///@name Construtores
        //@{

        /** Constr�i um novo menu de cores com o t�tulo dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuDeCores(std::string const& titulo);

	//@}
    };

    /** \class MenuDeSimOuNao menu.H Slang++/menu.H

        Representa menus com apenas duas op��es: sim e n�o. 

	\ingroup menus */
    class MenuDeSimOuNao : private MenuSimples {
    public:
        ///@name Construtores
        //@{

        /** Constr�i um novo menu sim/n�o com o t�tulo dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuDeSimOuNao(std::string const& titulo);

	//@}

        ///@name Inspectores
        //@{

	/** Devolve a op��o actual do menu.  O valor 0 significa "n�o" e o
	    valor 1 significa "n�o".
	
	    \pre V.
	    
	    \post opcaoActual = op��o actual do menu, i.e, a �ltima op��o
	    escolhida pelo utilizador. */
        virtual int opcaoActual() const;

	//@}

	using MenuSimples::interage;
    };

    /** \class Aviso menu.H Slang++/menu.H

	Representa caixas de aviso, que apenas mostram uma mensagem e das
        quais se sai pressionando 'enter'.

	\invariant V.

	\ingroup menus */
    class Aviso {
    public:
        ///@name Construtores
        //@{

        /** Constr�i uma nova caixa de aviso com a mensagem dada.

	    \pre mensagem <> "" e eImprimivel(mensagem). */
        explicit Aviso(std::string const& mensagem);

        /** Destrutor polim�rfico marca uma classe polim�rfica.

	\pre V. */
        virtual ~Aviso();

	//@}

        ///@name Interface com o utilizador
        //@{

        /** Executa a caixa de aviso, i.e., interage com o utilizador do
	    programa.

	    \pre V. */
        virtual void interage();

	//@}

    private:
        MenuSimples menu;

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;
    };

    /** \class CaixaDeTexto menu.H Slang++/menu.H

	Representa caixas de texto, que quando executadas permitem ao
        utilizador introduzir uma cadeia de caracteres.  A cadeia introduzida
        � recordada entre interac��es da caixa e pode-se restringir o seu
        formato impetindo a introdu��o de cadeias vazias e obrigando �
        introdu��o de caracteres de uma lista dada.

	\invariant titulo <> "" e eImprimivel(titulo) e
        1 <= numero_de_espacos_visiveis
        inicio_da_parte_visivel_do_texto <= texto_corrente.size() e
        posicao_do_cursor_nos_espacos_visiveis < numero_de_espacos_visiveis.

	\todo Permitir a passagem de um functor de verifica��o de sintaxe, que
	torne a classe verdadeiramente gen�rica.

	\ingroup menus */
    class CaixaDeTexto : protected ApendiceComCor {
    public:
        ///@name Construtores
        //@{

        /** Constr�i uma nova caixa de texto, com um dado t�tulo, um dado
            texto inicial (por omiss�o ""), um dado conjunto de caracteres
            admiss�veis (por omiss�o "", que significa que qualquer caracter
            imprim�vel � admiss�vel), com a op��o de impedir a termina��o da
            interac��o com a caixa vazia (por omiss�o n�o h� qualquer
            restri��o), e com um determinado n�mero de espa�os vis�veis (que
            pode ser espandido se o t�tulo for mais largo, e que tem valor
            nulo por omiss�o).

	    \pre titulo <> "" e eImprimivel(titulo). */
        explicit CaixaDeTexto(std::string const& titulo, 
                              std::string const& texto_inicial = "",
			      std::string const& caracteres_admissiveis = "",
                              bool deve_impedir_caixa_vazia = false,
			      std::string::size_type espacos = 0);

        /** Destrutor polim�rfico marca uma classe polim�rfica.

	\pre V. */
        virtual ~CaixaDeTexto();

	//@}

        ///@name Inspectores
        //@{

	/** Devolve o texto actual da caixa.
	
	    \pre V.
	    
	    \post textoActual = texto actual da caixa. */
        virtual std::string const& textoActual() const;

        /** Devolve o t�tulo da caixa de texto.

	    \pre V.

	    \post titulo = t�tulo da caixa de texto. */
        std::string titulo() const;

	//@}

        ///@name Interface com o utilizador
        //@{

        /** Executa a caixa de texto, i.e., interage com o utilizador do
	    programa.

	    \pre V. */
        virtual void interage();

	//@}

    private:
        std::string titulo_;
        std::string::size_type numero_de_espacos_visiveis;
        std::string texto_corrente;
        std::string caracteres_admissiveis;
        std::string::size_type inicio_da_parte_visivel_do_texto;
        std::string::size_type posicao_do_cursor_nos_espacos_visiveis;
        Dimensao dimensao;
        Posicao origem;
	bool impede_caixa_vazia;

	// Desenha a caixa de texto:
        void desenha() const;

	// Calcula posicao da caixa de texto:
        void calculaPosicao();

	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = (titulo <> "" e eImprimivel(titulo) e
	    1 <= numero_de_espacos_visiveis e
	    inicio_da_parte_visivel_do_texto <= texto_corrente.size() e
	    posicao_do_cursor_nos_espacos_visiveis <
	    numero_de_espacos_visiveis). */
	bool cumpreInvariante() const;
    };
}

#include <Slang++/menu_impl.H>

#endif // SLANG_MENU_H
