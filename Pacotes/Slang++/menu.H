/** \file menu.H 

    Ficheiro de interface do módulo menus. Define classes que permitem usar
    menus.

    \ingroup menus */
#ifndef SLANG_MENU_H
#define SLANG_MENU_H

#include <vector>
#include <string>

#include <Slang++/ecra.H>

namespace Slang {

    /** \defgroup menus Ferramentas de menus
	Módulo correspondente ao ficheiro Slang++/menu.H. Contém ferramentas
	para criar e executar vários tipos de menus e caixas de diálogo
	simples. 

	Os vários tipos de menus são exemplificados no programa abaixo:

	\include exemplo2.C */

    /** \class ApendiceComCor menu.H Slang++/menu.H

	Define ferramentas relacionadas com cores para os menus que as
	possuirem. 
        
        São definidas cores para a borda, o título, os itens e o item corrente 
        do menu.  As cores usadas são (por omissão):
        
        -# borda: preto sobre branco (ou cinzento).
        -# título: vermelho sobre branco (ou cinzento).
        -# itens: preto sobre branco (ou cinzento).
        -# item corrente: amarelo sobre azul.

        Um apêndice serve para equipar outras classes de ferramentas mais ou
        menos avulsas.  Estas classes são conhecidas também por
        <em>mixin</em>.

	\invariant V.

	\ingroup menus */
    class ApendiceComCor {
    protected:
        ///@name Construtores
        //@{

        /** Constrói um novo apêndice com cor, atribuindo cores por omissão.
	    
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

        /** Destrói um apêndice com cor.

	    \pre V. */
        ~ApendiceComCor();

	//@}
        
        ///@name Inspectores
        //@{

        /** Devolve o objecto cor da borda.
	    
	    \pre V.

	    \post objectoCorDaBorda é o objecto cor usado para representar a
	    borda do menu. */
        Ecra::ObjectoCor const& objectoCorDaBorda() const;

        /** Devolve o objecto cor do título.
	    
	    \pre V.

	    \post objectoCorDoTitulo é o objecto cor usado para representar o
	    título do menu. */
        Ecra::ObjectoCor const& objectoCorDoTitulo() const;

        /** Devolve o objecto cor dos itens.
	    
	    \pre V.

	    \post objectoCorDosItens é o objecto cor usado para representar os
	    itens do menu. */
        Ecra::ObjectoCor const& objectoCorDosItens() const;

        /** Devolve o objecto cor do item corrente.
	    
	    \pre V.

	    \post objectoCorDoItemCorrente é o objecto cor usado para
	    representar o item corrente do menu. */
        Ecra::ObjectoCor const& objectoCorDoItemCorrente() const;

        //@}

        ///@name Modificadores
        //@{

        /** Devolve o objecto cor da borda.
	    
	    \pre V.

	    \post objectoCorDaBorda é o objecto cor usado para representar a
	    borda do menu. */
        Ecra::ObjectoCor& objectoCorDaBorda();

        /** Devolve o objecto cor do título.
	    
	    \pre V.

	    \post objectoCorDoTitulo é o objecto cor usado para representar o
	    título do menu. */
        Ecra::ObjectoCor& objectoCorDoTitulo();

        /** Devolve o objecto cor dos itens.
	    
	    \pre V.

	    \post objectoCorDosItens é o objecto cor usado para representar os
	    itens do menu. */
        Ecra::ObjectoCor& objectoCorDosItens();

        /** Devolve o objecto cor do item corrente.
	    
	    \pre V.

	    \post objectoCorDoItemCorrente é o objecto cor usado para
	    representar o item corrente do menu. */
        Ecra::ObjectoCor& objectoCorDoItemCorrente();

        //@}

    private:
        Ecra::ObjectoCor objecto_cor_da_borda;
        Ecra::ObjectoCor objecto_cor_do_titulo;
        Ecra::ObjectoCor objecto_cor_dos_itens;
        Ecra::ObjectoCor objecto_cor_do_item_corrente;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;
    };

