/** \file menu.C

    Ficheiro de implementação do módulo menus. Define classes que permitem usar
    menus.

    \ingroup menus */
#include <Slang++/menu.H>
#include <Slang++/teclado.H>

using namespace std;

// MenuSimples:

Slang::MenuSimples::MenuSimples(string const& titulo, 
				string const& itens_juntos) 
    : MenuComCor(titulo), opcao_corrente(0)
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo));

    // itens_juntos tem todos os itens separados por \n.  Obtê-los todos
    // separados:
    string::size_type inicio = 0;
    string::size_type fim;
    while((fim = itens_juntos.find('\n', inicio)) != string::npos) {
	if(fim - inicio != 0)
	    // Itens vazios não se põem...
	    itens.push_back(itens_juntos.substr(inicio, fim - inicio));
	inicio = fim + 1;
    }

    // Ainda pode haver um, se a última linha não terminou em '\n'!
    if(inicio < itens_juntos.length())
	itens.push_back(itens_juntos.substr(inicio));

    numero_de_itens = int(itens.size());

    assert(1 <= numero_de_itens);
    for(int i = 0; i != numero_de_itens; ++i)
	assert(Utilitarios::eImprimivel(itens[i]));
    
    calculaDimensao();
    calculaPosicao();

    assert(cumpreInvariante());
}

void Slang::MenuSimples::interage() 
{
    assert(cumpreInvariante());

    // Copiar ecrã sem menu.  
    // \todo Copiar apenas parte afectada pelo menu!
    Ecra::Troco troco = ecra.trocoDoEcraCompleto();

    // Guardar posição do cursor:
    Posicao c = ecra.posicaoDoCursor();
    
    desenha();
    desenhaItem(opcao_corrente);
    ecra << refresca;
    while(true) {
	if(ecra.foiRedimensionado()) {
	    calculaPosicao();
	    ecra.cola(troco);
	    desenha();
	    desenhaItem(opcao_corrente);
	    ecra << refresca;
	}
	if(teclado.haTeclaDisponivel(1)) {
	    teclado.leProximaTeclaDisponivel();
	    switch(teclado.teclaLida()) {
	      case Tecla::entrada:
		// Volta ao normal:
		ecra.cola(troco);
		ecra << c << fundo << refresca;
		return;
	      case Tecla::cima:
		if(opcao_corrente != 0) {
		    --opcao_corrente;
		    desenhaItem(opcao_corrente + 1);
		    desenhaItem(opcao_corrente);
		    ecra << refresca;
		}
		break;
	      case Tecla::baixo:
		if(opcao_corrente != numero_de_itens - 1) {
		    ++opcao_corrente;
		    desenhaItem(opcao_corrente - 1);
		    desenhaItem(opcao_corrente);
		    ecra << refresca;
		}
		break;
	      default:
		break;
	    }
	}
    }

    assert(cumpreInvariante());
}

void Slang::MenuSimples::calculaDimensao()
{
    comprimento_maximo_dos_itens = titulo().length();

    for(int i = 0; i != numero_de_itens; ++i)
	if(comprimento_maximo_dos_itens < itens[i].size())
	    comprimento_maximo_dos_itens = itens[i].size();

    dimensao.mudaNumeroDeLinhasPara(numero_de_itens + 3);
    dimensao.mudaNumeroDeColunasPara(comprimento_maximo_dos_itens + 2);
}

void Slang::MenuSimples::desenha() const 
{
    assert(cumpreInvariante());

    // Desenhar caixa:
    ecra << objectoCorDaBorda() << caixa(posicao, dimensao);

    // Desenhar titulo:
    ecra << objectoCorDoTitulo() << posicao + Dimensao(1, 1) 
	 << largura(comprimento_maximo_dos_itens) << titulo();
	
    // Desenhar itens:
    ecra << objectoCorDosItens();
    for(int i = 0; i != numero_de_itens; ++i)
	ecra << posicao + Dimensao(2 + i, 1) 
	     << largura(comprimento_maximo_dos_itens) << itens[i];
}

inline bool Slang::MenuSimples::cumpreInvariante() const
{
    if(not (1 <= numero_de_itens and int(itens.size()) == numero_de_itens and 
	    0 <= opcao_corrente and opcao_corrente < numero_de_itens))
	return false;

    for(int i = 0; i != numero_de_itens; ++i)
	if(not Utilitarios::eImprimivel(itens[i]))
	    return false;

    std::string::size_type comprimento_maximo = itens[0].length();
    for(int i = 1; i != numero_de_itens; ++i)
	if(comprimento_maximo < itens[i].size())
	    comprimento_maximo = itens[i].size();

    return comprimento_maximo_dos_itens == 
	std::max(comprimento_maximo, titulo().length());
}


// CaixaDeTexto:

