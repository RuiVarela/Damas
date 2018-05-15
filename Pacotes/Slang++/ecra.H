/** \file ecra.H 

    Ficheiro de interface do módulo ecras.  Define a classe
    Slang::Ecra e outras classes associadas.

    \todo Ver se versões mais actualizadas do S-Lang indicam com rigor
    cores válidas no fundo e posições da palete; verificar se se dão
    bem com a Konsole.

    \todo A restrição do cursor ao ecrã real não está a ser feita
    sistematicamente. Por enquanto não é problemático, pois o ecrã solitão é
    contruído sem essa restrição e o consumidor do código não a pode impor a
    posteriori. 

    \todo Na cologem de troços dever-se-ia guardar o objecto cor actual para o
    poder repor no final da colagem.

    \todo Escrever testes para o ecrã.  É possível, pois pode-se analizar o
    conteúdo dos troços, em princípio.  Mas é necessário alterar muito
    código.

    \ingroup ecras */
#ifndef SLANG_ECRA_H
#define SLANG_ECRA_H

#include <string>
#include <vector>
#include <iostream>
#include <limits>

#include <Slang++/teclado.H>

namespace Slang {

    /** \defgroup ecras Ferramentas de ecrã

        Módulo correspondente ao ficheiro Slang++/ecra.H. Contém
        ferramentas para escrever e manipular o ecrã. */

    // Declaração de classe definida mais abaixo.
    class Dimensao;


    /** \class Posicao ecra.H Slang++/ecra.H 

         Representa a posição de uma célula do ecrã.  As coordenadas
         de uma posição são inteiras e expressas em (linha, coluna).
         A linha 0 corresponde ao topo do ecrã e a coluna 0
         corresponde ao lado esquerdo do ecrã.  Note-se que
         conceptualmente o ecrã é ilimitado (ou melhor, é limitado
         apenas pela gama dos inteiros usados como coordenadas), o que
         significa que as posições podem ter coordenadas negativas.

	 É possível realizar operações aritméticas com posições e
	 dimensões (i.e., valores da classe Dimensao).  As posições
	 são entendidas como pontuais, enquanto as dimensões são
	 entendidas como vectoriais.  Assim, a diferença entre duas posições
	 é uma dimensão, sendo também possível adicinar ou subtrair dimensões
	 a posições, de que resulta uma nova posição.

	 As posições podem ser inseridas no ecrã, usando o operador <<, o que
	 tem como efeito colocar o cursor na posição inserida (ou na posição
	 mais próxima do ecrã real, se o ecrã tiver o cursor limitado ao ecrã
	 real).

	 \invariant V.

        \ingroup ecras */
    class Posicao {
    public:
        ///@name Construtores
        //@{

        /** Constrói uma nova posição.  Por omissão a posição
            corresponde ao canto superior esquerdo do ecrã.

            \pre V.

            \post linha() = \a linha e coluna() = \a coluna.  */
        explicit Posicao(int const linha = 0, 
			 int const coluna = 0);

        //@}

        ///@name Inspectores
        //@{

        /** Devolve a linha do ecrã correspondente à posição.

            \pre V.

            \post linha() = linha a que a posição corresponde. */
        int linha() const;

        /** Devolve a coluna do ecrã correspondente à posição.

            \pre V.

            \post coluna() = coluna a que a posição corresponde. */
        int coluna() const;

        //@}

        ///@name Modificadores
        //@{

        /** Muda a linha do ecrã correspondente à posição para \a
	    nova_linha.

            \pre V.

            \post linha() = \a nova_linha. */
        void mudaLinhaPara(int const nova_linha);

        /** Muda a coluna do ecrã correspondente à posição para \a
	    nova_coluna.

            \pre V.

            \post coluna() = \a nova_coluna. */
        void mudaColunaPara(int const nova_coluna);

        //@}

        ///@name Serializadores
        //@{

        /** Constrói uma posição por carregamento a partir de um canal
            de entrada.  Assume-se que os dados no canal têm um
            formato equivalente ao produzido pela operação guardaEm().

            \pre entrada.good().  

            \post Posicao é a posição que se encontrava no canal de
            entrada.

            \exception ErroAoCarregar é lançada se a construção por
            carregamento falhar.  */
        explicit Posicao(std::istream& entrada);

        /** Carrega a posição a partir de um canal.  Assume-se que os
            dados no canal têm um formato equivalente ao produzido
            pela operação guardaEm().

            \pre entrada.good().

            \post *this é a posição que se encontrava no canal de entrada.

            \exception ErroAoCarregar é lançada se o carregamento falhar.
            Nesse caso o canal pode ficar parcialmente lido. */
        void carregaDe(std::istream& entrada);

        /** Guarda a posição num canal.  O formato produzido é
            compatível com o que o método carregaDe() espera.

            \pre saida.good().

            \exception ErroAoGuardar é lançada se a operação falhar.
            Nesse caso o canal pode ficar parcialmente escrito. */
        void guardaEm(std::ostream& saida) const;

        //@}

        ///@name Operadores especiais de atribuição
        //@{

        /** Adiciona a posição de uma dimensão interpretada como um
	    vector.

            \pre *this = p.

            \post *this = p + \a deslocamento. */
        Posicao& operator+=(Dimensao const& deslocamento);

        /** Subtrai a posição de uma dimensão interpretada como um
	    vector.

            \pre *this = p.

            \post *this = p - \a deslocamento. */
        Posicao& operator-=(Dimensao const& deslocamento);

        //@}

    private:
        int linha_;
        int coluna_;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;
    };

    /** \relates Posicao

         Devolve a adição de uma posição com uma dimensão (a dimensão
         é interpretada como um vector).

        \pre p = posicao.

        \post operator+.linha() = p.linha() + deslocamento.numeroDeLinhas() e
        operator+.coluna() = p.coluna() + deslocamento.numeroDeColunas(). */
    Posicao const operator+(Posicao posicao, 
                            Dimensao const& deslocamento);

    /** \relates Posicao

         Devolve a subtracção de uma posição de uma dimensão (a
         dimensão é interpretada como um vector).

        \pre p = posicao.

        \post operator+.linha() = p.linha() - deslocamento.numeroDeLinhas() e
        operator+.coluna() = p.coluna() - deslocamento.numeroDeColunas(). */
    Posicao const operator-(Posicao posicao, 
                            Dimensao const& deslocamento);

    /** \relates Posicao

         Devolve a adição de uma posição com uma dimensão (a dimensão
         é interpretada como um vector).

        \pre p = posicao.

        \post operator+.linha() = p.linha() + deslocamento.numeroDeLinhas() e
        operator+.coluna() = p.coluna() + deslocamento.numeroDeColunas(). */
    Posicao const operator+(Dimensao const& deslocamento,
			    Posicao posicao);

    /** \relates Posicao

         Devolve a subtracção de uma posição de uma dimensão (a
         dimensão é interpretada como um vector).

        \pre V.

        \post operator+.linha() = deslocamento.numeroDeLinhas() -
        posicao.linha() e operator+.coluna() =
        deslocamento.numeroDeColunas() - posicao.coluna(). */
    Posicao const operator-(Dimensao const& deslocamento,
			    Posicao const& posicao);

    /** \relates Posicao

         Devolve a diferença entre duas posições, que é a dimensão
         correspondente ao vector entre as duas posições.

        \pre V.

        \post operator+.numeroDeLinhas() = destino.linha() - origem.linha() e
        operator+.numeroDeColunas() = destino.coluna() - origem.coluna(). */
    Dimensao const operator-(Posicao const& destino,
			     Posicao const& origem);

    /** \relates Posicao

         Devolve o simétrico de uma posição.

        \pre V.

        \post operator-.linha() = -posicao.linha() e
        operator-.coluna() = -posicao.coluna(). */
    Posicao const operator-(Posicao const& posicao);

    /** \relates Posicao

         Indica se duas posições são iguais. 

        \pre V.

        \post operator== = (uma_posicao.linha() =
        outra_posicao.linha() e uma_posicao.coluna() =
        outra_posicao.coluna()). */
    bool operator==(Posicao const& uma_posicao, 
                    Posicao const& outra_posicao);

    /** \relates Posicao

         Indica se duas posições são diferentes. 

        \pre V.

        \post operator!= = (uma_posicao.linha() <>
        outra_posicao.linha() ou uma_posicao.coluna() <>
        outra_posicao.coluna()). */
    bool operator!=(Posicao const& uma_posicao, 
                    Posicao const& outra_posicao);


    /** \class Dimensao ecra.H Slang++/ecra.H 

         Representa uma dimensão em células do ecrã.  É tipicamente
         usada para representar a dimensão de caixas.  As dimensões
         são expressas em número de linhas e colunas.  Qualquer das
         componentes de uma dimensão pode tomar valores negativos.
         Quando isso acontecer diz-se que a dimensão é "não-canónica".

	 As dimensões também podem ser vistas como vectores.  Daí que possam
	 ser adicionadas a posições.  Da mesma forma, a subtracção entre duas
	 posições é uma dimensão.

	 \invariant V.

        \ingroup ecras */
    class Dimensao {
    public:
        ///@name Construtores
        //@{

        /** Constrói uma nova dimensão.  Por omissão a dimensão é
            nula.  Pode haver dimensões negativas.

            \pre V.

            \post numeroDeLinhas() = \a numero_de_linhas e
            numeroDeColunas() = \a numero_de_colunas. */
        explicit Dimensao(int const numero_de_linhas = 0, 
                          int const numero_de_colunas = 0);

        /** Constrói uma nova dimensão à custa de uma posição.  Define
            uma conversão explícita entre posições e dimensões.  A
            dimensão é a dimensão de uma caixa com canto superior
            esquerdo na célula (0, 0) e com canto inferior direito na
            célula imediatamente acima e à esquerda da posição dada.

            \pre V.

            \post numeroDeLinhas() = posicao.linha() e
            numeroDeColunas() = posicao.coluna(). */
        explicit Dimensao(Posicao const& posicao);