    /** \class Menu menu.H Slang++/menu.H

        Classe abstracta que representa a interface básica de todos os menus. 

	\invariant titulo <> "" e eImprimivel(titulo)..

	\ingroup menus */
    class Menu {
    public:
        ///@name Construtores
        //@{

        /** Constrói um novo menu com o título dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit Menu(std::string const& titulo);

        /** Destrutor abstracto marca uma classe abstracta.

	\pre V. */
        virtual ~Menu() = 0;

	//@}

        ///@name Inspectores
        //@{

        /** Devolve o título do menu.

	    \pre V.

	    \post titulo = título do menu. */
        std::string titulo() const;

	/** Devolve a opção actual do menu (o primeiro item do menu tem número
            0).
	
	    \pre V.
	    
	    \post opcaoActual = opção actual do menu. */
        virtual int opcaoActual() const = 0;

	//@}

        ///@name Interacção com o utilizador
        //@{

        /** Executa o menu, i.e., interage com o utilizador do programa.

	    \pre V.

	    \post opcaoActual() é a última opção escolhida pelo utilizador. */
        virtual void interage() = 0;

	//@}

    private:
        std::string titulo_;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = (titulo <> "" e eImprimivel(titulo)). */
	bool cumpreInvariante() const;
    };

    /** \class MenuComCor menu.H Slang++/menu.H

	Classe abstracta que define a interface básica de todos os menus com
	cores.  A parte das cores é herdada do apêndice ApendiceComCor. 

	\ingroup menus */
    class MenuComCor: public Menu, protected ApendiceComCor {
    public:
        ///@name Construtores
        //@{

        /** Constrói um novo menu com o título dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuComCor(std::string const& titulo);

        /** Destrutor abstracto marca uma classe abstracta.

	\pre V. */
	virtual ~MenuComCor() = 0;

	//@}
    };

    /** \class MenuSimples menu.H Slang++/menu.H
	Representa menus simples, que consistem numa sequência de itens.

        O programa abaixo mostra um menu simples no ecrã e escreve a opção que
        for pressionada até ser seleccionada a opção "Basar":

        \include menu1.C 

	O mesmo exemplo poderia ser escrito com mais simplicidade se não se
	precisasse de acedar às opções do menu individualmente:

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

        /** Constrói um menu simples com o título dado e com os itens cujo
            texto é dado na forma de uma matriz clássica de cadeias de
            caracteres.

	    \pre titulo <> "" e eImprimivel(titulo) e
	    1 <= numero_de_itens e itens tem numero_de_itens elementos  e 
	    (Q j : 0 <= j < numero_de_itens : eImprimivel(itens[j])).

	    \post titulo() = titulo. */
        MenuSimples(std::string const& titulo, 
                    std::string const itens[], 
                    int const numero_de_itens);

        /** Constrói um menu simples com o título dado e com os itens cujo
            texto é dado na forma de uma cadeia de caracteres onde os itens
            são terminados por '\\n'.

	    \pre titulo <> "" e eImprimivel(titulo) e itens tem pelo menos um
	    item e os itens em itens são todos imprimíveis.

	    \post titulo() = titulo. */
        MenuSimples(std::string const& titulo, 
                    std::string const& itens);

	//@}

        ///@name Inspectores
        //@{

	/** Devolve a opção actual do menu (o primeiro item do menu tem número
            0).
	
	    \pre V.
	    
	    \post opcaoActual = opção actual do menu, i.e, a última opção
	    escolhida pelo utilizador. */
        virtual int opcaoActual() const;

	//@}

        ///@name Interface com o utilizador
        //@{

        /** Executa o menu, i.e., interage com o utilizador do programa.

	    \pre V.

	    \post opcaoActual() é a última opção escolhida pelo utilizador. */
        virtual void interage();

	//@}

    private:
        std::vector<std::string> itens;
        int numero_de_itens;
        std::string::size_type comprimento_maximo_dos_itens;
        Posicao posicao;
        Dimensao dimensao;
        int opcao_corrente;

	// Calcula dimensão do menu:
        void calculaDimensao();

	// Calcula posicao do menu:
        void calculaPosicao();

	// Desenha o item com o número dado:
        void desenhaItem(int numero_do_item) const;

