/** \file ecra.C

    Ficheiro de implementção do módulo ecras. Define classes que permitem usar
    o ecrã alfa-numérico.

    \ingroup ecras */
#include <Slang++/ecra.H>

#include <Utilitarios/ignoradores.H>
#include <Erros/erros.H>

#include <memory.h>

using namespace std;

// Posicao:

Slang::Posicao::Posicao(istream& entrada) 
{
    assert(entrada.good());

    entrada >> linha_ >> Utilitarios::il >> coluna_ >> Utilitarios::il;

    if(not entrada.good())
	throw Erros::ErroAoCarregar("Posicao");

    assert(cumpreInvariante());
}

void Slang::Posicao::guardaEm(ostream& saida) const
{
    assert(cumpreInvariante());

    if(not (saida << linha_ << endl << coluna_ << endl))
	throw Erros::ErroAoGuardar("Posicao");
}


// Dimensao:

Slang::Dimensao::Dimensao(istream& entrada) 
{
    assert(entrada.good());

    entrada >> numero_de_linhas >> Utilitarios::il 
	    >> numero_de_colunas >> Utilitarios::il;

    if(not entrada.good())
	throw Erros::ErroAoCarregar("Dimensao");

    assert(cumpreInvariante());
}
      
void Slang::Dimensao::guardaEm(ostream& saida) const
{
    assert(cumpreInvariante());

    if(not (saida << numero_de_linhas << endl << numero_de_colunas << endl))
	throw Erros::ErroAoGuardar("Dimensao");
}


// Caixa:

void Slang::Caixa::guardaEm(ostream& saida) const
{
    assert(cumpreInvariante());

    origem_.guardaEm(saida);
    dimensao_.guardaEm(saida);
}


// Cor:

istream& Slang::operator>>(istream& entrada, Slang::Cor& cor) 
{
    string nome;
    if(entrada >> nome) {
	for(int c = Slang::primeira_cor; c != Slang::numero_de_cores; ++c)
	    if(Slang::nomes_das_cores[c] == nome) {
		cor = Slang::Cor(c);

		return entrada;
	    }
	entrada.clear(ios_base::badbit);
    }

    return entrada;
}


// Ecra:

Slang::Ecra::Ecra(Cor cor_do_texto, Cor cor_do_fundo, 
		  bool cursor_deve_ser_limitado)
    : cursor_esta_limitado_ao_ecra_real(cursor_deve_ser_limitado),
      redimensionado_(false),
      cursor_imovel_na_proxima_operacao_de_escrita(false), 
      justificacao_actual(a_esquerda), 
      largura_da_proxima_operacao_de_escrita(0), 
      ocupacao_dos_objectos(ObjectoCor::numero_de_objectos_cor_no_s_lang) 
{
    assert(not ja_existe_instancia);

    ja_existe_instancia = true;

    // Inicializações do slang:

    SLtt_get_terminfo();

    if(SLsmg_init_smg() == -1) {
	// Que fazer?
	assert(false);
    }

    // Inicializaçãoo do manipulador de mudanças no ecrã:
    SLsignal(SIGWINCH, manipuladorDeRedimensionamento);

    mudaCoresDasCelulasDoFundoPara(cor_do_texto, cor_do_fundo);

    assert(cumpreInvariante());
}

void Slang::Ecra::moveCursorPara(Posicao const& nova_posicao)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    int linha = nova_posicao.linha();
    int coluna = nova_posicao.coluna();

    if(cursor_esta_limitado_ao_ecra_real)
    {
	if(linha >= dimensao().numeroDeLinhas()) 
	    linha = dimensao().numeroDeLinhas() - 1;
	else if(linha < 0) 
	    linha = 0;
	
	if(coluna >= dimensao().numeroDeColunas()) 
	    coluna = dimensao().numeroDeColunas() - 1;
	else if(coluna < 0) 
	    coluna = 0;
    }

    SLsmg_gotorc(linha, coluna);

    assert(cumpreInvariante());
}

