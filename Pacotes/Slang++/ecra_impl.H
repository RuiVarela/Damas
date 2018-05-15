/** \file ecra_impl.H 

    Ficheiro auxiliar de implementação do módulo ecra.

    \ingroup ecra */

#include <cassert>
#include <sstream>
#include <algorithm>

extern "C" {
#include <slang.h>
#include <signal.h>
}


// Posicao:

inline Slang::Posicao::Posicao(int linha, int coluna)
    : linha_(linha), coluna_(coluna) 
{

    assert(cumpreInvariante());
}

inline int Slang::Posicao::linha() const
{
    assert(cumpreInvariante());

    return linha_;
}

inline int Slang::Posicao::coluna() const
{
    assert(cumpreInvariante());

    return coluna_;
}

inline void Slang::Posicao::mudaLinhaPara(int nova_linha) 
{
    assert(cumpreInvariante());

    linha_ = nova_linha;

    assert(cumpreInvariante());
}

inline void Slang::Posicao::mudaColunaPara(int nova_coluna) 
{
    assert(cumpreInvariante());

    coluna_ = nova_coluna;

    assert(cumpreInvariante());
}

inline void Slang::Posicao::carregaDe(std::istream& entrada) 
{
    assert(cumpreInvariante());

    *this = Posicao(entrada);

    assert(cumpreInvariante());
}