	// Desenha o menu completo:
        void desenha() const;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = (1 <= numero_de_itens e itens.size() =
	    numero_de_itens e (Q j : 0 <= j < numero_de_itens :
	    eImprimivel(itens[j])) e comprimento_maximo_dos_itens = max((M j:
	    0 <= j < numero_de_itens : itens[j].size()), titulo().length()) e
	    0 <= opcao_corrente < numero_de_itens). */
	bool cumpreInvariante() const;
    };

    /** \class MenuDeCores menu.H Slang++/menu.H

	Representa menus de selecção das cores básicas usáveis no ecrã. 

	\ingroup menus */
    class MenuDeCores : public MenuSimples {
    public:
        ///@name Construtores
        //@{

        /** Constrói um novo menu de cores com o título dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuDeCores(std::string const& titulo);

	//@}
    };

    /** \class MenuDeSimOuNao menu.H Slang++/menu.H

        Representa menus com apenas duas opções: sim e não. 

	\ingroup menus */
    class MenuDeSimOuNao : private MenuSimples {
    public:
        ///@name Construtores
        //@{

        /** Constrói um novo menu sim/não com o título dado.

	    \pre titulo <> "" e eImprimivel(titulo).

	    \post titulo() = titulo. */
        explicit MenuDeSimOuNao(std::string const& titulo);

	//@}

        ///@name Inspectores
        //@{

	/** Devolve a opção actual do menu.  O valor 0 significa "não" e o
	    valor 1 significa "não".
	
	    \pre V.
	    
	    \post opcaoActual = opção actual do menu, i.e, a última opção
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

        /** Constrói uma nova caixa de aviso com a mensagem dada.

	    \pre mensagem <> "" e eImprimivel(mensagem). */
        explicit Aviso(std::string const& mensagem);

        /** Destrutor polimórfico marca uma classe polimórfica.

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

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;
    };

    /** \class CaixaDeTexto menu.H Slang++/menu.H

	Representa caixas de texto, que quando executadas permitem ao
        utilizador introduzir uma cadeia de caracteres.  A cadeia introduzida
        é recordada entre interacções da caixa e pode-se restringir o seu
        formato impetindo a introdução de cadeias vazias e obrigando à
        introdução de caracteres de uma lista dada.

	\invariant titulo <> "" e eImprimivel(titulo) e
        1 <= numero_de_espacos_visiveis
        inicio_da_parte_visivel_do_texto <= texto_corrente.size() e
        posicao_do_cursor_nos_espacos_visiveis < numero_de_espacos_visiveis.

	\todo Permitir a passagem de um functor de verificação de sintaxe, que
	torne a classe verdadeiramente genérica.

	\ingroup menus */
    class CaixaDeTexto : protected ApendiceComCor {
    public:
        ///@name Construtores
        //@{

        /** Constrói uma nova caixa de texto, com um dado título, um dado
            texto inicial (por omissão ""), um dado conjunto de caracteres
            admissíveis (por omissão "", que significa que qualquer caracter
            imprimível é admissível), com a opção de impedir a terminação da
            interacção com a caixa vazia (por omissão não há qualquer
            restrição), e com um determinado número de espaços visíveis (que
            pode ser espandido se o título for mais largo, e que tem valor
            nulo por omissão).

	    \pre titulo <> "" e eImprimivel(titulo). */
        explicit CaixaDeTexto(std::string const& titulo, 
                              std::string const& texto_inicial = "",
			      std::string const& caracteres_admissiveis = "",
                              bool deve_impedir_caixa_vazia = false,
			      std::string::size_type espacos = 0);

        /** Destrutor polimórfico marca uma classe polimórfica.

	\pre V. */
        virtual ~CaixaDeTexto();

	//@}

        ///@name Inspectores
        //@{

	/** Devolve o texto actual da caixa.
	
	    \pre V.
	    
	    \post textoActual = texto actual da caixa. */
        virtual std::string const& textoActual() const;

        /** Devolve o título da caixa de texto.

	    \pre V.

	    \post titulo = título da caixa de texto. */
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

	/** Indica se a condição invariante da classe se verifica.

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
