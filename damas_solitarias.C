/********************************************************
                         ISCTE
           Informática e Gestão de Empresas

              Intodução à Programação

             Jogo Das Damas (2ª Fase)

             Trabalho realizado por:
             Rui Varela nº 22175 IA2
             Grupo 11

            the_true_ryven@hotmail.com
 **********************************************************/
#include <iostream>
#include <vector>
#include <Slang++/slang.H>
#include <cassert>
#include <cmath>

using namespace std;
using namespace Slang;

Ecra::ObjectoCor const cor_azul(azul,azul); // tabuleiro preto
Ecra::ObjectoCor const cor_ciano(ciano,ciano);// tabuleiro branco
Ecra::ObjectoCor const cor_branco(branco,branco); //peoes
Ecra::ObjectoCor const cor_preto(preto,preto); //peoes
Ecra::ObjectoCor const cor_damas_pretas(branco,preto);
Ecra::ObjectoCor const cor_damas_brancas(preto,branco);

Ecra::ObjectoCor const cor_texto_brancas(preto,ciano);
Ecra::ObjectoCor const cor_texto_pretas(branco,azul);
Ecra::ObjectoCor const cor_texto(branco,preto);

Ecra::ObjectoCor const cor_selecao(vermelho,vermelho);
Ecra::ObjectoCor const cor_selecao_origem(magenta,magenta);

enum CorDeQuadrado {
    quadrado_preto,
    quadrado_branco,
    quadrado_azul,
    quadrado_ciano,
    quadrado_seleccao_origem,
    quadrado_seleccao_destino
};
/** Procedimento que desenha quadrados
    @pre altura >= 0, largura >= 0, posicionamento >= Posicao(0,0)
    @post quadrado com as dimendoes altura largura, desenhado a partir de
    posicionamenteo e de cor cor. */
void desenhaQuadrado(Posicao const &posicionamento, CorDeQuadrado const cor_do_quadrado,int const altura, int const largura){
    assert((altura >= 0) and (largura >= 0) and (posicionamento.linha() >= 0) and (posicionamento.coluna() >= 0));
    ecra << cursor(posicionamento + Dimensao(-1,largura));
    for(int linha_actual = 0; linha_actual != altura; ++linha_actual)
    {
        ecra << ecra.posicaoDoCursor() + Dimensao(1,-largura);
        for(int coluna_actual =0; coluna_actual != largura; ++coluna_actual)
        {
            switch (cor_do_quadrado)
            {
              case quadrado_preto:
                ecra << cor_preto << ' ';
                break;
              case quadrado_branco:
                ecra << cor_branco << ' ';
                break;
              case quadrado_azul:
                ecra << cor_azul << ' ';
                break;
             case quadrado_ciano:
               ecra << cor_ciano << ' ';
               break;
              case quadrado_seleccao_destino:
                ecra << cor_selecao << ' ';
                break;
              case quadrado_seleccao_origem:
                ecra << cor_selecao_origem << ' ';
                break;
            }
        }
    }
}
/** Representa um peça.
    @invariant V. */
class Peca {
public:
    enum Tipo {
        sem_peca,
        dama,
        peao
    };
    enum Jogador {
        brancas,
        pretas
    };
    /** Constrói uma nova peça segunto tipo_da_peca e a sua cor
        @pre V.
        @post Peca = tipo_da_peca/cor */
    Peca(Tipo const tipo_da_peca,Jogador jogador);
    /** Simula Peça eliminada,(permitindo simulações de jogadas)
        @pre V.
        @post (this*).tipo() = sem_peca */
    inline void simulaPecaEliminada(); 
    /** Para a simulação de peça eliminada
        @pre V.
        @post (this*).tipo() = tipo_da_peca */
    inline void paraSimulacao(); 
    /** Devolve o tipo desta peça.
        @pre V.
        @post tipo = tipo desta peça */
    inline Tipo tipo() const;
    /** Devolve o jogador a que esta peça pertence.
        @pre V.
        @post jogador = jogador desta peça */
    inline Jogador jogador() const; 
    /** Devolve a cor, que é usada para desenhar desta peça.
        @pre V.
        @post corDestaPeca = cor(a pintar) da peça */
    inline CorDeQuadrado corDestaPeca() const;
private:
    bool simulacao_a_decorrer;
    CorDeQuadrado cor_da_peca;
    Tipo tipo_da_peca;
    Jogador jogador_da_peca;
};
Peca::Peca(Tipo const tipo_da_peca,Jogador jogador)
    :simulacao_a_decorrer(false),tipo_da_peca(tipo_da_peca), jogador_da_peca(jogador)
{
    if (jogador == brancas)
        cor_da_peca = quadrado_branco;
    else
        cor_da_peca = quadrado_preto; //sem_peca n vai ser desenhado por issu é indiferente
}
void Peca::simulaPecaEliminada()
{
    simulacao_a_decorrer = true;
}
void Peca::paraSimulacao()
{
    simulacao_a_decorrer = false;
}
Peca::Tipo Peca::tipo() const
{
    return simulacao_a_decorrer ? sem_peca : tipo_da_peca;
}
CorDeQuadrado Peca::corDestaPeca() const 
{
    return cor_da_peca;
}
Peca::Jogador Peca::jogador() const
{
    return jogador_da_peca;
}
//----------------------------------------CLASSE CELULA----------------------------------------
/** Representa um celula.
    @invariant (posicao_no_ecra.linha() >= 0) e (posicao_no_ecra.coluna() >= 0) 
    e (altura_da_celula >= 3) e (largura_da_celula >= 7) */