inline Slang::Posicao& 
Slang::Posicao::operator+=(Dimensao const& deslocamento) 
{
    assert(cumpreInvariante());

    linha_ += deslocamento.numeroDeLinhas();
    coluna_ += deslocamento.numeroDeColunas();

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Posicao& 
Slang::Posicao::operator-=(Dimensao const& deslocamento)
{
    assert(cumpreInvariante());

    linha_ -= deslocamento.numeroDeLinhas();
    coluna_ -= deslocamento.numeroDeColunas();

    assert(cumpreInvariante());

    return *this;
}

inline bool Slang::Posicao::cumpreInvariante() const
{
    return true;
}

inline Slang::Posicao const
Slang::operator+(Slang::Posicao posicao, Slang::Dimensao const& deslocamento)
{
    posicao += deslocamento;

    return posicao;
}

inline Slang::Posicao const
Slang::operator-(Slang::Posicao posicao, Slang::Dimensao const& deslocamento)
{
    return posicao -= deslocamento;
}

inline Slang::Posicao const
Slang::operator+(Slang::Dimensao const& deslocamento, Slang::Posicao posicao)
{
    posicao += deslocamento;

    return posicao;
}

inline Slang::Posicao const
Slang::operator-(Slang::Dimensao const& deslocamento, 
		 Slang::Posicao const& posicao)
{
    Posicao copia(-posicao);
    copia += deslocamento;

    return copia;
}

inline Slang::Dimensao const
Slang::operator-(Slang::Posicao const& destino, Slang::Posicao const& origem)
{
    return Dimensao(destino.linha() - origem.linha(),
		    destino.coluna() - origem.coluna());
}

inline Slang::Posicao const Slang::operator-(Slang::Posicao const& posicao)
{
    return Posicao(-posicao.linha(), -posicao.coluna());
}

inline bool 
Slang::operator==(Slang::Posicao const& uma_posicao, 
		  Slang::Posicao const& outra_posicao)
{
    return uma_posicao.linha() == outra_posicao.linha() and 
	uma_posicao.coluna() == outra_posicao.coluna();
}

inline bool 
Slang::operator!=(Slang::Posicao const& uma_posicao, 
		  Slang::Posicao const& outra_posicao)
{
    return not (uma_posicao == outra_posicao);
}


// Dimensao:

inline Slang::Dimensao::Dimensao(int numero_de_linhas, 
				 int numero_de_colunas) 
    : numero_de_linhas(numero_de_linhas),
      numero_de_colunas(numero_de_colunas)
{

    assert(cumpreInvariante());
}

inline Slang::Dimensao::Dimensao(Posicao const& posicao) 
    : numero_de_linhas(posicao.linha()),
      numero_de_colunas(posicao.coluna())
{

    assert(cumpreInvariante());
}
      
inline int Slang::Dimensao::numeroDeLinhas() const 
{
    assert(cumpreInvariante());

    return numero_de_linhas;
}

inline int Slang::Dimensao::numeroDeColunas() const
{
    assert(cumpreInvariante());

    return numero_de_colunas;
}

inline bool Slang::Dimensao::eCanonica() const
{
    assert(cumpreInvariante());

    return 0 <= numeroDeColunas() and 0 <= numeroDeLinhas();
}

inline void 
Slang::Dimensao::mudaNumeroDeLinhasPara(int const novo_numero_de_linhas) 
{
    assert(cumpreInvariante());

    numero_de_linhas = novo_numero_de_linhas;

    assert(cumpreInvariante());
}

inline void 
Slang::Dimensao::mudaNumeroDeColunasPara(int const novo_numero_de_colunas) 
{
    assert(cumpreInvariante());

    numero_de_colunas = novo_numero_de_colunas;

    assert(cumpreInvariante());
}

inline void Slang::Dimensao::carregaDe(std::istream& entrada) 
{
    assert(cumpreInvariante());

    *this = Dimensao(entrada);

    assert(cumpreInvariante());
}

inline Slang::Dimensao& Slang::Dimensao::operator+=(Dimensao const& dimensao)
{
    assert(cumpreInvariante() and dimensao.cumpreInvariante());

    numero_de_linhas += dimensao.numeroDeLinhas();
    numero_de_colunas += dimensao.numeroDeColunas();

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Dimensao& Slang::Dimensao::operator-=(Dimensao const& dimensao)
{
    assert(cumpreInvariante() and dimensao.cumpreInvariante());

    numero_de_linhas -= dimensao.numeroDeLinhas();
    numero_de_colunas -= dimensao.numeroDeColunas();

    assert(cumpreInvariante());

    return *this;
}

inline bool Slang::Dimensao::cumpreInvariante() const
{
    return true;
}

inline Slang::Dimensao const Slang::operator+(Dimensao uma_dimensao, 
					      Dimensao const& outra_dimensao)
{
    uma_dimensao += outra_dimensao;

    return uma_dimensao;
}

inline Slang::Dimensao const Slang::operator-(Dimensao uma_dimensao, 
					      Dimensao const& outra_dimensao)
{
    uma_dimensao -= outra_dimensao;

    return uma_dimensao;
}

inline Slang::Dimensao const Slang::operator-(Slang::Dimensao const& dimensao)
{
    return Dimensao(-dimensao.numeroDeLinhas(), -dimensao.numeroDeColunas());
}

inline bool Slang::operator==(Slang::Dimensao const& uma_dimensao, 
			      Slang::Dimensao const& outra_dimensao)
{
    return uma_dimensao.numeroDeLinhas() == outra_dimensao.numeroDeLinhas() and
	uma_dimensao.numeroDeColunas() == outra_dimensao.numeroDeColunas();
}

inline bool Slang::operator!=(Slang::Dimensao const& uma_dimensao, 
			      Slang::Dimensao const& outra_dimensao)
{
    return not (uma_dimensao == outra_dimensao);
}


// Caixa:

inline Slang::Caixa::Caixa(Posicao const& origem, Dimensao const& dimensao)
    : origem_(origem), dimensao_(dimensao)
{

    assert(cumpreInvariante());
}

inline Slang::Caixa::Caixa(Posicao const& origem, Posicao const& extremo)
    : origem_(origem), 
      dimensao_(extremo - origem + Dimensao(1, 1))
{

    assert(cumpreInvariante());
}

inline Slang::Posicao const& Slang::Caixa::origem() const
{
    assert(cumpreInvariante());

    return origem_;
}

inline Slang::Posicao Slang::Caixa::extremo() const
{
    assert(cumpreInvariante());

    return origem_ + dimensao_ - Dimensao(1, 1);
}

inline Slang::Dimensao const& Slang::Caixa::dimensao() const
{
    assert(cumpreInvariante());

    return dimensao_;
}

inline bool Slang::Caixa::eVazia() const
{
    assert(cumpreInvariante());

    return dimensao() == Dimensao(0, 0);
}

inline bool Slang::Caixa::eCanonica() const
{
    assert(cumpreInvariante());

    return dimensao().eCanonica();
}

inline bool Slang::Caixa::contem(Posicao const& posicao) const
{
    assert(cumpreInvariante());

    return origem().linha() <= posicao.linha() and 
	posicao.linha() <= extremo().linha() and
	origem().linha() <= posicao.coluna() and 
	posicao.coluna() <= extremo().coluna();
}

inline bool Slang::Caixa::bordaContem(Posicao const& posicao) const
{
    assert(cumpreInvariante());

    return ((origem().linha() <= posicao.linha() and 
	     posicao.linha() <= extremo().linha() and 
	     (posicao.coluna() == origem().coluna() or 
	      posicao.coluna() == extremo().coluna())) or
	    (origem().coluna() <= posicao.coluna() and 
	     posicao.coluna() <= extremo().coluna() and
	     (posicao.linha() == origem().linha() or 
	      posicao.linha() == extremo().linha())));
}

inline void Slang::Caixa::mudaOrigemPara(Posicao const & nova_origem)
{
    assert(cumpreInvariante());

    origem_ = nova_origem;

    assert(cumpreInvariante());
}

inline void Slang::Caixa::mudaExtremoPara(Posicao const& novo_extremo)
{
    assert(cumpreInvariante());

    dimensao_ = novo_extremo - origem() + Dimensao(1, 1);

    assert(cumpreInvariante());
}

inline void Slang::Caixa::mudaDimensaoPara(Dimensao const& nova_dimensao)
{
    assert(cumpreInvariante());

    dimensao_ = nova_dimensao;

    assert(cumpreInvariante());
}

inline Slang::Caixa::Caixa(std::istream& entrada)
    : origem_(entrada), dimensao_(entrada) 
{

    assert(cumpreInvariante());
}

inline void Slang::Caixa::carregaDe(std::istream& entrada) 
{
    assert(cumpreInvariante());

    *this = Caixa(entrada);

    assert(cumpreInvariante());
}

inline Slang::Caixa& 
Slang::Caixa::operator+=(Slang::Dimensao const& deslocamento)
{
    assert(cumpreInvariante());

    origem_ += deslocamento;

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Caixa& 
Slang::Caixa::operator-=(Slang::Dimensao const& deslocamento)
{
    assert(cumpreInvariante());

    origem_ -= deslocamento;

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Caixa& Slang::Caixa::operator+=(Slang::Caixa const& outra_caixa) 
{
    assert(cumpreInvariante());

    mudaOrigemPara(Posicao(std::min(origem().linha(), 
				    outra_caixa.origem().linha()),
			   std::min(origem().coluna(), 
				    outra_caixa.origem().coluna())));
    
    mudaExtremoPara(Posicao(std::max(extremo().linha(), 
				     outra_caixa.extremo().linha()),
			    std::max(extremo().coluna(), 
				     outra_caixa.extremo().coluna())));

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Caixa& Slang::Caixa::operator*=(Slang::Caixa const& outra_caixa) 
{
    assert(cumpreInvariante());

    mudaOrigemPara(Posicao(std::max(origem().linha(), 
				    outra_caixa.origem().linha()),
			   std::max(origem().coluna(), 
				    outra_caixa.origem().coluna())));
    
    mudaExtremoPara(Posicao(std::min(extremo().linha(), 
				     outra_caixa.extremo().linha()),
			    std::min(extremo().coluna(), 
				     outra_caixa.extremo().coluna())));

    assert(cumpreInvariante());

    return *this;
}

inline bool Slang::Caixa::cumpreInvariante() const
{
    return true;
}
	
inline Slang::Caixa const Slang::operator+(Slang::Caixa caixa, 
					   Slang::Dimensao const& deslocamento)
{
    caixa += deslocamento;

    return caixa;
}

inline Slang::Caixa const Slang::operator-(Slang::Caixa caixa, 
					   Slang::Dimensao const& deslocamento)
{
    caixa -= deslocamento;

    return caixa;
}

inline Slang::Caixa const Slang::operator+(Slang::Dimensao const& deslocamento,
					   Slang::Caixa caixa)
{
    caixa += deslocamento;

    return caixa;
}

inline Slang::Caixa const 
Slang::operator+(Slang::Caixa uma_caixa, Slang::Caixa const& outra_caixa)
{
    uma_caixa += outra_caixa;

    return uma_caixa;
}

inline Slang::Caixa const 
Slang::operator*(Slang::Caixa uma_caixa, Slang::Caixa const& outra_caixa)
{
    uma_caixa *= outra_caixa;

    return uma_caixa;
}

inline bool Slang::operator==(Caixa const& uma_caixa, Caixa const& outra_caixa)
{
    return uma_caixa.origem() == outra_caixa.origem() and
	uma_caixa.dimensao() == outra_caixa.dimensao();
}

inline bool Slang::operator!=(Caixa const& uma_caixa, Caixa const& outra_caixa)
{
    return not (uma_caixa == outra_caixa);
}


// Cor:

inline std::ostream& Slang::operator<<(std::ostream& saida, 
				       Slang::Cor const cor) 
{
    saida << Slang::nomes_das_cores[cor];

    return saida;
}


// Ecra:

inline Slang::Ecra::~Ecra()
{
    assert(cumpreInvariante());

    // Terminação do slang:
    SLsmg_reset_smg();
}

inline Slang::Dimensao const Slang::Ecra::dimensao() const 
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return Dimensao(SLtt_Screen_Rows, SLtt_Screen_Cols);
}

inline Slang::Posicao const Slang::Ecra::origem() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return Posicao(0, 0);
}

inline Slang::Posicao const Slang::Ecra::extremo() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return origem() + dimensao() - Dimensao(1, 1);
}

inline Slang::Posicao const Slang::Ecra::posicaoDoCursor() const 
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return Posicao(SLsmg_get_row(), SLsmg_get_column());
}

inline Slang::Justificacao 
Slang::Ecra::justificacaoActual() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return justificacao_actual;
}