void Slang::Ecra::moveCursorDeAcordoCom(Slang::Tecla const& tecla) 
{
    assert(cumpreInvariante());
    assert(tecla.eDeDeslocamento());

    switch(tecla)
    {
      case Tecla::cima:
	sobeCursor();
	break;

      case Tecla::baixo:
	baixaCursor();
	break;

      case Tecla::esquerda:
	recuaCursor();
	break;

      case Tecla::direita:
	avancaCursor();
	break;

      default:
	assert(false);
	break;
    }

    assert(cumpreInvariante());
}

static unsigned short int charAtScreen() {
	SLsmg_Char_Type ch;
	SLsmg_char_at(&ch);
	if (ch.nchars == 1) {
        return static_cast<unsigned short>(ch.wchars[0]);
	}
	return 0;
}

Slang::Ecra::Troco const Slang::Ecra::trocoDe(Caixa const& caixa) const 
{
    assert(cumpreInvariante());
    assert(caixa.eCanonica());

    verificaRedimensionamento();

    // Guardar cursor inicial:
    Posicao const posicao_original_do_cursor = posicaoDoCursor();

    int const linha = caixa.origem().linha(); 
    int const coluna = caixa.origem().coluna();
    int const numero_de_linhas = caixa.dimensao().numeroDeLinhas();
    int const numero_de_colunas = caixa.dimensao().numeroDeColunas();

    Troco troco(caixa.dimensao());
    int i = 0;
    for(int l = linha; l != linha + numero_de_linhas; ++l)
	for(int c = coluna; c != coluna + numero_de_colunas; ++c)
	{
	    	moveCursorPara(Posicao(l, c));
	    	troco.dados[i++] = charAtScreen();
	}

    // Regressar ao cursor inicial:
    moveCursorPara(posicao_original_do_cursor);

    return troco;
}

void Slang::Ecra::cola(Troco const& troco, Posicao const& em)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    Posicao posicao_original_do_cursor;

    if(cursor_imovel_na_proxima_operacao_de_escrita)
	posicao_original_do_cursor = posicaoDoCursor();

    int const linha = em.linha();
    int const coluna = em.coluna();
    int const numero_de_linhas = troco.dimensao().numeroDeLinhas();
    int const numero_de_colunas = troco.dimensao().numeroDeColunas();

    int i = 0;
    for(int l = linha; l != linha + numero_de_linhas; ++l)
	for(int c = coluna; c != coluna + numero_de_colunas; ++c)
	{
	    moveCursorPara(Posicao(l, c));
	    char const caractere = troco.dados[i] & 0XFF;
	    int const objecto = troco.dados[i++] >> 8;
	    SLsmg_set_color(objecto);
	    SLsmg_write_char(caractere);
	}

    if(cursor_imovel_na_proxima_operacao_de_escrita) {
	moveCursorPara(posicao_original_do_cursor);

	cursor_imovel_na_proxima_operacao_de_escrita = false;
    }

    // Em vez de regressar ao objecto da próxima escrita, põe-se o fundo:
    *this << fundo;

    assert(cumpreInvariante());
}

void Slang::Ecra::desenha(Caixa const& caixa)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    Posicao posicao_original_do_cursor;

    if(cursor_imovel_na_proxima_operacao_de_escrita)
	posicao_original_do_cursor = posicaoDoCursor();

    SLsmg_draw_box(caixa.origem().linha(), caixa.origem().coluna(), 
		   caixa.dimensao().numeroDeLinhas(), 
		   caixa.dimensao().numeroDeColunas());

    if(cursor_imovel_na_proxima_operacao_de_escrita)
    {
	moveCursorPara(posicao_original_do_cursor);

	cursor_imovel_na_proxima_operacao_de_escrita = false;
    }

    assert(cumpreInvariante());
}