        //@}

        ///@name Inspectores

        //@{

        /** Devolve o número de linhas ecrã correspondente à dimensão.

            \pre V.

            \post numeroDeLinhas() = número de linhas a que a dimensão
            corresponde. */
        int numeroDeLinhas() const;

        /** Devolve o número de colunas ecrã correspondente à dimensão.

            \pre V.

            \post numeroDeColunas() = número de colunas a que a
            dimensão corresponde. */
        int numeroDeColunas() const;

        //@}

        ///@name Predicados

        //@{

        /** Indica se a dimensão é canónica, i.e., se ambas as
	    componentes são não-negativas.

            \pre V.

            \post eCanonica() = (0 <= numeroDeLinhas() and 0 <=
            numeroDeColunas()). */
        bool eCanonica() const;

        //@}

        ///@name Modificadores 
        //@{

        /** Muda o número de linhas do ecrã correspondentes à dimensão
            para \a novo_numero_de_linhas.

            \pre V.
            
            \post numeroDeLinhas() = \a novo_numero_de_linhas. */
        void mudaNumeroDeLinhasPara(int const novo_numero_de_linhas);

        /** Muda o número de colunas do ecrã correspondentes à
            dimensão para \a novo_numero_de_colunas.

            \pre V.
             
            \post numeroDeColunas() = \a novo_numero_de_colunas. */
        void mudaNumeroDeColunasPara(int const novo_numero_de_colunas);

        //@}

        ///@name Serializadores
        //@{

        /** Constrói uma dimensão por carregamento a partir de um
            canal de entrada.  Assume-se que os dados no canal têm um
            formato equivalente ao produzido pela operação guardaEm().

            \pre entrada.good().  

            \post Dimensao é a dimensão que se encontrava no canal de
            entrada.

            \exception ErroAoCarregar é lançada se a construção por
            carregamento falhar.  */
        explicit Dimensao(std::istream& entrada);

        /** Carrega a dimensão a partir de um canal.  Assume-se que os
            dados no canal têm um formato equivalente ao produzido
            pela operação guardaEm().

            \pre entrada.good().

            \post *this é a dimensão que se encontrava no canal de
            entrada.

            \exception ErroAoCarregar é lançada se o carregamento
            falhar.  Nesse caso o canal pode ficar parcialmente
            lido. */
        void carregaDe(std::istream& entrada);

        /** Guarda a dimensão num canal.  O formato produzido é
            compatível com o que o método carregaDe() espera.

            \pre saida.good().

            \exception ErroAoGuardar é lançada se a operação falhar.
            Nesse caso o canal pode ficar parcialmente escrito. */
        void guardaEm(std::ostream& saida) const;

        //@}

        ///@name Operadores
        //@{

        /** Adiciona a dimensão de outra dimensão.  A dimensão
            resultante é a soma da original com a dimensão a somar, em
            cada uma das direcções.

            \pre *this = p.

            \post numeroDeLinhas() = p.numeroDeLinhas() +
            dimensao.numeroDeLinhas() e numeroDeColunas() =
            p.numeroDeColunas() + dimensao.numeroDeColunas(). */
        Dimensao& operator+=(Dimensao const& dimensao);

        /** Subtrai a dimensão de outra dimensão.  A dimensão
            resultante é a subtracção da original da dimensão a subtrair,
            em cada uma das direcções.

            \pre *this = p.

            \post numeroDeLinhas() = p.numeroDeLinhas() -
            dimensao.numeroDeLinhas() e numeroDeColunas() =
            p.numeroDeColunas() - dimensao.numeroDeColunas(). */
        Dimensao& operator-=(Dimensao const& dimensao);

        //@}

    private:
	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;

        int numero_de_linhas;
        int numero_de_colunas;
    };

    /** \relates Dimensao

         Devolve a adição de duas dimensões. 

        \pre uma_dimensao = d.

        \post operator+.numeroDeLinhas() = d.numeroDeLinhas() + 
        outra_dimensao.numeroDeLinhas() e operator+.numeroDeColunas() = 
        d.numeroDeColunas() + outra_dimensao.numeroDeColunas(). */
    Dimensao const operator+(Dimensao uma_dimensao, 
                             Dimensao const& outra_dimensao);

    /** \relates Dimensao

         Devolve a subtracção de duas dimensões. 

        \pre uma_dimensao = d.

        \post operator-.numeroDeLinhas() = d.numeroDeLinhas() -
        outra_dimensao.numeroDeLinhas() e operator-.numeroDeColunas() = 
        d.numeroDeColunas() - outra_dimensao.numeroDeColunas(). */
    Dimensao const operator-(Dimensao uma_dimensao, 
			     Dimensao const& outra_dimensao);

    /** \relates Dimensao

         Devolve o simétrico de uma dimensao.

        \pre V.

        \post operator-.numeroDeLinhas() = -dimensao.numeroDeLinhas() e
        operator-.numeroDeColunas() = -dimensao.numeroDeColunas(). */
    Dimensao const operator-(Dimensao const& dimensao);

    /** \relates Dimensao

         Indica se duas dimensões são iguais. 

        \pre V.

        \post operator== = (uma_dimensao.numeroDeLinhas() = 
        outra_dimensao.numeroDeLinhas() e uma_dimensao.numeroDeColunas() = 
        outra_dimensao.numeroDeColunas()). */
    bool operator==(Dimensao const& uma_dimensao, 
                    Dimensao const& outra_dimensao);

    /** \relates Dimensao

         Indica se duas dimensões são diferentes. 

        \pre V.

        \post operator!= = (uma_dimensao.numeroDeLinhas() <>
        outra_dimensao.numeroDeLinhas() ou uma_dimensao.numeroDeColunas() <>
        outra_dimensao.numeroDeColunas()). */
    bool operator!=(Dimensao const& uma_dimensao, 
                    Dimensao const& outra_dimensao);


    /** \class Caixa ecra.H Slang++/ecra.H

        Representa caixas no ecrã.  Uma caixa é um conjunto de células
        formando um rectângulo de lados não oblíquos, i.e., verticais
        ou horizontais. Uma caixa tem uma origem e um extremo.  A dimensão da
        caixa é a diferença entre o extremo e a origem, mas somada de
        Dimensao(1, 1), visto que quer a origem quer o extremo se encontram
        sobre a caixa.  Uma caixa diz-se canónica se a sua dimensão for
        canónica.  Uma caixa diz-se vazia se a sua dimensão for Dimensao(0,
        0).  As caixas podem ser inseridas no ecrã, sendo desenhado um
        rectângulo oco com as suas dimensões.  Por exemplo, o código

	\include caixa1.C

	escreve uma caixa centrada no ecrã e com 1/4 da sua área.

	 \invariant V.

	 \todo Falta implementar as operações de serialização.

        \ingroup ecras
    */
    class Caixa {
    public:
        ///@name Construtores
        //@{

        /** Constrói uma nova caixa.  Por omissão a caixa localiza-se
            no canto superior esquerdo do ecrã e a sua dimensão é
            nula.  Ao canto superior esquerdo de uma caixa chama-se a
            sua "origem".  Ao canto oposto chama-se "extremo".  Note-se que
            uma caixa pode ter dimensão nula ou mesmo negativa em alguma
            direcção.

            \pre V.

            \post origem() = \a origem e dimensao() = \a dimensao. */
        explicit Caixa(Posicao const& origem = Posicao(), 
                       Dimensao const& dimensao = Dimensao());

        /** Constrói uma nova caixa.  Neste caso a construção é feita
            a partir das posições de dois vértices da caixa.  Esses
            vértices são o superior esquerdo (origem) e o
            inferior direito (extremo).  Se a origem estiver à direita ou
            abaixo do extremo, a caixa diz-se não-canónica.

            \pre V.

            \post origem() = origem e extremo() = \a extremo. */
        explicit Caixa(Posicao const& origem, 
                       Posicao const& extremo);

        //@}
        
        ///@name Inspectores
        //@{

        /** Devolve a origem da caixa, i.e., a posição do seu vértice
            superior esquerdo.

            \pre V.

            \post origem() = origem da caixa. */
        Posicao const& origem() const;

        /** Devolve o extremo da caixa, i.e., a posição do seu vértice
            inferior direito.

            \pre V.

            \post extremo() = extremo da caixa. */
        Posicao extremo() const;

        /** Devolve a dimensao da caixa.

            \pre V.

            \post dimensao() = dimensão da caixa. */
        Dimensao const& dimensao() const;

        //@}

        ///@name Predicados
        //@{

        /** Indica se a caixa está vazia, i.e., se a sua dimensão é
	    nula.
            
            \pre V.

            \post eVazia = (dimensao() = Dimensao(0, 0)). */
        bool eVazia() const;

        /** Indica se a caixa é canónica, i.e., se a sua dimensão é
	    canónica. 
            
            \pre V.

            \post eCanonica = dimensao().eCanonica(). */
        bool eCanonica() const;

        /** Indica se uma posição se encontra sobre a caixa, quer
            sobre a sua borda quer sobre o seu interior.  Note-se que
            uma caixa com dimensão negativa em alguma das direcções
            não tem interior.
            
            \pre V.

            \post contem = \a posicao dentro da caixa (interior ou
            borda). */
        bool contem(Posicao const& posicao) const;

        /** Indica se uma posição se encontra sobre a borda da caixa,
            quee existe mesmo para uma caixa vazia ou com dimensão
            negativa em alguma das direcções.
            
            \pre V.

            \post bordaContem = \a posicao na borda da caixa. */
        bool bordaContem(Posicao const& posicao) const;