inline int Slang::Ecra::larguraDaProximaOperacaoDeEscrita() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return largura_da_proxima_operacao_de_escrita;
}

inline bool Slang::Ecra::foiRedimensionado() const 
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    if(redimensionado_)
    {
	redimensionado_ = false;
	return true;
    } else
	return false;
}

inline bool Slang::Ecra::cursorEstaVisivel() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return parteVisivelContem(posicaoDoCursor());
}

inline bool Slang::Ecra::parteVisivelContem(Posicao const& posicao) const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return Caixa(origem(), dimensao()).contem(posicao);
}

inline bool Slang::Ecra::cursorEstaLimitadoAoEcraReal() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return cursor_esta_limitado_ao_ecra_real;
}

inline bool 
Slang::Ecra::cursorImovelNaProximaOperacaoDeInsercao() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return cursor_imovel_na_proxima_operacao_de_escrita;
}

inline void 
Slang::Ecra::mudaJustificacaoPara(Justificacao const nova_justificacao)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    justificacao_actual = nova_justificacao;

    assert(cumpreInvariante());
}

inline void Slang::Ecra::impoeImobilidadeDoCursorNaProximaInsercao()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    cursor_imovel_na_proxima_operacao_de_escrita = true;

    assert(cumpreInvariante());
}