void Slang::Ecra::desenhaSegmentoHorizontalCom(int const largura)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    Posicao posicao_original_do_cursor;

    if(cursor_imovel_na_proxima_operacao_de_escrita)
	posicao_original_do_cursor = posicaoDoCursor();

    SLsmg_draw_hline(largura);

    if(cursor_imovel_na_proxima_operacao_de_escrita)
    {
	moveCursorPara(posicao_original_do_cursor);

	cursor_imovel_na_proxima_operacao_de_escrita = false;
    }

    assert(cumpreInvariante());
}

void Slang::Ecra::desenhaSegmentoVerticalCom(int const altura)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    Posicao posicao_original_do_cursor;

    if(cursor_imovel_na_proxima_operacao_de_escrita)
	posicao_original_do_cursor = posicaoDoCursor();

    SLsmg_draw_vline(altura);

    if(cursor_imovel_na_proxima_operacao_de_escrita)
    {
	moveCursorPara(posicao_original_do_cursor);

	cursor_imovel_na_proxima_operacao_de_escrita = false;
    }

    assert(cumpreInvariante());
}

Slang::Ecra& Slang::Ecra::operator<<(string const& cadeia_a_escrever)
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    string cadeia = cadeia_a_escrever;

    Posicao posicao_original_do_cursor;
    if(cursor_imovel_na_proxima_operacao_de_escrita)
	posicao_original_do_cursor = posicaoDoCursor();

    // Usar const_cast (abaixo) é violento, mas a verdade é que p
    // SLsmg_write_string deveria declarar parãmetro como char const*...

    if(largura_da_proxima_operacao_de_escrita == 0)
	SLsmg_write_string(const_cast<char *>(cadeia.c_str()));
    else {
	string::size_type espaco_a_usar = 
	    largura_da_proxima_operacao_de_escrita;

	if(cadeia.size() < espaco_a_usar)
	    switch(justificacao_actual) {
	      case ao_centro:
		cadeia = 
		    string((espaco_a_usar - cadeia.size() + 1) / 2,
			   ' ') + cadeia;
		break;
	      case a_direita:
		cadeia = 
		    string(espaco_a_usar - cadeia.size(), ' ') + 
		    cadeia;
		break;
	      case a_esquerda:
		cadeia += 
		    string(espaco_a_usar - cadeia.size(), ' ');
		break;
	    }
	else
	    switch(justificacao_actual) {
	      case ao_centro:
		cadeia = cadeia.substr((cadeia.size() - espaco_a_usar) / 2,
				       espaco_a_usar);
		break;
	      case a_direita:
		cadeia = cadeia.substr(cadeia.size() - espaco_a_usar,
				       espaco_a_usar);
		break;
	      case a_esquerda:
		cadeia = cadeia.substr(0, espaco_a_usar);
		break;
	    }
	    
	SLsmg_write_nstring(const_cast<char *>(cadeia.c_str()), 
			    espaco_a_usar);

	largura_da_proxima_operacao_de_escrita = 0;
    }

    if(cursor_imovel_na_proxima_operacao_de_escrita) {
	moveCursorPara(posicao_original_do_cursor);
	cursor_imovel_na_proxima_operacao_de_escrita = false;
    }

    assert(cumpreInvariante());

    return *this;
}

Slang::Ecra const& Slang::Ecra::operator>>(Troco& troco) const
{
    assert(cumpreInvariante());

    verificaRedimensionamento();

    Posicao const posicao_original_do_cursor = posicaoDoCursor();

    int const linha = posicao_original_do_cursor.linha();
    int const coluna = posicao_original_do_cursor.coluna();
    int const numero_de_linhas = troco.dimensao().numeroDeLinhas();
    int const numero_de_colunas = 
	troco.dimensao().numeroDeColunas();

    int i = 0;
    for(int l = linha; l != linha + numero_de_linhas; ++l)
	for(int c = coluna; c != coluna + numero_de_colunas; ++c) {
	    moveCursorPara(Posicao(l, c));
	    troco.dados[i++] = charAtScreen();
	}

    moveCursorPara(posicao_original_do_cursor);

    return *this;
}