void Slang::CaixaDeTexto::interage()
{
    assert(cumpreInvariante());

    // Copiar ecrã sem menu (Afazeres: copiar apenas parte afectada pelo
    // menu!):
    Ecra::Troco troco = ecra.trocoDoEcraCompleto();
    // Guardar posição do cursor:
    Posicao c = ecra.posicaoDoCursor();
    
    desenha();
    ecra << refresca;
    while(true) {
	if(ecra.foiRedimensionado()) {
	    calculaPosicao();
	    ecra.cola(troco);
	    desenha();
	    ecra << refresca;
	}
	if(teclado.haTeclaDisponivel(1)) {
	    teclado.leProximaTeclaDisponivel();
	    Tecla tecla = teclado.teclaLida();
	    switch(tecla) {
	      case Tecla::entrada:
		if(not impede_caixa_vazia or texto_corrente.length() != 0) {
		    // Volta ao normal:
		    ecra.cola(troco);
		    ecra << c << fundo << refresca;

		    return;
		}

		break;

	      case Tecla::esquerda:
		if(posicao_do_cursor_nos_espacos_visiveis > 0)
		    --posicao_do_cursor_nos_espacos_visiveis;
		else if(inicio_da_parte_visivel_do_texto > 0)
		    --inicio_da_parte_visivel_do_texto;
		desenha();
		ecra << refresca;

		break;

	      case Tecla::direita:
		if(posicao_do_cursor_nos_espacos_visiveis < 
		   texto_corrente.length() - inicio_da_parte_visivel_do_texto)
		    if(posicao_do_cursor_nos_espacos_visiveis < 
		       numero_de_espacos_visiveis - 1)
			++posicao_do_cursor_nos_espacos_visiveis;
		    else
			++inicio_da_parte_visivel_do_texto;
		desenha();
		ecra << refresca;

		break;

	      case Tecla::apaga:
		if(inicio_da_parte_visivel_do_texto + 
		   posicao_do_cursor_nos_espacos_visiveis < 
		   texto_corrente.length())
		    texto_corrente.
			erase(inicio_da_parte_visivel_do_texto + 
			      posicao_do_cursor_nos_espacos_visiveis, 1);
		desenha();
		ecra << refresca;

		break;

	      case Tecla::apaga_para_tras:
	      case 8 /* ctrl-H */:
		if(inicio_da_parte_visivel_do_texto + 
		   posicao_do_cursor_nos_espacos_visiveis > 0) {
		    if(posicao_do_cursor_nos_espacos_visiveis > 0)
			--posicao_do_cursor_nos_espacos_visiveis;
		    else
			--inicio_da_parte_visivel_do_texto;
		    texto_corrente.
			erase(inicio_da_parte_visivel_do_texto + 
			      posicao_do_cursor_nos_espacos_visiveis, 1);
		}
		desenha();
		ecra << refresca;

		break;

	      case Tecla::casa:
		posicao_do_cursor_nos_espacos_visiveis = 0;
		inicio_da_parte_visivel_do_texto = 0;
		desenha();
		ecra << refresca;

		break;

	      case Tecla::fim:
		if(texto_corrente.length() - inicio_da_parte_visivel_do_texto <
		   numero_de_espacos_visiveis)
		    posicao_do_cursor_nos_espacos_visiveis = 
			texto_corrente.length() - 
			inicio_da_parte_visivel_do_texto;
		else {
		    posicao_do_cursor_nos_espacos_visiveis = 
			numero_de_espacos_visiveis - 1;
		    inicio_da_parte_visivel_do_texto = 
			texto_corrente.length() - 
			numero_de_espacos_visiveis + 1;
		}
		desenha();
		ecra << refresca;

		break;

	      default:
		if(tecla.eChar() and 
		   Utilitarios::eImprimivel(tecla.comoChar()) and
		   (caracteres_admissiveis == "" or 
		    caracteres_admissiveis.find(tecla.comoChar()) != 
		    string::npos)) {
		    texto_corrente.
			insert(inicio_da_parte_visivel_do_texto + 
			       posicao_do_cursor_nos_espacos_visiveis, 1, 
			       tecla.comoChar());
		    if(posicao_do_cursor_nos_espacos_visiveis < 
		       numero_de_espacos_visiveis - 1)
			++posicao_do_cursor_nos_espacos_visiveis;
		    else
			++inicio_da_parte_visivel_do_texto;
		    desenha();
		    ecra << refresca;
		} else
		    ecra << campainha;

		break;
	    }
	}
    }

    assert(cumpreInvariante());
}

void Slang::CaixaDeTexto::desenha() const 
{
    // Desenhar caixa:
    ecra << objectoCorDaBorda() << caixa(origem, dimensao);

    // Desenhar titulo:
    ecra << objectoCorDoTitulo() << origem + Dimensao(1, 1)
	 << largura(numero_de_espacos_visiveis) << titulo();
	
    // Desenhar texto:
    ecra << objectoCorDoItemCorrente();
    ecra << origem + Dimensao(2, 1)
	 << largura(numero_de_espacos_visiveis) 
	 << texto_corrente.substr(inicio_da_parte_visivel_do_texto) 
	 << origem + Dimensao(2, 1 + posicao_do_cursor_nos_espacos_visiveis);
}


// Programa de teste:

#ifdef TESTE

int main()
{
    // Ferramentas com interface gráfica não têm testes.
}

#endif