inline void Slang::Ecra::mudaLarguraDaProximaOperacaoDeEscritaPara
(int const largura_da_proxima_operacao_de_escrita_)
{
    assert(cumpreInvariante());
    assert(0 <= largura_da_proxima_operacao_de_escrita_);

    verificaRedimensionamento();

    largura_da_proxima_operacao_de_escrita = 
	largura_da_proxima_operacao_de_escrita_;

    assert(cumpreInvariante());
}

inline void Slang::Ecra::mudaObjectoCorEmUsoPara(ObjectoCor const& objecto_cor)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_set_color(objecto_cor.numero_do_objecto);

    assert(cumpreInvariante());
}

inline void Slang::Ecra::mudaObjectoCorEmUsoParaFundo()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_set_color(0);

    assert(cumpreInvariante());
}

inline void 
Slang::Ecra::mudaCoresDasCelulasDoFundoPara(Cor const cor_do_texto, 
					    Cor const cor_do_fundo)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLtt_set_color(0, 0, nome_de_cor_do_s_lang[cor_do_texto], 
		   nome_de_cor_do_s_lang[cor_do_fundo]);

    assert(cumpreInvariante());
}

inline void Slang::Ecra::sobeCursor()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    moveCursorPara(posicaoDoCursor() - Dimensao(1, 0));

    assert(cumpreInvariante());
}