void Slang::Ecra::verificaRedimensionamento() const
{
    if(tamanho_do_ecra_real_mudou)
    {
	// A variável tamanho_do_ecra_real_mudou passa a falso.  Ela é
	// colocada a true pelo manipulador do sinal SIGWINCH!
	tamanho_do_ecra_real_mudou = false;

	// Como o ecrã mudou de tamanho, põe-se a true a variável
	// redimensionado_, para que os clientes do ecrã possam
	// redesenhar o que for necessário (tipicamente tudo):
	redimensionado_ = true;

	// Guarda-se a antiga posição do cursor:
	Posicao const posicao_do_cursor = posicaoDoCursor();

	// Obter nova dimensão do ecrã e reinicializar o slang smg:
	SLtt_get_screen_size();
	SLsmg_reinit_smg();	// a posição do cursor perde-se aqui...

	// Colocar de novo o cursor onde estava:
	moveCursorPara(posicao_do_cursor);
    }
}

void Slang::Ecra::moveCursorPara(Posicao const& nova_posicao_do_cursor) const
{
    verificaRedimensionamento();

    int linha = nova_posicao_do_cursor.linha();
    int coluna = nova_posicao_do_cursor.coluna();

    if(cursor_esta_limitado_ao_ecra_real)
    {
	if(dimensao().numeroDeLinhas() <= linha) 
	    linha = dimensao().numeroDeLinhas() - 1;
	else if(linha < 0) 
	    linha = 0;
	
	if(dimensao().numeroDeColunas() <= coluna) 
	    coluna = dimensao().numeroDeColunas() - 1;
	else if(coluna < 0) 
	    coluna = 0;
    }

    SLsmg_gotorc(linha, coluna);
}

int Slang::Ecra::reservaObjecto()
{
    int numero_do_objecto_reservado = 1;
    int ocupacao_minima = ocupacao_dos_objectos[1];

    for(int numero_do_objecto = 2; 
	numero_do_objecto != ObjectoCor::numero_de_objectos_cor_no_s_lang; 
	++numero_do_objecto)
	if(ocupacao_dos_objectos[numero_do_objecto] < ocupacao_minima) {
	    ocupacao_minima = ocupacao_dos_objectos[numero_do_objecto];
	    numero_do_objecto_reservado = numero_do_objecto;
	}

    ++ocupacao_dos_objectos[numero_do_objecto_reservado];

    return numero_do_objecto_reservado;
}

void Slang::Ecra::libertaObjecto(int const numero_do_objecto)
{
    assert(1 <= numero_do_objecto and 
	   numero_do_objecto < ObjectoCor::numero_de_objectos_cor_no_s_lang);
    assert(ocupacao_dos_objectos[numero_do_objecto] != 0);

    --ocupacao_dos_objectos[numero_do_objecto];
}


bool Slang::Ecra::ja_existe_instancia = false;

bool volatile Slang::Ecra::tamanho_do_ecra_real_mudou = false;

char* Slang::Ecra::nome_de_cor_do_s_lang[numero_de_cores] = {
    "black",
    "gray",
    "red",
    "brightred",
    "green",
    "brightgreen",
    "brown",
    "yellow",
    "blue",
    "brightblue",
    "magenta",
    "brightmagenta",
    "cyan",
    "brightcyan",
    "lightgray",
    "white"
};

Slang::Ecra Slang::ecra;

string const Slang::nomes_das_cores[numero_de_cores] = {
    "preto",
    "cinza",
    "vermelho",
    "vermelho-brilhante",
    "verde",
    "verde-brilhante",
    "castanho",
    "amarelo",
    "azul",
    "azul-brilhante",
    "magenta",
    "magenta-brilhante",
    "ciano",
    "ciano-brilhante",
    "cinzento-claro",
    "branco"
};


#ifdef TESTE

#include <fstream>

using namespace Slang;