class Celula {
public:
    /** Constrói uma nova celula
        @pre V.
        @post Celula /cor */
    inline Celula(CorDeQuadrado const cor_a_usar,Peca::Tipo const tipo, Peca::Jogador const jogador);
    /** Desenha a celula
        @pre V.
        @post Celula desenhada*/
    inline void desenha() const;
    /** Desenha a peca agregada à celula
        @pre V.
        @post peca desenhada */
    void desenhaPeca() const;
    /** Desenha a selecao de destino (caracter central)
        @pre V.
        @post desenhaSeleccaodestino =  1 caracter no centro da celula */
    inline void desenhaSeleccaoDestino() const;
    /** Desenha a selecao de Origem (pinta por cima da celula)
        @pre V.
        @post desenhaSeleccaoOrigem =  celula pintada com a cor de seleccao */
    inline void desenhaSeleccaoOrigem() const;
    /** Actualiza os elementso de referencia da celula 
        @pre (0 <= linha <= 7) and (0 <= coluna <= 7) and (altura >= 3) and (largura >= 7).
        @post actualiza as referencias da celula (posicao,altura,largura) */
    inline void actualizaMedidas(int const linha,int const coluna,int const altura, int const largura);
    /** Substitui a peça da celula
        @pre V.
        @post peca_da_celula = nova_peca */
    inline void substituiPeca(Peca const& nova_peca);
    /** Eliminia a peça agrgada á celula
        @pre V.
        @post peca_da_celula.tipo() = sem_peca */
    inline void eliminaPeca();
    /** Simula a eliminação da peça da celula
        @pre V.
        @post peca_da_celula.tipo() = sem_peca */
    inline void simulaEliminaPeca();
    /** Pára a simulaão de eliminação da peça da celula
        @pre V.
        @post peca_da_celula = peca_da_celula */
    inline void paraSimulacao();
    /** Devolve a peça da celula ->inspector
        @pre V.
        @post peca() = peca_da_celula */
    inline Peca peca() const;
    /** Indica se a celula está ocupada
        @pre V.
        @post estaOcupada = estad da celula (ocupada ou desocupada)  */
    inline bool estaOcupada() const;
    /** Devolve o tipo da peça agregada á celula
        @pre V.
        @post tipoDaPecaQueOcupaCelula() = tipo da peça refernete a esta celula  */
    inline Peca::Tipo tipoDaPecaQueOcupaCelula() const;
    /** Devolve o jogador da peça agregada á celula
        @pre V.
        @post jogadorDaPecaQueOcupaCelula() = jogador da peça rferente a esta celula  */
    inline Peca::Jogador jogadorDaPecaQueOcupaCelula() const;
private:
    Peca peca_da_celula;
    Posicao posicao_no_ecra;
    CorDeQuadrado cor_da_celula;
    int altura_da_celula,largura_da_celula;
    /** Indica se a instância cumpre a condição invariante de classe.
        @pre V.
        @post cumpreInvariante = (posicao_no_ecra.linha() >= 0) e (posicao_no_ecra.coluna() >= 0) 
        e (altura_da_celula >= 3) e (largura_da_celula >= 7) */
    inline bool cumpreInvariante() const;
};
Celula::Celula(CorDeQuadrado const cor_a_usar,Peca::Tipo const tipo, Peca::Jogador const jogador)
    : peca_da_celula(tipo,jogador),cor_da_celula(cor_a_usar)
{
//apóe contrução é necessário actuaçizar as medidas -> actualizaMedidas();
}
bool Celula::cumpreInvariante() const
{
    return ((posicao_no_ecra.linha() >= 0) and (posicao_no_ecra.coluna() >= 0) 
            and (altura_da_celula >= 3) and largura_da_celula >= 7);
}
void Celula::simulaEliminaPeca()
{
    assert(cumpreInvariante());
    peca_da_celula.simulaPecaEliminada();
    assert(cumpreInvariante());
}
void Celula::paraSimulacao()
{
    assert(cumpreInvariante());
    peca_da_celula.paraSimulacao();
    assert(cumpreInvariante());
}
Peca Celula::peca() const 
{
    assert(cumpreInvariante());
    return peca_da_celula;
}
void Celula::substituiPeca(Peca const& nova_peca)
{
    assert(cumpreInvariante());
    peca_da_celula = nova_peca;
    assert(cumpreInvariante());
}
void Celula::eliminaPeca()
{
    assert(cumpreInvariante());
    peca_da_celula = Peca(Peca::sem_peca,Peca::brancas);
    assert(cumpreInvariante());
}
bool Celula::estaOcupada() const
{
    assert(cumpreInvariante());
    return (peca_da_celula.tipo() != Peca::sem_peca);
}
void Celula::actualizaMedidas(int const linha,int const coluna,int const altura, int const largura)
{
    assert((0 <= linha <= 7) and (0 <= coluna <= 7) and (altura >= 3) and (largura >= 7));
    altura_da_celula = altura;
    largura_da_celula = largura;
    posicao_no_ecra = Posicao(2 + (linha * altura_da_celula), 2+ (coluna * largura_da_celula));
    assert(cumpreInvariante());
}
void Celula::desenha() const 
{
    assert(cumpreInvariante());
    desenhaQuadrado(posicao_no_ecra,cor_da_celula,altura_da_celula,largura_da_celula);
}
void Celula::desenhaPeca() const
{
    assert(cumpreInvariante());
    Posicao posicao_da_peca = posicao_no_ecra + Dimensao(1,2);
    int altura = altura_da_celula - 2;
    int largura = largura_da_celula - 4;
    Peca::Jogador jogador_da_peca = peca_da_celula.jogador();
    Peca::Tipo tipo_da_peca = peca_da_celula.tipo();
    CorDeQuadrado cor_da_peca = peca_da_celula.corDestaPeca();
    if (tipo_da_peca != Peca::sem_peca)
    {
        desenhaQuadrado(posicao_da_peca,cor_da_peca,altura,largura);
        if (tipo_da_peca == Peca::dama) {
            if (jogador_da_peca == Peca::brancas)
                ecra << cor_damas_brancas << cursor((posicao_da_peca.linha() + (altura / 2)),
                                                    (posicao_da_peca.coluna() + (largura / 2)))
                     << '*';
            if (jogador_da_peca == Peca::pretas)
                ecra << cor_damas_pretas << cursor((posicao_da_peca.linha() + (altura / 2)),
                                                   (posicao_da_peca.coluna() + (largura / 2)))
                     << '*';
        }
    }
}
void Celula::desenhaSeleccaoDestino() const 
{ 
    assert(cumpreInvariante());
    Posicao posicao_da_seleccao = posicao_no_ecra + Dimensao(altura_da_celula / 2,largura_da_celula / 2);
    desenhaQuadrado(posicao_da_seleccao,quadrado_seleccao_destino,1,1);
}
void Celula::desenhaSeleccaoOrigem() const 
{
    assert(cumpreInvariante());
    desenhaQuadrado(posicao_no_ecra,quadrado_seleccao_origem,altura_da_celula,largura_da_celula);
}
Peca::Tipo Celula::tipoDaPecaQueOcupaCelula() const
{
    assert(cumpreInvariante());
    return peca_da_celula.tipo();
}
Peca::Jogador Celula::jogadorDaPecaQueOcupaCelula() const
{ 
    assert(cumpreInvariante());
    return peca_da_celula.jogador();
}
//----------------------------------------CLASSE TABULEIRO----------------------------------------
/** Representa um tabuleiro de damas.
    @invariant celulas_do_tabuleiro forma um vector 8x8, aspecto >=0*/