inline void Slang::Ecra::baixaCursor()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    moveCursorPara(posicaoDoCursor() + Dimensao(1, 0));

    assert(cumpreInvariante());
}

inline void Slang::Ecra::recuaCursor()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    moveCursorPara(posicaoDoCursor() - Dimensao(0, 1));

    assert(cumpreInvariante());
}

inline void Slang::Ecra::avancaCursor()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    moveCursorPara(posicaoDoCursor() + Dimensao(0, 1));

    assert(cumpreInvariante());
}

inline Slang::Ecra::Troco const Slang::Ecra::trocoDoEcraCompleto() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    return trocoDe(Caixa(Posicao(0, 0), dimensao()));
}

inline Slang::Ecra::Troco const
Slang::Ecra::trocoNoCursorCom(Dimensao const& dimensao) const
{
    assert(cumpreInvariante());
    assert(dimensao.eCanonica());

    verificaRedimensionamento();

    return trocoDe(Caixa(posicaoDoCursor(), dimensao));
}

inline void Slang::Ecra::tocaCampainha() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLtt_beep();
}

inline void Slang::Ecra::apagaDoCursorAteOFimDaLinha()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_erase_eol();

    assert(cumpreInvariante());
}

inline void Slang::Ecra::apagaDoCursorAteOFim()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_erase_eos();

    assert(cumpreInvariante());
}

inline void Slang::Ecra::apaga()
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_cls();

    assert(cumpreInvariante());
}

inline void Slang::Ecra::refresca() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_refresh();
}

inline void Slang::Ecra::refrescaTudo() const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    // Com isto o próximo refresh redesenhará todo o ecrã!
    SLsmg_touch_lines(0, dimensao().numeroDeLinhas());

    refresca();
}

template <typename T>
inline Slang::Ecra& Slang::Ecra::operator<<(T const& valor)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    std::ostringstream saida;

    saida << valor;

    *this << saida.str();

    assert(cumpreInvariante());

    return ecra;
}

inline Slang::Ecra& Slang::Ecra::operator<<(Caixa const& caixa)
{
    assert(cumpreInvariante());
    assert(caixa.eCanonica());

    verificaRedimensionamento();

    desenha(caixa);

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& Slang::Ecra::operator<<(Simbolo const simbolo)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    SLsmg_set_char_set(1);
    *this << char(simbolo);
    SLsmg_set_char_set(0);

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& Slang::Ecra::operator<<(Troco const& troco)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    cola(troco, posicaoDoCursor());

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& 
Slang::Ecra::operator<<(Posicao const& nova_posicao_do_cursor)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    moveCursorPara(nova_posicao_do_cursor);

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& Slang::Ecra::operator<<(ObjectoCor const& objecto_cor)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    mudaObjectoCorEmUsoPara(objecto_cor);

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& 
Slang::Ecra::operator<<(Justificacao nova_justificacao)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    mudaJustificacaoPara(nova_justificacao);

    assert(cumpreInvariante());

    return *this;
}