int main()
{
    Posicao p;

    assert(p == Posicao());
    assert(p == Posicao(0, 0));

    p.mudaLinhaPara(10);
    p.mudaColunaPara(20);

    assert(p == Posicao(10, 20));
    assert(p.linha() == 10);
    assert(p.coluna() == 20);

    ofstream saida("ecra.lixo");

    p.guardaEm(saida);

    saida.close();

    ifstream entrada("ecra.lixo");

    Posicao q(entrada);

    assert(p == q);

    entrada.seekg(0);

    p = Posicao(0, 0);

    assert(p == Posicao(0, 0));

    p.carregaDe(entrada);

    entrada.close();

    assert(p == q);

    p += Dimensao(-20, -10);

    assert(p == Posicao(-10, 10));

    p -= Dimensao(-20, -10);

    assert(p == q);

    assert(p + Dimensao(-20, -10) == Posicao(-10, 10));

    assert(p - Dimensao(20, 10) == Posicao(-10, 10));

    assert(Dimensao(-20, -10) + p == Posicao(-10, 10));
    
    assert(Dimensao(20, 10) - p == Posicao(10, -10));

    assert(p - Posicao(0, 0) == Dimensao(10, 20));

    assert(Posicao(0, 0) - p == Dimensao(-10, -20));

    assert(-p == Posicao(-10, -20));


    Dimensao d(p);

    assert(d == Dimensao(10, 20));

    assert(d.numeroDeLinhas() == 10);

    assert(d.numeroDeColunas() == 20);

    assert(d.eCanonica());

    d = -d;

    assert(d == Dimensao(-10, -20));

    assert(not d.eCanonica());

    d.mudaNumeroDeLinhasPara(0);

    d.mudaNumeroDeColunasPara(0);

    assert(d == Dimensao(0, 0));

    d = Dimensao(p);

    assert(d == Dimensao(10, 20));

    saida.open("ecra.lixo");

    d.guardaEm(saida);

    saida.close();

    entrada.open("ecra.lixo");

    Dimensao e(entrada);

    assert(d == e);

    entrada.seekg(0);

    d = Dimensao(0, 0);

    assert(d == Dimensao(0, 0));

    d.carregaDe(entrada);

    entrada.close();

    assert(d == e);

    d += Dimensao(-20, -10);

    assert(d == Dimensao(-10, 10));

    d -= Dimensao(-20, -10);

    assert(d == e);

    assert(d + Dimensao(-20, -10) == Dimensao(-10, 10));

    assert(d - Dimensao(20, 10) == Dimensao(-10, 10));


    Caixa c1(Posicao(10, 20), Dimensao(3, 6));
    Caixa c2(Posicao(10, 20), Posicao(12, 25));

    assert(not c1.eVazia());

    assert(c1.eCanonica());
    
    assert(c1 == c2);

    assert(c1.origem() == Posicao(10, 20));
    assert(c1.extremo() == Posicao(12, 25));
    assert(c1.dimensao() == Dimensao(3, 6));

    c1.mudaDimensaoPara(Dimensao(0, 0));

    assert(c1.eVazia());

    assert(c1.eCanonica());

    c1.mudaDimensaoPara(Dimensao(-6, -8));

    assert(not c1.eVazia());

    assert(not c1.eCanonica());

    assert(c1.extremo() == Posicao(3, 11));
    assert(c1.dimensao() == Dimensao(-6, -8));
    
    c1 += Dimensao(7, 9);

    assert(c1.dimensao() == Dimensao(-6, -8));
    assert(c1.origem() == Posicao(17, 29));

    assert((c1 + Dimensao(-7, -9)).origem() == Posicao(10, 20));
    assert((c1 - Dimensao(7, 9)).origem() == Posicao(10, 20));

    assert(c1 + c2 == Caixa(Posicao(10, 20), Posicao(12, 25)));
    assert(c1 * c2 == Caixa(Posicao(17, 29), Posicao(10, 20)));

    // Não se testam classes com interface gráfica...
}

#endif // TESTE