        //@}

        ///@name Modificadores
        //@{

        /** Muda a origem da caixa para \a nova_origem.  Atenção: a
            dimensão mantém-se, pelo que o extremo da caixa é alterado
            em paralelo com a sua origem!

            \pre dimensao() = d.

            \post origem() = \a nova_origem e dimensao() = d. */
        void mudaOrigemPara(Posicao const& nova_origem);

        /** Muda o extremo da caixa para \a novo_extremo.  Atenção: a
            origem mantém-se, pelo que a dimensão da caixa é alterada,
            ao contrário do que acontece quando a origem é alterada
            directamente!

            \pre origem() = o.

            \post extremo() = \a novo_extremo e origem() = o. */
        void mudaExtremoPara(Posicao const& novo_extremo);

        /** Muda a dimensão da caixa para \a nova_dimensão.  Atenção:
            a origem mantém-se, pelo que o extremo da caixa é alterado
            em paralelo com a sua dimensão!

            \pre origem() = o.

            \post dimensao() = \a nova_dimensao e origem() = o. */
        void mudaDimensaoPara(Dimensao const& nova_dimensao);

        //@}

        ///@name Serializadores
        //@{

        /** Constrói uma caixa por carregamento a partir de um canal de
            entrada.  Assume-se que os dados no canal têm um formato
            equivalente ao produzido pela operação guardaEm().

            \pre entrada.good().  

            \post Posicao é a caixa que se encontrava no canal de entrada.  

            \exception ErroAoCarregar é lançada se a construção por
            carregamento falhar.  */
        explicit Caixa(std::istream& entrada);

        /** Carrega a caixa a partir de um canal.  Assume-se que os
            dados no canal têm um formato equivalente ao produzido
            pela operação guardaEm().

            \pre entrada.good().

            \post *this é a caixa que se encontrava no canal de
            entrada.

            \exception ErroAoCarregar é lançada se o carregamento
            falhar.  Nesse caso o canal pode ficar parcialmente
            lido. */
        void carregaDe(std::istream& entrada);

        /** Guarda a caixa num canal.  O formato produzido é
            compatível com o que o método carregaDe() espera.

            \pre saida.good().

            \exception ErroAoGuardar é lançada se a operação falhar.
            Nesse caso o canal pode ficar parcialmente escrito. */
        void guardaEm(std::ostream& saida) const;

        //@}

        ///@name Operadores especiais de atribuição
        //@{

        /** Desloca a caixa de um dado deslocamento. 

            \pre origem() = o e dimensao() = d.

            \post origem() = o + \a deslocamento e dimensao() = d. */
        Caixa& operator+=(Dimensao const& deslocamento);

        /** Desloca a caixa de um dado deslocamento. 

            \pre origem() = o e dimensao() = d.

            \post origem() = o - \a deslocamento e dimensao() = d. */
        Caixa& operator-=(Dimensao const& deslocamento);

        /** Une a caixa com a caixa \a outra_caixa.  A união de duas
            caixas é a menor caixa que as envolve.

            \pre origem() = o e extremo() = e.

            \post origem().linha() = min(o.linha(),
            outra_caixa.origem().linha()) e origem().coluna() =
            min(o.coluna(), outra_caixa.origem().coluna()) e
            extremo().linha() = max(e.linha(),
            outra_caixa.extremo().linha()) e extremo().coluna() =
            max(e.coluna(), outra_caixa.extremo().coluna()). */
        Caixa& operator+=(Caixa const& outra_caixa);

        /** Intersecta a caixa com a caixa \a outra_caixa.  A
            intersecção de duas caixas é a maior caixa que se inclui
            em ambas.  Note-se, no entanto, que se as duas caixas
            forem regulares (i.e., com dimensão positiva) e se não
            intersectarem geometricamente, esta operação tem como
            resultado uma caixa com pelo menos uma dimensão negativa
            ou nula.

            \pre origem() = o e extremo() = e.

            \post origem().linha() = max(o.linha(),
            outra_caixa.origem().linha()) e origem().coluna() =
            max(o.coluna(), outra_caixa.origem().coluna()) e
            extremo().linha() = min(e.linha(),
            outra_caixa.extremo().linha()) e extremo().coluna() =
            min(e.coluna(), outra_caixa.extremo().coluna()). */
        Caixa& operator*=(Caixa const& outra_caixa);

        //@}

    private:
	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;

        Posicao origem_;
        Dimensao dimensao_;
    };

    /** \relates Caixa

         Devolve a adição de uma caixa e de uma dimensão.  A dimensão é
         interpretada como um vector de deslocamento.  A caixa
         devolvida é igual à recebida como argumento, embora deslocada
         de acordo com o deslocamento dado.

        \pre caixa = c.

        \post operator+.dimensao() = c.dimensao() e operator+.origem()
        = c.origem() + deslocamento. */
    Caixa const operator+(Caixa caixa, Dimensao const& deslocamento);

    /** \relates Caixa

         Devolve a subtracção de uma caixa e de uma dimensão.  A dimensão é
         interpretada como um vector de deslocamento.  A caixa
         devolvida é igual à recebida como argumento, embora deslocada
         de acordo com o deslocamento dado.

        \pre caixa = c.

        \post operator-.dimensao() = c.dimensao() e operator-.origem()
        = c.origem() - deslocamento. */
    Caixa const operator-(Caixa caixa, Dimensao const& deslocamento);

    /** \relates Caixa

         Devolve a adição de uma caixa e de uma dimensão.  A dimensão é
         interpretada como um vector de deslocamento.  A caixa
         devolvida é igual à recebida como argumento, embora deslocada
         de acordo com o deslocamento dado.

        \pre caixa = c.

        \post operator+.dimensao() = c.dimensao() e operator+.origem()
        = c.origem() + deslocamento. */
    Caixa const operator+(Dimensao const& deslocamento, Caixa caixa);

    /** \relates Caixa

         Devolve a união de duas caixas.  A união de duas caixas é a
         menor caixa que as envolve.

        \pre uma_caixa = c.

        \post operator+.origem().linha() = min(c.origem().linha(),
        outra_caixa.origem().linha()) e operator+.origem().coluna() =
        min(c.origem().coluna(), outra_caixa.origem().coluna()) e
        operator+.extremo().linha() = max(c.extremo().linha(),
        outra_caixa.extremo().linha()) e operator+.extremo().coluna()
        = max(c.extremo().coluna(),
        outra_caixa.extremo().coluna()). */
    Caixa const operator+(Caixa uma_caixa, Caixa const& outra_caixa);

    /** \relates Caixa

         Devolve a intersecção de duas caixas.  A intersecção de duas
         caixas é a maior caixa que se inclui em ambas.  Note-se, no
         entanto, que se as duas caixas forem regulares (i.e., com
         dimensão positiva) e se não intersectarem geometricamente,
         esta operação tem como resultado uma caixa com pelo menos uma
         dimensão negativa ou nula.
        
        \pre uma_caixa = c.

        \post origem().linha() = max(c.origem().linha(),
        outra_caixa.origem().linha()) e origem().coluna() =
        max(c.origem().coluna(), outra_caixa.origem().coluna()) e
        extremo().linha() = min(c.extremo().linha(),
        outra_caixa.extremo().linha()) e extremo().coluna() =
        min(c.extremo().coluna(), outra_caixa.extremo().coluna()). */
    Caixa const operator*(Caixa uma_caixa, Caixa const& outra_caixa);

    /** \relates Caixa

         Indica se duas caixas são iguais. 

        \pre V.

        \post operator== = (uma_caixa.origem() = outra_caixa.origem() e
	uma_caixa.dimensao() = outra_caixa.dimensao()). */
    bool operator==(Caixa const& uma_caixa, Caixa const& outra_caixa);

    /** \relates Caixa

         Indica se duas caixas são diferentes. 

        \pre V.

        \post operator!= = (uma_caixa.origem() <> outra_caixa.origem() ou
	uma_caixa.dimensao() <> outra_caixa.dimensao()). */
    bool operator!=(Caixa const& uma_caixa, Caixa const& outra_caixa);

    /**@name Constantes associadas à classe Caixa
       \ingroup ecras */
    //@{

    /** \relates Caixa

         Constante representando uma caixa vazia, i.e., com dimensão
         nula.  Esta caixa tem como origem o canto superior esquerdo
         do ecrã.

        \hideinitializer */
    Caixa const caixa_vazia = Caixa();

    /** \relates Caixa

         Constante representando a caixa universal (enche todo o
         espaço).

         \hideinitializer */
    Caixa const caixa_universal = 
    Caixa(Posicao(std::numeric_limits<int>::min(),
                  std::numeric_limits<int>::min()), 
          Dimensao(std::numeric_limits<int>::max(),
                  std::numeric_limits<int>::max()));

    //@}


    /** Representa as possíveis cores do texto e do fundo de cada
         célula do ecrã.  Note-se que nem todas as cores são válidas
         para o fundo em todos os terminais!  Experimente para
         verificar quais funcionam bem...  Ver na documentação abaixo
         os nomes das cores usados para inserção e extração de canais.

        \ingroup ecras */
    enum Cor {
        preto,                  ///< Num canal: \c preto.
        primeira_cor = preto,        
        cinza,                  ///< Num canal: \c cinza.
        vermelho,               ///< Num canal: \c vermelho.
        vermelho_brilhante,     ///< Num canal: \c vermelho-brilhante.
        verde,                  ///< Num canal: \c verde.
        verde_brilhante,        ///< Num canal: \c verde-brilhante.
        castanho,               ///< Num canal: \c castanho.
        amarelo,                ///< Num canal: \c amarelo.
        azul,                   ///< Num canal: \c azul.
        azul_brilhante,         ///< Num canal: \c azul-brilhante.
        magenta,                ///< Num canal: \c magenta.
        magenta_brilhante,      ///< Num canal: \c magenta-brilhante.
        ciano,                  ///< Num canal: \c ciano.
        ciano_brilhante,        ///< Num canal: \c ciano-brilhante.
        cinzento_claro,         ///< Num canal: \c cinzento-claro.
        branco,                 ///< Num canal: \c branco.
        ultima_cor = branco
    };