inline Slang::Ecra& 
Slang::Ecra::operator<<(void manipulador(Ecra& ecra))
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    manipulador(*this);

    assert(cumpreInvariante());

    return *this;
}

inline void Slang::Ecra::mudaCoresDe(int const objecto, 
				     Cor const cor_do_texto, 
				     Cor const cor_do_fundo) 
{
    SLtt_set_color(objecto, 0, 
		   nome_de_cor_do_s_lang[cor_do_texto], 
		   nome_de_cor_do_s_lang[cor_do_fundo]);
}

inline void Slang::Ecra::manipuladorDeRedimensionamento(int const sinal)
{
    Slang::Ecra::tamanho_do_ecra_real_mudou = true;

    SLsignal(SIGWINCH, manipuladorDeRedimensionamento);
}

inline bool Slang::Ecra::cumpreInvariante() const
{
    return true;
}


// Ecra::ObjectoCor:

inline Slang::Ecra::ObjectoCor::ObjectoCor(Cor const cor_do_texto, 
					   Cor const cor_do_fundo)
    : cor_do_texto(cor_do_texto), cor_do_fundo(cor_do_fundo),
      numero_do_objecto(ecra.reservaObjecto())
{
    ecra.mudaCoresDe(numero_do_objecto, cor_do_texto, cor_do_fundo);

    assert(cumpreInvariante());
}

inline Slang::Ecra::ObjectoCor::~ObjectoCor()
{
    assert(cumpreInvariante());

    ecra.libertaObjecto(numero_do_objecto);
}

inline Slang::Cor Slang::Ecra::ObjectoCor::corDoTexto() const
{
    assert(cumpreInvariante());

    return cor_do_texto;
}

inline Slang::Cor Slang:: Ecra::ObjectoCor::corDoFundo() const
{
    assert(cumpreInvariante());

    return cor_do_fundo;
}

inline void 
Slang::Ecra::ObjectoCor::mudaCorDoTextoPara(Cor const nova_cor_do_texto)
{
    assert(cumpreInvariante());

    cor_do_texto = nova_cor_do_texto;

    ecra.mudaCoresDe(numero_do_objecto, cor_do_texto, cor_do_fundo);

    assert(cumpreInvariante());
}

inline void 
Slang::Ecra::ObjectoCor::mudaCorDoFundoPara(Cor const nova_cor_do_fundo)
{
    assert(cumpreInvariante());

    cor_do_fundo = nova_cor_do_fundo;

    ecra.mudaCoresDe(numero_do_objecto, cor_do_texto, cor_do_fundo);

    assert(cumpreInvariante());
}

inline bool Slang::Ecra::ObjectoCor::cumpreInvariante() const
{
    return 1 <= numero_do_objecto and 
	numero_do_objecto < numero_de_objectos_cor_no_s_lang;
}


// Ecra::Troco:

inline Slang::Ecra::Troco::Troco(Dimensao const& dimensao)
    : dimensao_(dimensao), 
      dados(dimensao.numeroDeLinhas() * dimensao.numeroDeColunas())
{
    assert(dimensao.eCanonica());

    assert(cumpreInvariante());
}

inline Slang::Dimensao Slang::Ecra::Troco::dimensao() const
{
    assert(cumpreInvariante());

    return dimensao_;
}

inline bool Slang::Ecra::Troco::cumpreInvariante() const
{
    return dimensao_.numeroDeLinhas() * dimensao_.numeroDeColunas() ==
	int(dados.size());
}