class Tabuleiro {
public:
    enum EstadoDePosicao {
        possivel,
        pode_comer,
        impossivel,
        origem_sem_peca,
        destino_ocupado,
        jogador_diferente_da_seleccao, 
        mais_do_que_um_movimento        
    };
    /** Constrói uma novo tabuleiro de damas
        @pre V.
        @post tabuleiro criado*/
    Tabuleiro();
    /** Desenha o tabuleiro 
        @pre V.
        @post tabuleiro desenhado*/
    void desenha() const;
    /** Desenha as peças
        @pre V.
        @post peças desenhado*/
    void desenhaPecas() const;
    /** Desenha as novas referencias de medida do tabuleiro e das celulas
        @pre V.
        @post aspecto = novo aspecto, celulas kom medidas actualizadas*/
    void actualizaMedidas();
    /** Desenha a seleccao de destino na celula posicao_do_tabuleiro
        @pre cumpreLimitesDePosicao(posicao_do_tabuleiro)
        @post SeleccaoDestino() = desenhada em posicao_do_tabuleiro */
    inline void SeleccaoDestino(Posicao const &posicao_do_tabuleiro) const;
    /** Activa a seleccao de origem em posicao_do_tabuleiro
        @pre cumpreLimitesDePosicao(posicao_do_tabuleiro)
        @post origem_selecionada = posicao_do_tabuleiro, estado_da_seleccao_de_origem = true */
    inline void activaSeleccaoOrigem(Posicao const &posicao_do_tabuleiro);
    /** Desactiva a seleccao de origem
        @pre V.
        @post estado_da_seleccao_de_origem = false */
    inline void desactivaSeleccaoOrigem();
    /** Devolve o estado da seleccao de origem
        @pre V.
        @post haSeleccaoDeOrigem() = estado_da_seleccao_de_origem */
    inline bool haSeleccaoDeOrigem() const; //inspector
    /** Indica se há nova dama, alteradndo de seguida ha_nova_dama para false
        @pre V.
        @post haNovaDama() = ha_nova_dama, ha_nova_dama = false */
    inline bool haNovaDama(); 
    /** Devolve o valor d aspecto do tabuleiro
        @pre V.
        @post valorDoAspecto() = aspecto*/
    inline int valorDoAspecto() const; //inspector
    /** Exibe um aviso de erro konsoante o estado
        @pre V.
        @post mensagem de erro */
    void processaErroDeEstadoDePosicao(EstadoDePosicao estado) const;
    /** Indica se alguma peça de 'jogador' pode ser selccionada
        @pre V.
        @post podeSeleccionarAlgumaPosicao() = pode selecional alguma casa */
    bool podeSeleccionarAlgumaPosicao(Peca::Jogador jogador) const;
    /** Indica se posicao_do_tabuleiro pode ser origem de acordo com jogador_actual
        @pre cumpreLimitesDePosicao(posicao_do_tabuleiro)
        @post podeSerOrigem() = estado da posicao */
    EstadoDePosicao podeSerOrigem(Posicao const &posicao_do_tabuleiro,Peca::Jogador const jogador_actual,
                                  Peca::Tipo const tipo_da_peca) const; 
    /** Indica se destino pode ser destino do movimento de acordo com
        jogador_actual e origem
        @pre cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino)
        @post podeSerOrigem() = estado da posicao */
    EstadoDePosicao podeSerDestino(Posicao const &origem,Posicao const &destino,Peca::Jogador const jogador_actual
                                   ,bool const e_sequencia);
    /** Efectua a jogada
        @pre podeserOrigem(origem) and podeSerDestino(destino)
        @post jogada efectuada */
    Peca::Tipo executaJogada(Posicao const &origem,Posicao const &destino);
private:
    /** Simula a execução de um percurso, indicando s é possivel atingir o destino
        @pre V.
        @post indica se pode chegar ao destino */
    bool simulacaoDePercurso(Posicao const &origem,Posicao const &destino,Peca::Jogador const jogador_actual);
    /** Informa se através de movimentos de captura é possível chegar ao destino
        @pre V.
        @post indica se pode chegar ao destino */
    bool podePercorrer(Posicao const &origem,Posicao const &destino,Peca::Jogador const jogador_actual,Peca::Tipo tipo_de_peca);
    /** Termina a simulaçãod e perurso
        @pre V.
        @post todas as peças voltam a reaparecer com os tipo correcto */
    void terminaSimulacao();  
    /** Calcula o numero de peças entre 2 pontos d uma diagonal
        @pre cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino)
        @post numeroDePecasEntreDiagonal() = numero total de peças entre a origem e o destino */
    int numeroDePecasEntreDiagonal(Posicao const &origem,Posicao const &destino) const; 
   /** Indica se a instância cumpre a condição invariante de classe.
        @pre V.
        @post celulas_do_tabuleiro == matrix de [8]x[8], aspecto >= 0  */
    bool cumpreInvariante() const;
    /** Indica se posicao_a_verificar esta dentro dos limites suportados pelo celulas_do_tabuleiro
        @pre V.
        @post posicao_a_verificar = Posicao(0->7,0->7) */
    inline bool cumpreLimitesDePosicao(Posicao const &posicao_a_verificar) const ;
    vector< vector<Celula> > celulas_do_tabuleiro;
    bool estado_da_seleccao_de_origem;
    Posicao origem_selecionada;
    int aspecto;
    bool ha_nova_dama;
};
Tabuleiro::Tabuleiro()
    :estado_da_seleccao_de_origem(false),origem_selecionada(Posicao(0,0)),aspecto(0),ha_nova_dama(false)
{
    celulas_do_tabuleiro.resize(8);
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(int coluna  = 0; coluna != 8; ++coluna) 
        { 
            Peca::Tipo tipo_peca_da_celula = Peca::peao;
            Peca::Jogador jogador_peca_da_celula;
            bool valor_e_impar = ((linha + coluna) % 2) != 0;
            if ((linha <= 2) and valor_e_impar)
                jogador_peca_da_celula = Peca::pretas;
            else if (((linha >= 5) and (linha <= 7)) and valor_e_impar)
                jogador_peca_da_celula = Peca::brancas;
            else
                tipo_peca_da_celula = Peca::sem_peca;
            Celula celula_a_acrescentar((((linha + coluna) % 2) == 0) ? quadrado_ciano : quadrado_azul 
                                        , tipo_peca_da_celula,jogador_peca_da_celula ); 
            celulas_do_tabuleiro[linha].push_back(celula_a_acrescentar);
        }
    }
    actualizaMedidas();
    assert(cumpreInvariante());
}
bool Tabuleiro::cumpreLimitesDePosicao(Posicao const &posicao_a_verificar) const
{
    return (((posicao_a_verificar.linha() >= 0) and (posicao_a_verificar.linha() <= 7)) and 
            ((posicao_a_verificar.coluna() >= 0) and (posicao_a_verificar.coluna() <= 7)));
}
bool Tabuleiro::cumpreInvariante() const 
{
    if (celulas_do_tabuleiro.size() != 8)
        return false;
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        if(celulas_do_tabuleiro[linha].size() != 8)
            return false;
    }
    return (aspecto >= 0);
}
void Tabuleiro::desenha() const
{
    assert(cumpreInvariante());
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(vector< vector<Celula> >::size_type coluna  = 0; coluna != celulas_do_tabuleiro[linha].size(); ++coluna) 
            celulas_do_tabuleiro[linha][coluna].desenha();
    } //O cursor está agora no canto inferior direito do tabuleiro
    int altura = 3 + aspecto;
    int largura = 7 + aspecto;
    ecra << cursor(2+int(altura / 2),0); // vertical (numeros)
    for(int Linha = 1; Linha <= 8  ; ++Linha)
    {
        ecra << fundo << Linha;
        ecra << ecra.posicaoDoCursor() + Dimensao(altura,-1);
    }
    ecra << cursor(0,2+int(largura / 2)); // horizontal (letras)
    char ch= 'A';
    for(int  Coluna= 0; Coluna < 8  ; ++Coluna)
    {
        ecra << fundo << char(ch + Coluna);
        ecra << ecra.posicaoDoCursor() + Dimensao(0,largura - 1);
    }
    ecra << cursor(0,0) << fundo << caixa(1,1,8 * altura + 2, 8 * largura + 2);//Desenha a borda da Tabuleiro
    if(estado_da_seleccao_de_origem) //desenha a seleccao de origem
        celulas_do_tabuleiro[origem_selecionada.linha()][origem_selecionada.coluna()].desenhaSeleccaoOrigem();
}
void Tabuleiro::actualizaMedidas()
{
    int tamanho_vertical = ecra.dimensao().numeroDeLinhas();
    int tamanho_horizontal = ecra.dimensao().numeroDeColunas();
    while((tamanho_vertical < 27) or (tamanho_horizontal < 82))
    {
        Aviso("Erro: Aumente a dimensao da janela para continuar!").interage();
        tamanho_vertical = ecra.dimensao().numeroDeLinhas();
        tamanho_horizontal = ecra.dimensao().numeroDeColunas();
    }
    int incremento_tamanho_vertical = int((tamanho_vertical - 27) / 8);
    int incremento_tamanho_horizontal = int((tamanho_horizontal - 82) / 8);
    aspecto = ((incremento_tamanho_vertical > incremento_tamanho_horizontal)?
                   incremento_tamanho_horizontal:incremento_tamanho_vertical);
    int largura_da_celula = 7 + aspecto;
    int altura_da_celula  = 3 + aspecto;
    for(vector<vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(vector< vector<Celula> >::size_type coluna  = 0; coluna != celulas_do_tabuleiro[linha].size(); ++coluna) 
        { 
            celulas_do_tabuleiro[linha][coluna].actualizaMedidas(linha,coluna,altura_da_celula,largura_da_celula);
        }
    }
 
    ecra << apaga << refresca_tudo;
    assert(cumpreInvariante());
}
void Tabuleiro::desenhaPecas() const
{
    assert(cumpreInvariante());
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(vector< vector<Celula> >::size_type coluna  = 0; coluna != celulas_do_tabuleiro[linha].size(); ++coluna) 
        { 
            celulas_do_tabuleiro[linha][coluna].desenhaPeca();
        }
    }
}
void Tabuleiro::SeleccaoDestino(Posicao const &posicao_do_tabuleiro) const 
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(posicao_do_tabuleiro));
    celulas_do_tabuleiro[posicao_do_tabuleiro.linha()][posicao_do_tabuleiro.coluna()].desenhaSeleccaoDestino();
}
void Tabuleiro::activaSeleccaoOrigem(Posicao const &posicao_do_tabuleiro)
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(posicao_do_tabuleiro));
    estado_da_seleccao_de_origem = true;
    origem_selecionada = posicao_do_tabuleiro;
    desenha();
    desenhaPecas();
    assert(cumpreInvariante());
}
void Tabuleiro::desactivaSeleccaoOrigem()
{
    assert(cumpreInvariante());  
    estado_da_seleccao_de_origem = false;
    desenha();
    desenhaPecas();
    assert(cumpreInvariante());
}
bool Tabuleiro::haSeleccaoDeOrigem() const
{
    assert(cumpreInvariante());
    return estado_da_seleccao_de_origem;
}
int Tabuleiro::valorDoAspecto() const 
{
    assert(cumpreInvariante());
    return aspecto;
}
bool Tabuleiro::haNovaDama()
{
    bool valor_a_devolver = ha_nova_dama;
    ha_nova_dama = false ;
    return valor_a_devolver;
}
void Tabuleiro::terminaSimulacao()
{
    assert(cumpreInvariante());
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(vector< vector<Celula> >::size_type coluna  = 0; coluna != celulas_do_tabuleiro[linha].size(); ++coluna) 
        { 
            celulas_do_tabuleiro[linha][coluna].paraSimulacao();
        }
    }
    assert(cumpreInvariante());
}
bool Tabuleiro::podeSeleccionarAlgumaPosicao(Peca::Jogador jogador) const
{
    assert(cumpreInvariante());
    for(vector< vector<Celula> >::size_type linha = 0; linha != celulas_do_tabuleiro.size(); ++linha) 
    { 
        for(vector< vector<Celula> >::size_type coluna  = 0; coluna != celulas_do_tabuleiro[linha].size(); ++coluna) 
        { 
            if ((celulas_do_tabuleiro[linha][coluna].jogadorDaPecaQueOcupaCelula() == jogador) and
                (celulas_do_tabuleiro[linha][coluna].tipoDaPecaQueOcupaCelula() != Peca::sem_peca))
            { 
                Tabuleiro::EstadoDePosicao estado = podeSerOrigem(Posicao(linha,coluna),jogador,Peca::sem_peca);
                if ((estado == Tabuleiro::possivel) or (estado == Tabuleiro::pode_comer))
                    return true;
            }                                                                                     
        }
    }
    return false;
}
Peca::Tipo Tabuleiro::executaJogada(Posicao const &origem,Posicao const &destino)
{ 
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino));
    Peca::Tipo peca_comida = Peca::sem_peca;
    Peca::Tipo tipo_da_nova_peca = celulas_do_tabuleiro[origem.linha()][origem.coluna()].tipoDaPecaQueOcupaCelula();;
    if (((destino.linha() == 0) or (destino.linha() == 7)) and (tipo_da_nova_peca != Peca::dama))
    {
        tipo_da_nova_peca= Peca::dama;
        ha_nova_dama = true;
    }    
    Peca::Jogador jogador_da_nova_peca = celulas_do_tabuleiro[origem.linha()][origem.coluna()].jogadorDaPecaQueOcupaCelula();
    celulas_do_tabuleiro[destino.linha()][destino.coluna()].substituiPeca(Peca(tipo_da_nova_peca,jogador_da_nova_peca));
    celulas_do_tabuleiro[origem.linha()][origem.coluna()].eliminaPeca();
    int distancia = abs(destino.linha() - origem.linha());
    if (distancia == 1)
        peca_comida = Peca::sem_peca;
    else
    {
        int linha = destino.linha() + (((destino.linha() - origem.linha()) > 0) ? -1 : +1 );
        int coluna = destino.coluna() + (((destino.coluna() - origem.coluna()) > 0) ? -1 : +1 );
        peca_comida = celulas_do_tabuleiro[linha][coluna].tipoDaPecaQueOcupaCelula();
        celulas_do_tabuleiro[linha][coluna].eliminaPeca();
    }
    assert(cumpreInvariante());
    return peca_comida;
}
int Tabuleiro::numeroDePecasEntreDiagonal(Posicao const &origem,Posicao const &destino) const
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino));
    int numero_de_pecas_entre_diagonal;
    if ( destino == origem )
        numero_de_pecas_entre_diagonal = 0;
    else 
    {
        bool sentido_vertical = ((destino.linha() - origem.linha()) > 0); // 1->para baixo
        bool sentido_horizontal = ((destino.coluna() - origem.coluna()) > 0); // 1->para a direita
        Posicao origem_a_calcular = origem + Dimensao((sentido_vertical ? +1 : -1 ) , (sentido_horizontal ? +1 : -1));
        if (celulas_do_tabuleiro[origem_a_calcular.linha()][origem_a_calcular.coluna()].estaOcupada())
            numero_de_pecas_entre_diagonal = 1 + numeroDePecasEntreDiagonal(origem_a_calcular,destino);
        else
            numero_de_pecas_entre_diagonal = 0 + numeroDePecasEntreDiagonal(origem_a_calcular,destino);
    }
    return numero_de_pecas_entre_diagonal;
}
Tabuleiro::EstadoDePosicao Tabuleiro::podeSerDestino(Posicao const &origem,Posicao const &destino,
                                                     Peca::Jogador const jogador_actual,bool const e_sequencia)
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino));
    Tabuleiro::EstadoDePosicao estado = Tabuleiro::impossivel;
    bool e_diagonal = (abs((destino.linha() - origem.linha())) == abs((destino.coluna() - origem.coluna())));
    bool destino_esta_vazio = not(celulas_do_tabuleiro[destino.linha()][destino.coluna()].estaOcupada());
    if (e_diagonal){
        if (destino_esta_vazio)
        {
            bool sentido_correcto = ((destino.linha() - origem.linha() > 0) == int(jogador_actual));
            int distancia = abs(destino.linha() - origem.linha());
            int numero_de_pecas_entre_diagonal = numeroDePecasEntreDiagonal(origem,destino);
            if ((distancia == 1) and sentido_correcto)
                estado = Tabuleiro::possivel;
            else
            { 
                int sentido_vertical = destino.linha() + (((destino.linha() - origem.linha()) > 0) ? -1 : +1 );
                int sentido_horizontal = destino.coluna() + (((destino.coluna() - origem.coluna()) > 0) ? -1 : +1 );
                Celula junto_ao_destino = celulas_do_tabuleiro[sentido_vertical][sentido_horizontal];
                bool peca_junto_ao_destino_adversaria = ((junto_ao_destino.jogadorDaPecaQueOcupaCelula() != jogador_actual) 
                                                         and (junto_ao_destino.tipoDaPecaQueOcupaCelula() != Peca::sem_peca));
                Peca::Tipo tipo_da_peca_origem = celulas_do_tabuleiro[origem.linha()][origem.coluna()].tipoDaPecaQueOcupaCelula();
                if ((distancia == 2) and (numero_de_pecas_entre_diagonal == 1) and //peaoao a comer
                    peca_junto_ao_destino_adversaria and  sentido_correcto)
                    estado = Tabuleiro::pode_comer;
                else if (tipo_da_peca_origem == Peca::dama){ //damas 
                    if ((distancia == 2) and (numero_de_pecas_entre_diagonal == 1) and
                        peca_junto_ao_destino_adversaria and e_sequencia)
                        estado = Tabuleiro::pode_comer; //komer kuando sequencia
                    else if ((numero_de_pecas_entre_diagonal == 1) and peca_junto_ao_destino_adversaria
                             and (tipo_da_peca_origem == Peca::dama))
                        estado = Tabuleiro::pode_comer; //komer normal
                    else if (numero_de_pecas_entre_diagonal == 0)
                        estado = Tabuleiro::possivel;
                }
            }
        }
        else
            estado = Tabuleiro::destino_ocupado;
    }
    if(estado == Tabuleiro::impossivel)
        if (simulacaoDePercurso(origem,destino,jogador_actual))
            estado = Tabuleiro::mais_do_que_um_movimento;
    assert(cumpreInvariante());
    return estado;
}
//,Peca::Tipo const tipo_da_peca = Peca::sem_peca
Tabuleiro::EstadoDePosicao Tabuleiro::podeSerOrigem(Posicao const &posicao_do_tabuleiro,Peca::Jogador const jogador_actual
                                                    ,Peca::Tipo const tipo_da_peca) const
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(posicao_do_tabuleiro));
    Tabuleiro::EstadoDePosicao estado = Tabuleiro::impossivel;
    int linha = posicao_do_tabuleiro.linha();
    int coluna = posicao_do_tabuleiro.coluna();
    bool pode_comer = false;
    bool possivel = false;
    Celula celula_a_verificar = celulas_do_tabuleiro[linha][coluna];
    Peca::Jogador jogador_da_peca = (tipo_da_peca == Peca::sem_peca) ? celula_a_verificar.jogadorDaPecaQueOcupaCelula() : jogador_actual;
    //no caso do 3 parm ser explicitado, simula uma peça na origem definida     
    Peca::Tipo tipo_de_peca = (tipo_da_peca == Peca::sem_peca) ? celula_a_verificar.tipoDaPecaQueOcupaCelula() : tipo_da_peca;
    bool celula_ocupada = (tipo_da_peca == Peca::sem_peca) ? celula_a_verificar.estaOcupada() : true;
    if(celula_ocupada)
    {
        if (jogador_actual != jogador_da_peca)
            estado = Tabuleiro::jogador_diferente_da_seleccao;
        else 
        {
            int numero_de_iteracoes = ((tipo_de_peca == Peca::dama)? 4 : 2);
            int iteracao = 1;
            while(iteracao < (numero_de_iteracoes + 1))
            {
                int sentido_horizontal = int(pow( -1.0 , iteracao));
                int sentido_vertical = ((jogador_actual == Peca::brancas) ? -1 :1) * ((iteracao < 3) ? 1 : -1);
                int linha_a_calcular = linha + sentido_vertical;
                int coluna_a_calcular = coluna + sentido_horizontal;
                if ((coluna_a_calcular < 0) or (coluna_a_calcular > 7) or 
                    (linha_a_calcular < 0) or (linha_a_calcular > 7)) //limita o tabuleiro
                {
                    coluna_a_calcular = coluna; 
                    linha_a_calcular = linha;
                }
                Celula proxima_celula_diagonal = celulas_do_tabuleiro[linha_a_calcular][coluna_a_calcular];
                linha_a_calcular = linha + (2 * sentido_vertical);
                coluna_a_calcular = coluna + (2 * sentido_horizontal);
                if ((coluna_a_calcular < 0) or (coluna_a_calcular > 7) or 
                    (linha_a_calcular < 0) or (linha_a_calcular > 7))
                {
                    coluna_a_calcular = coluna;
                    linha_a_calcular = linha;
                }
                Celula celula_captura = celulas_do_tabuleiro[linha_a_calcular][coluna_a_calcular];
                Peca::Jogador jogador_captura = proxima_celula_diagonal.jogadorDaPecaQueOcupaCelula();  
                if (not(proxima_celula_diagonal.estaOcupada()))
                    possivel = true;
                else if (proxima_celula_diagonal.estaOcupada() and 
                         not(celula_captura.estaOcupada()) and (jogador_actual != jogador_captura))
                    pode_comer = true;
                else
                    estado = Tabuleiro::impossivel;
                ++iteracao;
            }
        }
    }
    else
        estado = Tabuleiro::origem_sem_peca;
    if (pode_comer)
        estado = Tabuleiro::pode_comer;
    else if (possivel)
        estado = Tabuleiro::possivel;
    return estado;
}
bool Tabuleiro::simulacaoDePercurso(Posicao const &origem,Posicao const &destino,
                                    Peca::Jogador const jogador_actual)
{ 
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino));
    Peca::Tipo tipo_de_peca = celulas_do_tabuleiro[origem.linha()][origem.coluna()].tipoDaPecaQueOcupaCelula();
    if (tipo_de_peca == Peca::dama)
    {
        int linha = origem.linha();
        int coluna = origem.coluna();
        int numero_de_iteracoes = ((tipo_de_peca == Peca::dama)? 4 : 2);
        int iteracao = 1;
        while(iteracao < (numero_de_iteracoes + 1))
        {
            int sentido_horizontal = int(pow( -1.0 , iteracao));
            int sentido_vertical = ((jogador_actual == Peca::brancas) ? -1 :1) * ((iteracao < 3) ? 1 : -1);
            bool estado_do_ciclo = true;
            int contador = 1;
            do
            {
                int linha_actual = linha + (sentido_vertical * contador);
                int coluna_actual = coluna + (sentido_horizontal * contador);
                if (not(((coluna_actual < 0) or (coluna_actual > 7) or
                         (linha_actual < 0) or (linha_actual > 7))))
                {
                    Celula cell_a_verificar = celulas_do_tabuleiro[linha_actual][coluna_actual];
                    bool casa_ocupada = cell_a_verificar.estaOcupada();
                    bool jogador_compativel = (cell_a_verificar.jogadorDaPecaQueOcupaCelula() != jogador_actual);
                    if (casa_ocupada and jogador_compativel)
                    {
                        int linha_destino = linha_actual + sentido_vertical;
                        int coluna_destino = coluna_actual + sentido_horizontal;
                        if (not(((coluna_destino < 0) or (coluna_destino > 7) or
                                 (linha_destino < 0) or (linha_destino > 7))))
                        {
                            if(not(celulas_do_tabuleiro[linha_destino][coluna_destino].estaOcupada())) //destino vazio
                            {
                                Posicao junto_a_primeira_adversaria(linha_destino,coluna_destino);
                                bool resultado = podePercorrer(junto_a_primeira_adversaria,destino,jogador_actual,tipo_de_peca);
                                terminaSimulacao();
                                return resultado;
                            }
                            estado_do_ciclo = false;
                        }
                    }
                    else if(casa_ocupada)
                        estado_do_ciclo = false;
                }
                else
                    estado_do_ciclo = false;
                ++contador;
            }
            while(estado_do_ciclo);
                ++iteracao;

        }
        return false;
    }
    else
    {
        bool resultado = podePercorrer(origem,destino,jogador_actual,tipo_de_peca);
        terminaSimulacao();
        return resultado;    
    } 
}
bool Tabuleiro::podePercorrer (Posicao const &origem,Posicao const &destino,
                              Peca::Jogador const jogador_actual,Peca::Tipo tipo_de_peca )
{
    assert(cumpreInvariante());
    assert(cumpreLimitesDePosicao(origem) and cumpreLimitesDePosicao(destino));
    if (destino == origem)
        return true;
    if (podeSerOrigem(origem,jogador_actual,tipo_de_peca)== Tabuleiro::pode_comer)
    {
        int linha = origem.linha();
        int coluna = origem.coluna();
        int numero_de_iteracoes = ((tipo_de_peca == Peca::dama)? 4 : 2);
        int iteracao = 1;
        while(iteracao < (numero_de_iteracoes + 1))
        {
            int sentido_horizontal = int(pow( -1.0 , iteracao));
            int sentido_vertical = ((jogador_actual == Peca::brancas) ? -1 :1) * ((iteracao < 3) ? 1 : -1);
            int linha_a_calcular = linha + (2 * sentido_vertical);
            int coluna_a_calcular = coluna + (2 * sentido_horizontal);
            Posicao destino_a_calcular(linha_a_calcular,coluna_a_calcular);
           
            if (not(((coluna_a_calcular < 0) or (coluna_a_calcular > 7) or
                     (linha_a_calcular < 0) or (linha_a_calcular > 7))))
            {
                int peca_intermedia_linha = linha + sentido_vertical;
                int peca_intermedia_coluna = coluna + sentido_horizontal;
                if (not(((peca_intermedia_coluna < 0) or (peca_intermedia_coluna > 7) or
                         (peca_intermedia_linha < 0) or (peca_intermedia_linha > 7))))
                {
                    bool destino_vazio =
                        (celulas_do_tabuleiro[linha_a_calcular][coluna_a_calcular].tipoDaPecaQueOcupaCelula() == Peca::sem_peca );
                    Peca::Jogador junto_ao_destino =
                        celulas_do_tabuleiro[peca_intermedia_linha][peca_intermedia_coluna].jogadorDaPecaQueOcupaCelula();
                    bool peca_junto_ao_destino_adversaria = (junto_ao_destino != jogador_actual);
                    bool peca_junto_ao_destino =
                        (celulas_do_tabuleiro[peca_intermedia_linha][peca_intermedia_coluna].tipoDaPecaQueOcupaCelula() != Peca::sem_peca);
                    
                    if (peca_junto_ao_destino and peca_junto_ao_destino_adversaria and destino_vazio)
                    {
                        if ((linha_a_calcular == 0) or (linha_a_calcular == 7))
                            tipo_de_peca = Peca::dama;
                        celulas_do_tabuleiro[peca_intermedia_linha][peca_intermedia_coluna].simulaEliminaPeca();
                        if(podePercorrer(destino_a_calcular,destino,jogador_actual,tipo_de_peca))
                           return true;
                        celulas_do_tabuleiro[peca_intermedia_linha][peca_intermedia_linha].paraSimulacao();
                    }
                }
            }
            ++iteracao;
        }
    }
    return false;
}
void Tabuleiro::processaErroDeEstadoDePosicao(Tabuleiro::EstadoDePosicao const estado) const
{
    assert(cumpreInvariante());
    string mensagem_a_mostrar;
    switch(estado)
    {
      case Tabuleiro::origem_sem_peca :
        mensagem_a_mostrar = "A posicao escolhida não està ocupada!";
        break;
      case Tabuleiro::destino_ocupado :
        mensagem_a_mostrar = "Não é possível mover a peças escolhida!";
        break;
      case Tabuleiro::jogador_diferente_da_seleccao:
        mensagem_a_mostrar = "A peca não tem a cor certa!";
        break;
      case Tabuleiro::impossivel :
        mensagem_a_mostrar = "Não é possível mover a peça escolhida!";
        break;
      case Tabuleiro::mais_do_que_um_movimento:
        mensagem_a_mostrar = "Jogada realizável em mais que um movimento";
        break;
      default:
        break;
    }
    Aviso(mensagem_a_mostrar).interage();
    ecra.apaga();
    desenha();
    desenhaPecas();
}
//----------------------------------------JOGO----------------------------------------
class Jogo {
public:
    enum EstadoDeJogo {
        brancas_ganharam,
        brancas_perderam,
        pretas_ganharam,
        pretas_perderam,
        brancas_desistiram,
        pretas_desistiram,
        empate,
        empate_limite_jogadas
    };
    /** Constrói um novo jogo de damas
        @pre V.
        @post jogo de damas criado */
    Jogo(); //Solitario
    /** Corre o jogo de damas
        @pre V.
        @post jogo terminado*/
    EstadoDeJogo motorDeJogo();
    /** Exibe um mensagem que informa o resultado do jogo
        @pre V.
        @post mensagem com o resulatdo do jogo */
    void processaRsultadoDeJogo(Jogo::EstadoDeJogo const resultado_do_jogo) const;
private:
    /** Selecciona uma posicao do tabuleiro
        @pre V.
        @post posicao = posicao de vector escolhida */
    Tecla selecciona(Posicao &posicao);
    /** Selecciona a origem e destino konsoante as regras das damas
        @pre V.
        @post origem e destino escolhidos de forma válida */
    bool seleccaoInteractiva();
    /** Desenha as informações de jogo
        @pre V.
        @post informações e jogo desenhadas */
    void mostraInformacoes() const;
    /** Verifica se o jogador actual ganhou
        @pre V.
        @post jogadorActualGanhou() = estado do jogador (se ganhou ou n ) */
    bool jogadorActualGanhou() const; 
    /** Verifica se a jogada gerou novas damas e actualiza a
        estatistica de jogo
        @pre V.
        @post informações de peças actualizadas */
    inline void verificaNovasDamas(); 
    /** Actualiza as informações de jogo (estatistica), consoante o
        tipo_de_peca_tomada
        @pre V.
        @post informações de peças actualizadas */
    void calculaNovasInformacoesDeJogo(Peca::Tipo const tipo_peca_tomada, bool const peca_tomada);
    Peca::Jogador jogador_actual;
    Tabuleiro tabuleiro_de_jogo;
    bool e_sequencia;
    Posicao destino,origem;
    int peoes_brancas,damas_brancas,peoes_pretas,damas_pretas;
    int contador_de_jogadas;
    /** Indica se a instância cumpre a condição invariante de classe.
        @pre V.
        @post posição destno e origem com valores de vector válidos,
        número de peças no tabuleiro válido */
    inline bool cumpreInvariante() const;
};
Jogo::Jogo()
    :jogador_actual(Peca::brancas),e_sequencia(false),peoes_brancas(12),damas_brancas(0)
     ,peoes_pretas(12),damas_pretas(0),contador_de_jogadas(0)
{
 
}
bool Jogo::cumpreInvariante() const
{
    return (((0 <= peoes_brancas <= 12) and (0 <= peoes_pretas < 8)) 
            and ((0 <= damas_brancas <= 12) and (0 <= damas_pretas < 8)) 
            and (0 <= contador_de_jogadas <= 20) and
            ((0 <= origem.linha() <= 7 ) and (0 <= origem.coluna() <= 7)) and 
            ((0 <= destino.linha() <= 7 ) and (0 <= destino.coluna() <= 7)) );

}
bool Jogo::jogadorActualGanhou() const
{
    assert(cumpreInvariante());
    return (((peoes_brancas == 0) and (damas_brancas == 0)) 
            or ((peoes_pretas == 0) and (damas_pretas ==0)));
}
void Jogo::verificaNovasDamas()
{
    assert(cumpreInvariante());
    if (tabuleiro_de_jogo.haNovaDama())
        calculaNovasInformacoesDeJogo(Peca::dama,false);
    assert(cumpreInvariante());
}
Jogo::EstadoDeJogo Jogo::motorDeJogo()
{
    assert(cumpreInvariante());
      do{ //ciclo referente ás 20 jogadas
        ++contador_de_jogadas;
        for(int jogador = 0; jogador!=2; ++jogador)
        { // ciclo referente a troca de jogadores

           if (not(tabuleiro_de_jogo.podeSeleccionarAlgumaPosicao(jogador_actual))) //testa empate
                return (jogador_actual == Peca::brancas) ? Jogo::pretas_ganharam : Jogo::brancas_ganharam;
           bool jogada_terminada = false;
           while (not(jogada_terminada)){ 
               tabuleiro_de_jogo.desenha();
               tabuleiro_de_jogo.desenhaPecas();
               mostraInformacoes();

               if (not(seleccaoInteractiva())) //testa desistencia
                   return (jogador_actual == Peca::brancas) ? Jogo::brancas_desistiram : Jogo::pretas_desistiram ;
               Peca::Tipo peca_tomada = tabuleiro_de_jogo.executaJogada(origem,destino);
               
               calculaNovasInformacoesDeJogo(peca_tomada,true);
               verificaNovasDamas();
               if (jogadorActualGanhou()) //testa vitoria
                   return (jogador_actual == Peca::brancas) ? Jogo::brancas_ganharam : Jogo::pretas_ganharam;
               if ((tabuleiro_de_jogo.podeSerOrigem(destino,jogador_actual,Peca::sem_peca) 
                    == Tabuleiro::pode_comer) 
                   and peca_tomada != Peca::sem_peca)
               {
                   MenuDeSimOuNao menu_de_sequencia("Quer continuar?");
                   menu_de_sequencia.interage();
                   if (menu_de_sequencia.opcaoActual())
                   {
                       tabuleiro_de_jogo.activaSeleccaoOrigem(destino);
                       origem = destino;
                       e_sequencia = true;
                   }
                   else
                       jogada_terminada = true;
               }
               else
                   jogada_terminada = true;
           }
           jogador_actual = (jogador_actual == Peca::brancas) ? Peca::pretas : Peca::brancas; // muda de jogador
            tabuleiro_de_jogo.desactivaSeleccaoOrigem();
            e_sequencia = false;
        }
    }while(contador_de_jogadas != 20);

    return Jogo::empate_limite_jogadas;
}
void Jogo::calculaNovasInformacoesDeJogo(Peca::Tipo const tipo_peca_tomada, bool const peca_tomada)
{
    assert(cumpreInvariante());
    if (not(peca_tomada))
    {
        if (jogador_actual == Peca::brancas)
        {
            ++damas_brancas;
            --peoes_brancas;
        }
        else
        {
            ++damas_pretas;
            --peoes_pretas;
        }
    }
    else if(tipo_peca_tomada != Peca::sem_peca)
    {
         contador_de_jogadas = 0;
        if (jogador_actual != Peca::brancas)
        {
            if (tipo_peca_tomada == Peca::peao)
                --peoes_brancas;
            else 
                --damas_brancas;
        }
        else
        {
            if (tipo_peca_tomada == Peca::peao)
                --peoes_pretas;
            else 
                --damas_pretas;
        }
        
    }
    assert(cumpreInvariante());
}
void Jogo::mostraInformacoes() const
{
    assert(cumpreInvariante());
    int largura_da_celula = 7 + tabuleiro_de_jogo.valorDoAspecto();
    int altura_da_celula  = 3 + tabuleiro_de_jogo.valorDoAspecto();
    ecra << cursor(2,2 + 8*largura_da_celula + 3) << largura(20) << cor_texto_brancas << a_esquerda << "Brancas";
    ecra << cursor(3,2 + 8*largura_da_celula + 3) << cor_texto << "Peões: " << largura(2) << a_direita << peoes_brancas;
    ecra << cursor(4,2 + 8*largura_da_celula + 3) << cor_texto << "Damas: " << largura(2) << a_direita << damas_brancas;

    ecra << cursor(6,2 + 8*largura_da_celula + 3) << largura(20) << cor_texto_pretas << a_esquerda << "Pretas";
    ecra << cursor(7,2 + 8*largura_da_celula + 3) << cor_texto << "Peões: " << largura(2) << a_direita << peoes_pretas;
    ecra << cursor(8,2 + 8*largura_da_celula + 3) << cor_texto << "Damas: " << largura(2) << a_direita << damas_pretas;

    Posicao posicao_indica_jogador(8 * altura_da_celula -1,2 + 8 * largura_da_celula + 3);
    desenhaQuadrado(posicao_indica_jogador,(jogador_actual == Peca::pretas ? quadrado_azul : quadrado_ciano),3,20);
    ecra << cursor(posicao_indica_jogador.linha()+1,posicao_indica_jogador.coluna())
         <<(jogador_actual ? cor_texto_pretas : cor_texto_brancas) << largura(20) << ao_centro
         <<(jogador_actual ? "Jogam as Pretas" : "Jogam as brancas");
}
Tecla Jogo::selecciona(Posicao &posicao)
{
    assert(cumpreInvariante());
    assert((0 <= posicao.linha() < 8) and (0 <= posicao.coluna() < 8));
    tabuleiro_de_jogo.SeleccaoDestino(posicao);
    while (true)
     {
        if(ecra.foiRedimensionado())//em caso de redimensionamento
        {
            tabuleiro_de_jogo.actualizaMedidas();
            ecra.refresca();
            tabuleiro_de_jogo.desenha();
            tabuleiro_de_jogo.desenhaPecas();
            tabuleiro_de_jogo.SeleccaoDestino(posicao);
            mostraInformacoes();
        }
        if (teclado.haTeclaDisponivel(10))
        {
            teclado.leProximaTeclaDisponivel();
            Tecla tecla_primida = teclado.teclaLida();
            if (tecla_primida.eDeDeslocamento()) //quando é premido deslocamento
            {
                switch(tecla_primida)//delimita a mesa
                {
                  case Tecla::cima :
                    if(posicao.linha() > 0)
                        posicao.mudaLinhaPara(posicao.linha() - 1);
                    break;
                  case Tecla::baixo :
                    if(posicao.linha() < 7)
                        posicao.mudaLinhaPara(posicao.linha() + 1);
                    break;
                  case Tecla::esquerda :
                    if(posicao.coluna() > 0)
                        posicao.mudaColunaPara(posicao.coluna() - 1);
                    break;
                  case Tecla::direita :
                    if(posicao.coluna() < 7)
                        posicao.mudaColunaPara(posicao.coluna() + 1);
                    break;
                  default: //na maquina mercurio é necessario...
                    break;
                }
                tabuleiro_de_jogo.desenha();
                tabuleiro_de_jogo.desenhaPecas();
                tabuleiro_de_jogo.SeleccaoDestino(posicao);
            }
            else if ((tecla_primida == Tecla::entrada) or (tecla_primida == Tecla::F4))// seleciona origem e destino
                return tecla_primida;           
        }
        ecra.refresca();
    }
}
bool Jogo::seleccaoInteractiva()
{
    assert(cumpreInvariante());
    Tecla tecla_primida = Tecla::F12;
    if (not(tabuleiro_de_jogo.haSeleccaoDeOrigem())) //origem
    { 
        origem = destino; 
        bool fim_do_ciclo = false;
        while(not(fim_do_ciclo))//validação de escolha
        {       
            tecla_primida = selecciona(origem);
            if (tecla_primida == Tecla::F4)
                return false; 
            Tabuleiro::EstadoDePosicao estado_da_seleccao = tabuleiro_de_jogo.podeSerOrigem(origem,jogador_actual,Peca::sem_peca);
            fim_do_ciclo = ((estado_da_seleccao == Tabuleiro::possivel) or (estado_da_seleccao == Tabuleiro::pode_comer));
            if (not(fim_do_ciclo))
            {
                tabuleiro_de_jogo.processaErroDeEstadoDePosicao(estado_da_seleccao);
                mostraInformacoes();
            }
        }
        tabuleiro_de_jogo.activaSeleccaoOrigem(origem);
        destino = origem;
    }
    bool fim_do_ciclo = false; //destino
    while(not(fim_do_ciclo))//validação de escolha
    {   
        tecla_primida = selecciona(destino);
        if (tecla_primida == Tecla::F4)
            return false; 
        Tabuleiro::EstadoDePosicao estado_da_seleccao = tabuleiro_de_jogo.podeSerDestino(origem,destino,jogador_actual,e_sequencia);
        if (e_sequencia) 
        {
            if (estado_da_seleccao == Tabuleiro::pode_comer)
                fim_do_ciclo = true;
            estado_da_seleccao = Tabuleiro::impossivel;
        }
        else
            fim_do_ciclo = ((estado_da_seleccao == Tabuleiro::possivel) or (estado_da_seleccao == Tabuleiro::pode_comer));
        if (not(fim_do_ciclo))
        {
            tabuleiro_de_jogo.processaErroDeEstadoDePosicao(estado_da_seleccao);
            mostraInformacoes();
        }
        tabuleiro_de_jogo.SeleccaoDestino(destino);
    }
    return true;
}
//portabilidade
void Jogo::processaRsultadoDeJogo(Jogo::EstadoDeJogo const resultado_do_jogo) const
{
    assert(cumpreInvariante());
    string mensagem_a_mostrar;
    switch (resultado_do_jogo)
    {
      case Jogo::brancas_perderam:
        mensagem_a_mostrar = "As Brancas Perderam o Jogo";
        break;
      case Jogo::pretas_ganharam:
        mensagem_a_mostrar = "As Pretas Ganharam o Jogo";
        break;
      case Jogo::pretas_perderam:
        mensagem_a_mostrar = "As Pretas Perderam o Jogo";
        break;
      case Jogo::brancas_ganharam:
        mensagem_a_mostrar = "As Brancas Ganharam o Jogo";
        break;
      case Jogo::brancas_desistiram:
        mensagem_a_mostrar = "As Brancas desistiram do jogo";
        break;
      case Jogo::pretas_desistiram:
        mensagem_a_mostrar = "As Pretas desistiram do jogo";
        break;
      case Jogo::empate_limite_jogadas:
        mensagem_a_mostrar = "Empate, O limite de jogadas foi atingido";
        break;
      case Jogo::empate:
        mensagem_a_mostrar = "Os Jogadores empataram";
        break;
      default:
        break;
    }
    Aviso(mensagem_a_mostrar).interage();
}
int main ()
{
    //teclado.leProximaTeclaDisponivel(); //debug
    Jogo novo_jogo;
    Jogo::EstadoDeJogo resultado_do_jogo = novo_jogo.motorDeJogo();
    novo_jogo.processaRsultadoDeJogo(resultado_do_jogo);

}
//c++ -Wall -ansi -pedantic -g -I/usr/local/include/stlport damas_solitarias.C -lstlport_gcc_stldebug -lpthread -lefence -o damas_solitarias -lslang -lSlang++ -lUtilitarios 