    /**@name Operadores associados ao tipo enumerado Cor
       \ingroup ecras */
    //@{

    /** Insere uma cor num canal.

        \pre V.

        \post não saida.good() ou (saida.good() e canal contém a
        representação textual da cor). */
    std::ostream& operator<<(std::ostream& saida, Cor const cor);

    /** Extrai uma cor de um canal.

        \pre cor = c.

        \post (não entrada.good() e cor = c) ou (entrada.good() e
        canal já não contém a representação textual da cor e cor = cor
        cuja representação textual estava no canal). */
    std::istream& operator>>(std::istream& entrada, Cor& cor);

    /** Constante que guarda o número total de cores.  

        \hideinitializer */
    int const numero_de_cores = ultima_cor + 1;

    //@}

    /** Representa caracteres especiais úteis para desenhar no ecrã
        caixas e outros símbolos pouco usuais.

	Pode ver o aspecto destes símbolos executando o seguinte programa de
	exemplo:

	\include simbolo1.C

        \ingroup ecras */
    enum Simbolo {
        diamante = '`',
        tijolo,
        ht,
        ff,
        cr,
        lf,
        grau,
        mais_menos,
        nl,
        vt,
        canto_inferior_direito,
        canto_superior_direito,
        canto_superior_esquerdo,
        canto_inferior_esquerdo,
        cruzamento,
        traco_topo,
        traco_superior,
        traco_horizontal,
        traco_inferior,
        traco_base,
        encontro_direita,
        encontro_esquerda,
        encontro_cima,
        encontro_baixo,
        traco_vertical,
        menor_ou_igual,
        maior_ou_igual,
        pi,
        diferente
    };


    /** Representa os vários tipos de justificação possíveis ao
        escrever texto no ecrã.

	O valor a_esquerda (que é a justificação por omissão do ecrã) faz
	com que as entidades inseridas no ecrã fiquem à esquerda do espaço
	para eles reservado.  O valor a_direita alinha as entidades à
	direita. O valor ao_centro leva as entidades inseridas a serem
	colocadas ao centro do espaço para elas reservado através, por
	exemplo, do manipulador largura().  Se o espaço reservado for
	insuficiente, a entidade inserida será truncada à direita, de ambos os
	lados, ou à esquerda, consoante a justificação escolhida seja à
	esquerda, ao centro ou à direita.

	O programa que se segue ilustra o funcionamento destes valores
	enumerados, que ao serem inseridos no ecrã alteram a justificação de
	forma permanente:

	\include justificacao1.C

        \see largura()

        \ingroup ecras */
    enum Justificacao {
        /** Manipulador usado para colocar justificação centrada. */
        ao_centro,
        /** Manipulador usado para colocar justificação à esquerda. */
        a_esquerda,
        /** Manipulador usado para colocar justificação à direita. */
        a_direita
    };


    /** \class Ecra ecra.H Slang++/ecra.H

        Representa o ecrã.  Esta classe é um solitão, pois admite-se
        não haver senão um ecrã.

        Por ecrã entende-se um conjunto de células cada uma das quais
        contém um caractere com uma dada cor de texto e uma dada cor
        de fundo.  Conceptualmente o ecrã estende-se em ambas as
        direcções até ao infinito, que vertical quer horizontalmente.
        No entanto, só uma parte do ecrã é visível, dependendo da
        dimensão do dispositivo onde ocorrerá a sua visualização.  Por
        exemplo, se o ecrã estiver a ser visualizado na janela de uma
        consola (e.g., \c xterm) com 24 linhas e 80 colunas, só serão
        visíveis as linhas 0 a 23 do ecrã e as colunas 0 a 79.
        chamar-se ecrã real ao dispositivo no qual o ecrã (virtual) é
        visualizado ou, pelo menos, à zona do ecrã virtual que é
        visível no ecrã real.

        O ecrã é virtual.  As alterações nele feitas só têm efeito no
        ecrã real depois de uma operação de refrescamento.  Veja-se a
        operação refresca() ou o manipulador refresca.

        O ecrã permite várias operações: 

          -# inspeccionar a dimensão do ecrã real e a posição do
          cursor no ecrã (virtual);
          -# verificar se o ecrã real foi redimensionado;
          -# modificar a posição do cursor (de várias formas diferentes);
          -# copiar ou colar um troço de/para uma posição do ecrã (um
          troço é um conjunto rectangular de células do ecrã);
          -# apagar várias partes do ecrã;
          -# refrescar o ecrã real (ou seja, mostrar ou ecrã virtual);
          -# desenhar uma caixa no ecrã;
          -# enviar para o ecrã um caractere, um inteiro, uma cadeia
          de caracteres, uma caixa, um troço ou um dos manipuladores
          definidos;
          -# etc.

        \b Refrescamento

        As alterações só são visíveis depois de chamada uma das operações de
        refrescamento do ecrã. Quando há um redimensionamento do ecrã deve ser
        invocada a operação refrescaTudo() ou usado o manipulador
        refresca_tudo.  Quando são feitas pequenas alterações deve ser
        invocada a operação refresca() ou usado o manipulador refresca.

        \b Exemplo de utilização

        O programa que se segue escreve no ecrã todas as letras do
        alfabeto (maiúsculas e minúsculas) e depois, a cada pressão de
        uma tecla, escreve os dígitos de zero a nove com outra cor,
        com largura proporcional ao dígito escrito e centrados.

        \include ecra1.C

	Para mais exemplos ver documentação das operações específicas e das
	classe auxiliares.

        \ingroup ecras */
    class Ecra {
    public:
	// A classe Manipulador será definida mais abaixo.
	class Manipulador;

        // A classe Troco será definida mais abaixo.
        class Troco;

        // A classe ObjectoCor será definida mais abaixo.
        class ObjectoCor;

        ///@name Construtores
        //@{

        /** Constrói um ecrã.  Encarrega-se de inicializar o "screen
             management" do S-Lang.  Se se construir com
             limita_cursor_ao_ecra_real verdadeiro, o ecrã garantirá
             que o cursor se encontra dentro dos limites do ecrã real
             em cada instante.  Por omissão essa verificação não é
             feita, ou seja, o cursor pode-se deslocar para fora do
             ecrã real.  O construtor recebe também as cores do texto
             e do fundo das chamadas "células do fundo", para as quais
             não se explicita nenhuma cor.

             Tal como a biblioteca se encontra definida, este
             construtor não pode ser usado directamente, pois a classe
             é um solitão e a biblioteca pré-define uma variável
             global deste tipo.  No entanto, numa versão futura, onde
             não exista variável global para representar o ecrã, o
             programador utilizador pode vir a usá-lo.

            \pre V.

            \post Ecra é um ecrã pronto a utilizar.*/
        explicit Ecra(Cor cor_do_texto = branco, 
                      Cor cor_do_fundo = preto, 
                      bool limita_cursor_ao_ecra_real = false);

        /** Destrutor da classe.  Encarrega-se de finalizar o "screen
            management" do S-Lang.

            \pre V. */
        ~Ecra();

        //@}

        ///@name Inspectores
        //@{

        /** Devolve a dimensão corrente do ecrã real.

            No programa abaixo vê-se uma utilização deste inspector para
            controlar a dimensão de uma caixa inserida no ecrã.

	    \include caixa1.C

            \pre V.

            \post dimensao = dimensão do ecrã real. */
        Dimensao const dimensao() const;

        /** Devolve a posição da origem do ecrã real no ecrã virtual.
	    De momento devolve sempre (0, 0).

            \pre V.

            \post origem = origem do ecrã real, de momento sempre (0,
            0). */
        Posicao const origem() const;

        /** Devolve a posição do extremo do ecrã real no ecrã virtual.
	    De momento devolve sempre dimensao() - Dimensao(1, 1).

            \pre V.

            \post extremo = extremo do ecrã real, de momento sempre
            (dimensao().numeroDeLinhas() - 1,
            dimensao().numeroDeColunas() - 1). */
        Posicao const extremo() const;

        /** Devolve a posição corrente do cursor.

	    O programa de exemplo abaixo permite deslocar o cursor de acordo
	    com as teclas premidas, dizendo em cada instante se o cursor se
	    encontra dentro ou fora do ecrã.  Para isso recorre à operação
	    posicaoDoCursor(), pois precisa de recolocar o cursor depois de
	    uma operação de escrita:

	    \include ecra3.C

            \pre V.

            \post posicaoDoCursor = posição corrente do cursor. */
        Posicao const posicaoDoCursor() const;

	/** Devolve a justificação actual das inserções no ecrã.

	    \pre V.
	
	    \post justificacaoActual = justificação actual do ecrã. */
        Justificacao justificacaoActual() const;

	/** Devolve a largura a usar na próxima inserção no ecrã.  Note-se que
	    o valor 0 significa que não se usa largura na inserção.

	    \pre V.
	
	    \post larguraDaProximaOperacaoDeEscrita = largura a usar na
	    próxima inserção no ecrã. */
        int larguraDaProximaOperacaoDeEscrita() const;

        //@}

        ///@name Predicados
        //@{