// ManipuladorDaLargura:

inline Slang::ManipuladorDaLargura::ManipuladorDaLargura(int const largura)
    : largura(largura)
{
}

inline Slang::Ecra& Slang::operator<<(Ecra& ecra, 
				      ManipuladorDaLargura const& manipulador) 
{
    ecra.mudaLarguraDaProximaOperacaoDeEscritaPara(manipulador.largura);
    
    return ecra;
}


// ManipuladorDeDesenhoDeSegmento:

inline Slang::ManipuladorDeDesenhoDeSegmento::
ManipuladorDeDesenhoDeSegmento(bool const e_horizontal, 
			       int const dimensao)
    : e_horizontal(e_horizontal), dimensao(dimensao)
{
}

inline Slang::Ecra& 
Slang::operator<<(Ecra& ecra, 
		  ManipuladorDeDesenhoDeSegmento const& manipulador)
{
    if(manipulador.e_horizontal)
	ecra.desenhaSegmentoHorizontalCom(manipulador.dimensao);
    else
	ecra.desenhaSegmentoVerticalCom(manipulador.dimensao);

    return ecra;
}


// Manipuladores:

inline Slang::Posicao const Slang::cursor(int const linha, int const coluna)
{
    return Slang::Posicao(linha, coluna);
}

inline Slang::Posicao const& Slang::cursor(Slang::Posicao const& posicao)
{
    return posicao;
}

inline Slang::Caixa const Slang::caixa(int const linha, int const coluna, 
				       int const numero_de_linhas, 
				       int const numero_de_colunas)
{
    return Caixa(Posicao(linha, coluna), 
		 Dimensao(numero_de_linhas, numero_de_colunas));
}

inline Slang::Caixa const 
Slang::caixa(Slang::Posicao const& origem, Slang::Dimensao const& dimensao)
{
    return Caixa(origem, dimensao);
}

inline void Slang::fundo(Slang::Ecra& ecra)
{
    ecra.mudaObjectoCorEmUsoParaFundo();
}

inline void Slang::parado(Slang::Ecra& ecra)
{
    ecra.impoeImobilidadeDoCursorNaProximaInsercao();
}

inline void Slang::sobeCursor(Slang::Ecra& ecra)
{
    ecra.sobeCursor();
}

inline void Slang::baixaCursor(Slang::Ecra& ecra)
{
    ecra.baixaCursor();
}

inline void Slang::recuaCursor(Slang::Ecra& ecra)
{
    ecra.recuaCursor();
}

inline void Slang::avancaCursor(Slang::Ecra& ecra)
{
    ecra.avancaCursor();
}

inline Slang::ManipuladorDaLargura Slang::largura(int const largura)
{
    assert(0 <= largura);

    return ManipuladorDaLargura(largura);
}

inline Slang::ManipuladorDeDesenhoDeSegmento 
Slang::segmento_horizontal(int largura)
{
    assert(0 <= largura);

    return ManipuladorDeDesenhoDeSegmento(true, largura);
}

inline Slang::ManipuladorDeDesenhoDeSegmento 
Slang::segmento_vertical(int altura)
{
    assert(0 <= altura);

    return ManipuladorDeDesenhoDeSegmento(false, altura);
}

inline void Slang::refresca(Ecra& ecra)
{
    ecra.refresca();
}

inline void Slang::refresca_tudo(Ecra& ecra)
{
    ecra.refrescaTudo();
}

inline void Slang::apaga(Ecra& ecra)
{
    ecra.apaga();
}

inline void Slang::apaga_fim_da_linha(Ecra& ecra)
{
    ecra.apagaDoCursorAteOFimDaLinha();
}

inline void Slang::apaga_fim_do_ecra(Ecra& ecra)
{
    ecra.apagaDoCursorAteOFim();
}

inline void Slang::campainha(Ecra& ecra)
{
    ecra.tocaCampainha();
}