        /** Indica se o ecrã real foi redimensionado ou não.  Isto é
	    particularmente relevante se o programa estiver a correr
	    numa consola dentro de um ambiente de janelas.  Nessas
	    circunstâncias o utilizador pode alterar a dimensão da
	    janela, sendo com isso alterada a dimensão do ecrã.  Se
	    isso acontecer o programa deverá redesenhar e refrescar o
	    ecrã.  Note-se que conceptualmente este predicado pode
	    mudar de valor devolvido sem que tenha sido invocado
	    nenhum modificador.  Note-se ainda que logo após devolver
	    verdadeiro devolverá falso até ocorrer novo
	    redimensionamento.

	    É esta operação que permite ao programa

	    \include ecra3.C

	    adaptar-se a alterações na dimensão do ecrã real.

	    \pre V.

	    \post foiRedimensionado = ecrã real foi redimensionado
	    deste a construção do ecrã ou desde a última invocação do
	    predicado e não redimensionado.  */
        bool foiRedimensionado() const;

	/** Indica se o cursor está sobre o ecrã real, i.e., se o cursor é
	    visível.  Note-se que quando o cursor está "invisível" é um seu
	    "fantasma" visível no ecrã real.  A biblioteca S-Lang não permite
	    ocultar este "fantasma", infelismente.

	    Na documentação de posicaoDoCursor() encontra-se um programa de
	    exemplo que faz uso deste predicado.

	    \pre V.
	
	    \post cursorEstaVisivel = parteVisivelContem(posicaoDoCursor()). */
        bool cursorEstaVisivel() const;

	/** Indica se uma posição está sobre o ecrã real, i.e., se a parte
	    visível do ecrã contém essa posição.

	    \pre V.
	
	    \post parteVisivelContem = Caixa(origem(),
	    extremo()).contem(posicao). */
        bool parteVisivelContem(Posicao const& posicao) const;

	/** Indica se o cursor está limitado ao ecrã real, i.e., se o ecrã
	    proíbe o cursor de se deslocar para fora da sua parte visível.
	
	    \pre V.

	    \post cursorEstaLimitadoAoEcraReal = cursor está proibído de
	    abandonar a parte visível do ecrã. */
        bool cursorEstaLimitadoAoEcraReal() const;

	/** Indica se o cursor ficará imóvel na próxima operação de inserção.
	
	    \pre V.

	    \post cursorImovelNaProximaOperacaoDeInsercao = cursor ficará
	    imóvel na próxima operação de inserção. */
        bool cursorImovelNaProximaOperacaoDeInsercao() const;

        //@}

        ///@name Modificadores
        //@{

	/** Muda a justificação do ecrã para a justificação dada.  A
	    justificação mantém-se até à próxima alteração.

	    \pre V.

	    \post justificacaoActual() = nova_justificacao */
	void mudaJustificacaoPara(Justificacao const nova_justificacao);

	/** Coloca o ecrã num estado tal que a próxima operação de
	    inserção não tem efeito sobre a posição do cursor.

	    \pre V.

	    \post cursorImovelNaProximaOperacaoDeInsercao(). */
	void impoeImobilidadeDoCursorNaProximaInsercao();

	/** Coloca o ecrã num estado tal que a próxima operação de
	    inserção será feita usando exactamente \a
	    largura_da_proxima_operacao_de_escrita células do ecrã.

	    \pre 0 <= largura_da_proxima_operacao_de_escrita.

	    \post LarguraDaProximaOperacaoDeEscrita() = \a
	    largura_da_proxima_operacao_de_escrita

	    \see largura() */
	void mudaLarguraDaProximaOperacaoDeEscritaPara
	(int const largura_da_proxima_operacao_de_escrita);

	/** Muda o objecto cor em uso para \a objecto_cor.  Útil para
	    alterar as cores das próximas inserções no ecrã.
	    Normalmente usa-se o correspondente operador de inserção
	    para obter o mesmo efeito.  As duas formas de utilização de
	    objectos cor estão demonstradas no programa de exemplo abaixo:

	    \include objectocor1.C

	    \pre V.

	    \post As próximas inserções passarão a ser realizadas
	    usando o objecto cor \a objecto_cor. */
	void mudaObjectoCorEmUsoPara(ObjectoCor const& 
				     objecto_cor);

	/** Muda o objecto cor em uso para o objecto cor do fundo.
	    Útil para que as próximas inserções sejam feitas como
	    células do fundo.

	    Veja-se o exemplo na documentação da operação
	    mudaObjectoCorEmUsoPara().

	    \pre V.

	    \post As próximas escritas passarão a ser realizadas
	    usando o objecto cor do fundo. */
	void mudaObjectoCorEmUsoParaFundo();

        /** Modifica as cores das células do fundo.  Útil para
	    modificar o aspecto do fundo mesmo quando não se tem
	    acesso ao construtor do ecrã.

	    Um exemplo de utilização desta operação pode ser visto abaixo:

	    \include ecra4.C

            \pre V. 

	    \post Células desenhadas com o objecto cor do fundo serão
	    desenhadas com as cores dadas. */
        void mudaCoresDasCelulasDoFundoPara(Cor const cor_do_texto, 
					    Cor const cor_do_fundo);

        /** Desloca o cursor para a posição dada.

            \pre V.

            \post posicaoDoCursor() = nova_posicao_do_cursor (mas
            limitada ao ecrã real se se optou por limitar o
            posicionamento do cursor). */
        void moveCursorPara(Posicao const& nova_posicao_do_cursor);

        /** Sobe o cursor uma linha.

            \pre p = posicaoDoCursor().

            \post posicaoDoCursor() = p - Dimensao(1, 0) (mas limitada
            ao ecrã real se se optou por limitar o posicionamento do
            cursor). */
        void sobeCursor();

        /** Baixa o cursor uma linha.

            \pre p = posicaoDoCursor().

            \post posicaoDoCursor() = p + Dimensao(1, 0) (mas limitada
            ao ecrã real se se optou por limitar o posicionamento do
            cursor). */
        void baixaCursor();

        /** Recua o cursor uma coluna (para a esquerda).

            \pre p = posicaoDoCursor().

            \post posicaoDoCursor() = p - Dimensao(0, 1) (mas limitada
            ao ecrã real se se optou por limitar o posicionamento do
            cursor). */
        void recuaCursor();

        /** Avança o cursor uma coluna (para a direita).

            \pre p = posicaoDoCursor().

            \post posicaoDoCursor() = p + Dimensao(0, 1) (mas limitada
            ao ecrã real se se optou por limitar o posicionamento do
            cursor). */
        void avancaCursor();

        /** Desloca o cursor na direcção dada por uma tecla de
	    deslocamento.

            \pre tecla.eDeslocamento() e p = posicaoDoCursor().

            \post (posicaoDoCursor() = p - Dimensao(1, 0) e tecla =
            Tecla::cima) ou (posicaoDoCursor() = p + Dimensao(1, 0) e
            tecla = Tecla::baixo) ou (posicaoDoCursor() = p -
            Dimensao(0, 1) e tecla = Tecla::esquerda) ou
            (posicaoDoCursor() = p + Dimensao(0, 1) e tecla =
            Tecla::direita) (mas limitada ao ecrã real se se optou por
            limitar o posicionamento do cursor). */
        void moveCursorDeAcordoCom(Tecla const& tecla);

        //@}

        ///@name Operações para cópia e cola de troços de ecrã
        //@{

        /** Devolve um troço do ecrã correspondente à caixa dada. 

	    Um exemplo de utilização pode ser encontrado em:
	    
	    \include ecra2.C

	    \pre caixa.eCanonica().

	    \post trocoDe = troço representando a cópia da zona do
	    ecrã correspondendo a \a caixa. */
        Troco const trocoDe(Caixa const& caixa) const;

        /** Devolve uma cópia integral do ecrã real.

	    \pre V.

	    \post trocoDoEcraCompleto = troço representando a cópia do ecrã
	    real completo. */
        Troco const trocoDoEcraCompleto() const;

        /** Devolve uma cópia do troço de ecrã com uma dada dimensão e
            com origem na posição corrente do cursor.

	    \pre dimensao.eCanonica().

	    \post trocoNoCursorCom = troço representando a cópia da zona do
	    ecrã com origem em posicaoDoCursor() e dimensão \a dimensao. */
        Troco const trocoNoCursorCom(Dimensao const& dimensao) const;

        /** Cola no ecrã, na posição indicada (por omissão o canto
            superior esquerdo do ecrã), um troço de ecrã.  O cursor é
            deslocado para a posição imediatamente após a última
            coluna da última linha onde o troço foi colocado, a não
            ser que se tenha pedido para manter o cursor parado.
            Atenção!  O objecto cor que estava a ser usado antes da
            colagem é perdido!  As próximas escritas são feitas usando
            a cor do fundo.

	    \pre V.

	    \post ecrã contém cópia do troço \a troco a partir da
	    posição \a em, ficando o cursor na posição imediatamente
	    após a última coluna da última linha onde o troço foi
	    colocado (mas limitada ao ecrã real se se optou por
	    limitar o posicionamento do cursor), excepto se o cursor
	    tiver de ficar parado.

            \see parado */
        void cola(Troco const& troco, 
		  Posicao const& em = Posicao());

        //@}

        ///@name Operações para actualizar o ecrã
        //@{

        /** Toca a "campaínha" do ecrã.  Por vezes o ecrã pisca, embora não
	    seja nunca alterado.  Por exemplo:

	    \include campainha1.C

	    \pre V.

	    \post Uma campaínha soou. */
        void tocaCampainha() const;

        /** Apaga (i.e., pinta com cor do fundo) desde o cursor até ao
            fim da respectiva linha.

	    \pre V.

	    \post ecrã "vazio" entre posicaoDoCursor() e o final da
	    respectiva linha. */
        void apagaDoCursorAteOFimDaLinha(); 

        /** Apaga (i.e., pinta com cor do fundo) desde o cursor até ao
            fim do ecrã.

	    \pre V.

	    \post ecrã vazio entre posicaoDoCursor() e o final do
	    ecrã. */
        void apagaDoCursorAteOFim();

        /** Apaga (i.e., pinta com cor do fundo) todo o ecrã.

	    \pre V.

	    \post ecrã vazio. */
        void apaga();

        /** Refresca o ecrã, ou seja, reflecte no ecrã real as últimas
            alterações realizadas no ecrã virtual.

	    \pre V.

	    \post Ecrã real reflecte exactamente a parte
	    correspondente do ecrã virtual. */
        void refresca() const;

        /** Refresca totalmente o ecrã, ou seja, reflecte no ecrã real
            todo o ecrã virtual.  O efeito deve ser semelhante ao
            obtido pela operação refresca(), só diferindo em caso de
            erro do sistema.  Útil para tentar ultrapassar erros de
            programação, fornecendo-se ao utilizador uma forma de
            refrescar o ecrã inteiro.

	    \pre V.

	    \post Ecrã real reflecte exactamente a parte
	    correspondente do ecrã virtual. */
        void refrescaTudo() const;

        /** Desenha uma caixa no ecrã, sendo a borda desenhada com
            caracteres especiais.  O interior da caixa não é
            alterado. O cursor é colocado na célula imediatamente à
            direita do canto inferior direito da caixa (mas limitado
            ao ecrã real se se optou por limitar o posicionamento do
            cursor), excepto se se tiver optado por fixar o cursor.

	    O mesmo efeito pode ser obtido inserindo a caixa no ecrã.
	    Veja-se o exemplo na documentação da classe Caixa.
            
	    \pre caixa.eCanonica().
	    
	    \post ecrã contém caracteres desenhando uma caixa nas
	    posições correspondentes à borda de \a caixa e o cursor está
	    colocado na célula imediatamente à direita do canto
	    inferior direito da caixa (mas limitado ao ecrã real se se
	    optou por limitar o posicionamento do cursor), excepto se
	    se tiver optado por fixar o cursor. */
        void desenha(Caixa const& caixa);

	/** Desenha um segmento de recta horizontal, com a largura dada, a
	    partir da posição do cursor (para a direita).

	    Veja-se um exemplo de utilização na documentação do manipulador
	    segmento_horizontal().

	    \pre 0 <= largura
	
	    \post Ecrã contém segmento de recta horizontal com a largura dada
	    e o cursor está colocado na célula imediatamente à direita do
	    extremo direito do segmento (mas limitado ao ecrã real se se optou
	    por limitar o posicionamento do cursor), excepto se se tiver
	    optado por fixar o cursor. 

	    \see segmento_horizontal() */
	void desenhaSegmentoHorizontalCom(int const largura);

	/** Desenha um segmento de recta vertical, com a altura dada, a
	    partir da posição do cursor (para baixo).

	    Veja-se um exemplo de utilização na documentação do manipulador
	    segmento_horizontal().

	    \pre 0 <= altura
	
	    \post Ecrã contém segmento de recta vertical com a altura dada e o
	    cursor está colocado na célula imediatamente abaixo do extremo
	    inferior do segmento (mas limitado ao ecrã real se se optou por
	    limitar o posicionamento do cursor), excepto se se tiver optado
	    por fixar o cursor. */
	void desenhaSegmentoVerticalCom(int const altura);
        //@}

        ///@name Operadores de inserção no ecrã de tipos usuais
        //@{

        /** Insere uma cadeia de caracteres na posição do cursor.  O
            cursor é deslocado para a posição à direita do último
            caractere escrito (mas limitado ao ecrã real se se optou
            por limitar o posicionamento do cursor)., a não ser que se
            tenha pedido para manter o cursor parado.  Se se tiver
            especificado uma largura antes, são acrescentados espaços
            até perfazer a largura indicada.  Se a cadeia for maior
            que a largura especificada, só são mostrados os primeiros
            caracteres. Os espaços são inseridos à esquerda, à direita
            ou de ambos os lados, consoante o tipo de justificação em
            vigor no ecrã.

	    \pre V.

	    \post (ver descrição acima).

	    \see parado 

	    \see largura 

	    \see Justificacao */
        Ecra& operator<<(std::string const& cadeia);

        /** Insere um valor do tipo T genérico na posição do cursor.  O efeito
	    é idêntico ao do operador<< para cadeias de caracteres.  O tipo T
	    do valor inserido tem de ter o operador << disponível para
	    inserções em canais \a ostream (ou pelo menos \a ostringstream).

	    \pre V.

	    \post (ver descrição acima). */
	template <typename T>
	Ecra& operator<<(T const& valor);

        //@}

        /**@name Operadores de inserção e extracção de objectos especiais no
	   ecrã */
        //@{

        /** Desenha uma caixa no ecrã.  Efeito equivalente ao da
            operação desenha(Caixa).

	    Veja-se o exemplo na documentação da classe Caixa.

	    \pre caixa.eCanonica().

	    \post Ver descrição de desenha(). */
        Ecra& operator<<(Caixa const& caixa);

        /** Desenha um símbolo especial no ecrã. 

	    Veja-se um exemplo de utilização na classe Simbolo.

	    \pre V.

	    \post ecrã contém o símbolo simbolo a partir da posição do
	    cursor (ver descrição de operador << para cadeias de
	    caracteres), avançando o cursor para a posição à sua
	    direita (mas limitado ao ecrã real se se optou por limitar
	    o posicionamento do cursor).

            \see Simbolo */
        Ecra& operator<<(Simbolo const simbolo);

        /** Cola no ecrã, na posição do cursor, um troço de ecrã.  O
            cursor é deslocado para a posição imediatamente após a
            última coluna da última linha onde o troço foi colocado
            (mas limitado ao ecrã real se se optou por limitar o
            posicionamento do cursor), a não ser que se tenha pedido
            para manter o cursor parado.  Atenção!  O objecto cor que
            estava a ser usado antes da colagem é perdido!  As
            próximas escritas são feitas usando a cor do fundo.

	    Veja-se um exemplo de utilização na documentação da operação
	    trocoDe().

	    \pre V.

	    \post ecrã contém cópia do troço \a troco a partir da
	    posição \a em, ficando o cursor na posição imediatamente
	    após a última coluna da última linha onde o troço foi
	    colocado (mas limitado ao ecrã real se se optou por
	    limitar o posicionamento do cursor), excepto se o cursor
	    tiver de ficar parado.

            \see parado 

	    \see cola */
        Ecra& operator<<(Troco const& troco);

        //@}

        ///@name Operadores de extracção de objectos especiais do ecrã
        //@{

        /** Extrai um troço do ecrã a partir da posição actual do
	    cursor.

	    \pre V.

	    \post \a troco é cópia da zona do ecrã começando na
	    posição actual do cursor e com dimensão
	    troco.dimensao(). 

	    \see trocoDe() */
        Ecra const& operator>>(Troco& troco) const;

        //@}

        /**@name Operadores de inserção de manipuladores no ecrã

	   Veja-se a descrição dos correspondentes manipuladores, onde
	   se explica o respectivo efeito. */
        //@{

        /** Altera a posição do cursor para a posição dada (mas
	    limitada ao ecrã real se se optou por limitar o
	    posicionamento do cursor).

	    \pre V.  

	    \post posicaoDoCursor() = nova_posicao_do_cursor (mas
	    limitada ao ecrã real se se optou por limitar o
	    posicionamento do cursor).

	    \see cursor

	    \see moveCursorPara() */
        Ecra& operator<<(Posicao const& nova_posicao_do_cursor);

        /** Altera o objecto cor das próximas operações de inserção no
            ecrã (com excepção das colagens!).

	    Um exemplo de utilização pode ser encontrado na documentação da
	    operacao mudaObjectoCorEmUsoPara().

	    \pre V.

	    \post Próximas inserções no ecrã (excepto colagens) serão
	    feitas usando o objecto cor passado.

	    \see mudaObjectoCorEmUsoPara() */
        Ecra& operator<<(ObjectoCor const& objecto_cor);

	/** Muda a justificação do ecrã para a justificação dada.  A
	    justificação mantém-se até à próxima alteração.

	    \pre V.

	    \post justificacaoActual() = justificacao das inserções no ecrã em
	    vigor. */
	Ecra& operator<<(Justificacao const nova_justificacao);

	/** "Gancho" para definir novos manipuladores do ecrã.  Um novo
	    manipulador consegue-se facilmente definindo um procedimento que
	    receba um ecrã por referência.  Esse procedimento será invocado
	    automaticamente quando for inserido no ecrã através do operador
	    <<.

	    O exemplo abaixo demonstra como se pode definir um manipulador
	    para deslocar o cursor para uma posição aleatória do ecrã real:

	    \include manipulador1.C
	    
	    \pre V.

	    \post O efeito é o mesmo de invocar manipulador(*this). */
	Ecra& operator<<(void manipulador(Ecra& ecra));

	//@}

    private:
        bool cursor_esta_limitado_ao_ecra_real;

        mutable bool redimensionado_;

        bool cursor_imovel_na_proxima_operacao_de_escrita;

        Justificacao justificacao_actual;

        int largura_da_proxima_operacao_de_escrita;

        std::vector<int> ocupacao_dos_objectos;

        static bool ja_existe_instancia;

	// Variável alterada pelo manipulador do sinal SIGWINCH
	// (SIGnal WINdow CHanged):
        static volatile bool tamanho_do_ecra_real_mudou;

        static char *nome_de_cor_do_s_lang[numero_de_cores];

        // Assim ninguém pode invocar o construtor por cópia...
        Ecra(Ecra const&);

        // ...nem a atribuição por cópia:
        Ecra& operator = (Ecra const&);

        // Coloca atributos num dado objecto:
        void mudaCoresDe(int const objecto, 
			 Cor const cor_do_texto, Cor const cor_do_fundo);

        // Verifica se a dimensão do ecrã real sofreu alterações:
        void verificaRedimensionamento() const;

        // Só os membros da classe podem posicionar o cursor sem que
        // isso seja considerado uma alteração.  Quando o fizerem têm
        // de se responsabilizar por voltar a por o cursor na posição
        // original.
        void moveCursorPara(Posicao const& posicao) const;

        // Usados pelos objectos cor para reservar ou libertar um
        // lugar na palete:
        int reservaObjecto();
        void libertaObjecto(int const numero_do_objecto);

	// Manipulador do sinal SIGWINCH:
        static void manipuladorDeRedimensionamento(int sinal);

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = V. */
	bool cumpreInvariante() const;

        // Amizades:
        friend class ObjectoCor;
    };

    /** \class Ecra::ObjectoCor ecra.H Slang++/ecra.H

        Esta classe é usada para indicar a cor das células do ecrã (as células
        têm uma cor de texto e outra de fundo).  O sistema usado pela
        biblioteca C S-Lang (base desta biblioteca \c Slang++) é complicado
        pelo facto de se basear no conceito de palete.  A ideia é que se deve
        usar um objecto cor para reservar uma posição da palete.  Todas as
        células escritas usando este objecto cor guardarão na realidade uma
        referência para o respectivo objecto cor.  Assim, se se alterar a cor
        do texto ou do fundo desse objecto cor, mudará a cor de todas as
        respectivas células!  Note-se que, devido a limitações da biblioteca
        de base que está a ser usada (C S-Lang), o número de objectos cor
        definidos em cada momento não deverá ultrapassar os 255!  Se isso
        acontecer, as cores deixarão de poder ser alteradas independentemente,
        com resultados muito estranhos...  Note-se ainda que nem todas as
        cores são utilizáveis como cor de fundo em todas as consolas.
        Infelizmente a biblioteca S-Lang não permite detectar este problema.

        Os objectos cor não são copiáveis!  Este facto deve-se a que
        cada objecto criado ocupa um posição da palete.  Assim, não é
        possível passar um objecto cor como argumento para uma função
        ou procedimento, excepto por referência.

        O ecrã tem sempre uma cor activa (nem que seja a cor do fundo
        do ecrã que por omissão é de texto branco sobre fundo preto).

        Pode-se mudar a cor activa de várias maneiras, por exemplo
        usando o operador Ecra::operator<<(ObjectoCor const&) do seguinte
        modo:

        \code
        Ecra::ObjectoCor cor(vermelho / * texto * /, verde / * fundo * /); 
        ecra << cor;
        \endcode

        A partir desta instrução tudo que for inserido ficará vermelho sobre
        verde até que a cor seja mudada de novo.  Note-se que é recomendável
        que a variável \a cor persista enquanto existirem no ecrã células
        desenhadas com recurso a essa cor, pois de outra forma a construção de
        um novo objecto cor poderá ocupar a mesma posição na palete, alterando
        a côr das respectivas células do ecrã.
        
        Após uma colagem de um troço de ecrã copiado previamente a cor activa
        volta a ser a do fundo do ecrã. Espera-se que um dia esta restrição
        venha a ser eliminada.
        
        A escolha das cores utilizadas num programa deve ter sempre
        como objectivo tornar tão clara quanto possível a utilização
        do programa. Não se deve usar todas as cores disponíveis
        apenas "porque estão lá".  Deve-se também também ter o cuidado
        de escolher cores de fundo e de texto que sejam minimamente
        contrastantes de modo a que o utilizador perceba bem o que
        está no ecrã.

	Os efeitos estranhos associados ao modelo de cor usado podem ser
	confirmados através exemplos que se seguem.

	O primeiro exemplo demonstra o efeito dos tempos de vida dos objectos
	cor:

	\include objectocor2.C

	O segundo exemplo demonstra o efeito de alterar as cores de um objecto
	cor sobre as células do ecrã que com ele tenham sido previamente
	desenhadas:

	\include objectocor3.C

	\invariant 1 <= numero_do_objecto < numero_de_objectos_cor_no_s_lang.

	\ingroup ecras

        \todo Faltam as operações carregaDe() e guardaEm().

        \todo Dever-se-ia gerir melhor as posições da palete. */
    class Ecra::ObjectoCor {
    public:
        /** Constrói um novo objecto cor com as cores dadas.  Ocupa uma
            posição da palete disponível.  Se não houver nenhuma, passa a
            partilhar uma posição já ocupada, o que resulta em efeitos
            estranhos.  Na prática nunca acontece, pois programas em modo
            texto não têm nunca mais de 256 cores...

            \pre V.

	    \post corDoTexto() = cor_do_texto e corDoFundo() =
	    cor_do_fundo. */
        ObjectoCor(Cor const cor_do_texto, Cor const cor_do_fundo);
        
        /** Destrói um objecto cor, libertando a respectiva posição na palete
	   (ou pelo menos reduzindo o seu grau de partilha).

	   \pre V. */
        ~ObjectoCor();

        ///@name Inspectores
        //@{

        /** Devolve a cor do texto corrente deste objecto cor.

	    \pre V.

	    \post corDoTexto = cor do texto corrente do objecto cor. */
        Cor corDoTexto() const;

        /** Devolve a cor do fundo corrente deste objecto cor.

	    \pre V.

	    \post corDoTexto = cor do fundo corrente do objecto cor. */
        Cor corDoFundo() const;

        //@}

        ///@name Modificadores
        //@{

        /** Modifica a cor do texto corrente deste objecto cor.  Afecta todas
	    as células do ecrã desenhadas com este objecto cor.

	    \pre V.

	    \post corDoTexto() = nova_cor_do_texto. */
        void mudaCorDoTextoPara(Cor const nova_cor_do_texto);

        /** Modifica a cor do fundo corrente deste objecto cor.  Afecta todas
	    as células do ecrã desenhadas com este objecto cor.

	    \pre V.

	    \post corDoFundo() = nova_cor_do_fundo. */
        void mudaCorDoFundoPara(Cor const nova_cor_do_fundo);

        //@}

    private:
	static int const numero_de_objectos_cor_no_s_lang = 256;

        // Não se podem copiar estes objectos!
        ObjectoCor(ObjectoCor const&);
        ObjectoCor& operator=(ObjectoCor const&);

        Cor cor_do_texto;
        Cor cor_do_fundo;
        int numero_do_objecto;	// entrada na palete.

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = 1 <= numero_do_objecto <
	    numero_de_objectos_cor_no_s_lang. */
	bool cumpreInvariante() const;

        // A classe Ecra precisa de aceder ao número do objecto:
        friend class Ecra;
    };

    /** \class Ecra::Troco ecra.H Slang++/ecra.H

        Esta classe serve para representar um troço de ecrã.  Os
        troços de ecrã são úteis para guardar partes do ecrã, que mais
        tarde podem ser desenhados onde se entender.

        Uma variável do tipo Troco (leia-se "troço") guarda uma parte do ecrã
        com todas as suas propriedades (i.e., caracteres e cores (do texto e
        do fundo) de todas as células de uma zona, ou trço, rectangular do
        ecrã. Esta classe é especialmente útil em operações como cortar e
        colar (<em>copy & paste</em>) para guardar a parte do ecrã que se
        pretende reproduzir e depois pôr este mesmo troço de ecrã noutra ou na
        mesma posição.

        \b Exemplo

        O seguinte programa demonstra a utilização de troços de ecrã:

	\include ecra2.C

	\invariant dimensao_.numeroDeLinhas() * dimensao_.numeroDeColunas() =
	dados.size().

	\ingroup ecras */
    class Ecra::Troco {
    public:
        /** Constrói um novo troço.  É pouco usual ser usado directamente.
            Normalmente é a própria classe ecrã que constrói o troço e o
            devolve, por exemplo através da operação Ecra::trocoDe() (e
            portanto o construtor mais usado é o construtor por cópia).

            \pre dimensao.eCanonica().
	
	    \post *this é um troço com a dimensão indicada, embora vazio. */
        explicit Troco(Dimensao const& dimensao);

        /** Devolve a dimensão do troço.

	    \pre V.

	    \post dimensao = dimensão do troço. */
        Dimensao dimensao() const;

    private:
        Dimensao dimensao_;
        std::vector<unsigned short> dados;

	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = dimensao_.numeroDeLinhas() *
	    dimensao_.numeroDeColunas() = dados.size(). */
	bool cumpreInvariante() const;

        // A classe Ecra precisa de acesso a dados privados desta
        // classe.
        friend class Ecra;
    };


    /** Uma variável global representando o ecrã.  A ideia é que
        substitua a variável global cout usada normalmente para
        escrever no ecrã.  É através desta variável que se procede a todas as
        inserções no ecrã.

        \ingroup ecras */
    extern Ecra ecra;


    // Classes auxiliares para manipuladores:

    /** Não usar directamente.

        \see Slang::largura() */
    struct ManipuladorDaLargura {
        explicit ManipuladorDaLargura(int const largura = 0); 

        int largura;
    };
    
    /** Não documentada.

        \see Slang::largura() */
    Ecra& operator<<(Ecra& ecra, 
		     ManipuladorDaLargura const& manipulador);

    /** Não usar directamente.

        \see Slang::segmento_horizontal()
        \see Slang::segmento_vertical() */
    struct ManipuladorDeDesenhoDeSegmento {
        explicit ManipuladorDeDesenhoDeSegmento(bool const e_horizontal, 
						int const dimensao = 1); 

        bool e_horizontal;
        int dimensao;
    };

    /** Não documentada.

        \see Slang::segmento_horizontal()
        \see Slang::segmento_vertical() */
    Ecra& operator<<(Ecra& ecra, 
		     ManipuladorDeDesenhoDeSegmento const& manipulador);


    /**@name Manipuladores do ecrã
       \ingroup ecras */
    //@{

    /** Manipulador usado para colocar o cursor numa dada posição.
        Usar como se segue:

        \code
        // Coloca cursor na linha 10 coluna 20 do ecrã:
        ecra << cursor(10, 20);

        // Escreve "Olá mundo!" a partir dessa posição:
        ecra << "Olá mundo";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::moveCursorPara() */
    Posicao const cursor(int const linha, int const coluna);

    /** Manipulador usado para colocar o cursor numa dada posição.
        Usar como se segue:

        \code
	// Definição de uma posicão:
	Posicao posicao(10, 20);

        // Coloca cursor na posição do ecrã definida:
        ecra << cursor(posicao);

        // Escreve "Olá mundo!" a partir dessa posição:
        ecra << "Olá mundo";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

	embora fosse mais simples omitir a utilização do manipulador,
	inserindo directamente a posição no ecrã:

        \code
	// Definição de uma posicão:
	Posicao posicao(10, 20);

        // Coloca cursor na posição do ecrã definida:
        ecra << posicao;

        // Escreve "Olá mundo!" a partir dessa posição:
        ecra << "Olá mundo";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

	que ainda pode ser simplificado para:

        \code
	// Coloca cursor na posição do ecrã definida:
        ecra << Posicao(10, 20);

        // Escreve "Olá mundo!" a partir dessa posição:
        ecra << "Olá mundo";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::moveCursorPara() */
    Posicao const& cursor(Posicao const& posicao);

    /** Manipulador usado para desenhar uma caixa com caracteres especiais
        numa dada posição e com uma dada dimensão.  Usar como se segue:

        \code
        // Desenha caixa com origem na linha 10 coluna 20 com 5 linhas e 15
        // colunas:
        ecra << caixa(10, 20, 5, 15);

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::desenha() */
    Caixa const caixa(int const linha, int const coluna, 
		      int const numero_de_linhas, int const numero_de_colunas);

    /** Manipulador usado para desenhar uma caixa com caracteres especiais
        numa dada posição e com uma dada dimensão.  Usar como se segue:

        \code
	// Definição de uma posição e uma dimensão para a caixa:
	Posicao posicao(10, 20);
	Dimensao dimensao(5, 15);

        // Desenha caixa com a posição e dimensão definidas:
        ecra << caixa(posicao, dimensao);

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

	Neste caso poder-se-ia ter omitido o manipulador, usando-se em vez
	dele o construtor da classe Caixa, que se pode inserir num ecrã:

        \code
	// Definição de uma posição e uma dimensão para a caixa:
	Posicao posicao(10, 20);
	Dimensao dimensao(5, 15);

        // Desenha caixa com a posição e dimensão definidas:
        ecra << Caixa(posicao, dimensao);

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 
	
        \see Ecra::desenha() */
    Caixa const caixa(Posicao const& origem = Posicao(), 
		      Dimensao const& dimensao = Dimensao());
    
    /** Manipulador usado para indicar que as próximas escritas devem
        ser realizadas usando a cor do fundo do ecrã.  Usar como se
        segue:

        \code
        // Coloca cursor no canto superior esquerdo do ecrã:
        ecra << cursor(0, 0);

        // Define objecto cor para a próxima escrita:
        Ecra::ObjectoCor cor(amarelo, vermelho);

        // Escreve "Olá mundo! " usando a cor indicada:
        ecra << oor << "Olá mundo! ";

        // Escreve "Olá mundo!" mas usando a cor do fundo:
        ecra << fundo << "Olá mundo!";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

	\see Ecra::mudaObjectoCorEmUsoParaFundo(). */
    void fundo(Ecra& ecra);

    /** Manipulador usado para manter o cursor na posição corrente durante a
        próxima operação de inserção no ecrã.  Usar como se segue:

        \code
        // Coloca cursor no canto superior esquerdo do ecrã:
        ecra << cursor(0, 0);

        // Escreve "Olá mundo!" mantendo a posição do cursor no topo superior
        // esquerdo do ecrã:
        ecra << parado << "Olá mundo!";

        // Refresca o ecrã:
        ecra << refresca;
	\endcode

	\see Ecra::impoeImobilidadeDoCursorNaProximaInsercao() */
    void parado(Ecra& ecra);

    /** Manipulador usado para subir o cursor no ecrã.  Usar como se segue:

        \code
        // Coloca cursor a meio do ecrã, à esquerda:
        ecra << cursor(ecra.dimensao().numeroDeLinhas() / 2, 0);

        // Escreve "mundo!" mantendo a posição do cursor:
        ecra << parado << "mundo!";

	// Sobe cursor para a linha acima:
	ecra << sobeCursor;

        // Escreve "Olá" mantendo a posição do cursor:
        ecra << parado << "Olá";

        // Refresca o ecrã:
        ecra << refresca;
	\endcode

	\see Ecra::sobeCursor() */
    void sobeCursor(Ecra& ecra);

    /** Manipulador usado para baixar o cursor no ecrã.  Usar como se segue:

        \code
        // Coloca cursor a meio do ecrã, à esquerda:
        ecra << cursor(ecra.dimensao().numeroDeLinhas() / 2, 0);

        // Escreve "Olá" mantendo a posição do cursor:
        ecra << parado << "Olá";

	// Baixa o cursor:
	ecra << sobeCursor;

        // Escreve "mundo!" mantendo a posição do cursor:
        ecra << parado << "mundo!";

        // Refresca o ecrã:
        ecra << refresca;
	\endcode

	\see Ecra::baixaCursor() */
    void baixaCursor(Ecra& ecra);

    /** Manipulador usado para recuar o cursor no ecrã.  Usa-se como os
	manipuladores sobeCursor() e baixaCursor().

	\see Ecra::recuaCursor() */
    void recuaCursor(Ecra& ecra);

    /** Manipulador usado para avançar o cursor no ecrã.  Usa-se como os
	manipuladores sobeCursor() e baixaCursor().

	\see Ecra::avancaCursor() */
    void avancaCursor(Ecra& ecra);

    /** Manipulador usado para indicar o número de células do ecrã a
        ocupar na próxima operação de inserção no ecrã.  Usar como se segue:

        \code
        // Coloca cursor no canto superior esquerdo do ecrã:
        ecra << cursor(0, 0);

        // Define objecto cor para a próxima escrita:
        Ecra::ObjectoCor cor(amarelo, vermelho);

        // Escreve "Olá mundo! " usando a cor indicada e centrados em 30
        // caracteres:
        ecra << oor << ao_centro << largura(30) << "Olá mundo!";
        \endcode 

	\pre 0 <= largura

	\see Ecra::mudaLarguraDaProximaOperacaoDeEscritaPara() */
    ManipuladorDaLargura largura(int const largura);

    /** Manipulador usado para desenhar um segmento de recta horizontal.  

	Veja-se um exemplo de utilização no programa abaixo:
	
	\include segmentos1.C

	\pre 0 <= largura

	\see Ecra::desenhaSegmentoHorizontalCom() */
    ManipuladorDeDesenhoDeSegmento segmento_horizontal(int const largura);

    /** Manipulador usado para desenhar um segmento de recta vertical.  

        Veja-se uma exemplo de utilização na documentação do manipulador
        segmento_horizontal().

	\pre 0 <= largura

	\see Ecra::desenhaSegmentoVerticalCom() */
    ManipuladorDeDesenhoDeSegmento segmento_vertical(int const altura);

    /** Manipulador usado para refrescar o ecrã.  Usado como
        se segue:

        \code
        // Coloca cursor no canto superior esquerdo do ecrã:
        ecra << cursor(0, 0);

        // Escreve "Olá mundo!" a partir dessa posição:
        ecra << "Olá mundo";

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::refresca() */
    void refresca(Ecra& ecra);

    /** Manipulador usado para fazer o refrescamento total do ecrã.
        Usado como se segue:

        \code
        ecra << refresca_tudo;
        \endcode 

        \see Ecra::refrescaTudo() */
    void refresca_tudo(Ecra& ecra);

    /** Manipulador usado para apagar o ecrã (ou seja, para o pintar
        com a cor do fundo).  Usar como se segue:

        \code
	// Apaga o ecrã:
        ecra << apaga;

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::apaga() */
    void apaga(Ecra& ecra);

    /** Manipulador usado para apagar até ao fim da linha do cursor
        (ou seja, para o pintar com a cor do fundo).  Usar como se
        segue:

        \code
        // Apaga linha 10 a partir da coluna 20:
        ecra << cursor(10, 20) << apaga_fim_da_linha;

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::apagaDoCursorAteOFimDaLinha() */
    void apaga_fim_da_linha(Ecra& ecra);

    /** Manipulador usado para apagar desde a posição do cursor até ao fim do
        ecrã (ou seja, para o pintar com a cor do fundo).  Usar como se segue:

        \code
        // Apaga ecrã a partir da coluna 20 da linha 10:
        ecra << cursor(10, 20) << apaga_fim_do_ecra;

        // Refresca o ecrã:
        ecra << refresca;
        \endcode 

        \see Ecra::apagaDoCursorAteOFim() */
    void apaga_fim_do_ecra(Ecra& ecra);

    /** Manipulador usado para fazer soar a campainha.  Usar como se segue:

        \code
        ecra << campainha;
        \endcode 

        \see Ecra::tocaCampainha() */
    void campainha(Ecra& ecra);

    //@}

    /** Constante global com os nomes das cores.  Indexável com os valores do
        tipo enumerado Cor. 

        \ingroup ecras */
    extern std::string const nomes_das_cores[numero_de_cores];
}

#include <Slang++/ecra_impl.H>

#endif // SLANG_ECRA_H
