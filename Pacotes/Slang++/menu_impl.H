/** \file menu_impl.H 

    Ficheiro auxiliar de implementação do módulo menus.

    \ingroup menus */

#include <Utilitarios/localizacao.H>

// ApendiceCor:

inline Slang::ApendiceComCor::ApendiceComCor()
    : objecto_cor_da_borda(preto, branco),
      objecto_cor_do_titulo(vermelho, branco),
      objecto_cor_dos_itens(preto, branco),
      objecto_cor_do_item_corrente(amarelo, azul) 
{

    assert(cumpreInvariante());
}

inline Slang::ApendiceComCor::~ApendiceComCor()
{
    assert(cumpreInvariante());
}

inline Slang::Ecra::ObjectoCor const& 
Slang::ApendiceComCor::objectoCorDaBorda() const 
{
    assert(cumpreInvariante());

    return objecto_cor_da_borda;
}

inline Slang::Ecra::ObjectoCor const& 
Slang::ApendiceComCor::objectoCorDoTitulo() const 
{
    assert(cumpreInvariante());

    return objecto_cor_do_titulo;
}

inline Slang::Ecra::ObjectoCor const& 
Slang::ApendiceComCor::objectoCorDosItens() const 
{
    assert(cumpreInvariante());

    return objecto_cor_dos_itens;
}

inline Slang::Ecra::ObjectoCor const& 
Slang::ApendiceComCor::objectoCorDoItemCorrente() const 
{
    assert(cumpreInvariante());

    return objecto_cor_do_item_corrente;
}

inline Slang::Ecra::ObjectoCor& Slang::ApendiceComCor::objectoCorDaBorda()
{
    assert(cumpreInvariante());

    return objecto_cor_da_borda;
}

inline Slang::Ecra::ObjectoCor& Slang::ApendiceComCor::objectoCorDoTitulo()
{
    assert(cumpreInvariante());

    return objecto_cor_do_titulo;
}

inline Slang::Ecra::ObjectoCor& Slang::ApendiceComCor::objectoCorDosItens()
{
    assert(cumpreInvariante());

    return objecto_cor_dos_itens;
}

inline Slang::Ecra::ObjectoCor& 
Slang::ApendiceComCor::objectoCorDoItemCorrente()
{
    assert(cumpreInvariante());

    return objecto_cor_do_item_corrente;
}

inline bool Slang::ApendiceComCor::cumpreInvariante() const
{
    return true;
}


// Menu:

inline Slang::Menu::Menu(std::string const& titulo)
    : titulo_(titulo) 
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo));

    assert(cumpreInvariante());
}

inline Slang::Menu::~Menu() 
{
    assert(cumpreInvariante());
}

inline std::string Slang::Menu::titulo() const 
{
    assert(cumpreInvariante());

    return titulo_;
}

inline bool Slang::Menu::cumpreInvariante() const
{
    return titulo_ != "" and Utilitarios::eImprimivel(titulo_);
}


// MenuComCor:

inline Slang::MenuComCor::MenuComCor(std::string const& titulo)
    : Menu(titulo) 
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo));

}

inline Slang::MenuComCor::~MenuComCor()
{
}


// MenuSimples:

inline Slang::MenuSimples::MenuSimples(std::string const& titulo, 
				       std::string const itens[], 
				       int const numero_de_itens) 
    : MenuComCor(titulo),
      itens(itens, itens + numero_de_itens),
      numero_de_itens(numero_de_itens),
      opcao_corrente(0) 
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo) and 
	   1 <= numero_de_itens);

    for(int i = 0; i != numero_de_itens; ++i)
	assert(Utilitarios::eImprimivel(itens[i]));

    // Calcular dimensões:
    calculaDimensao();
    calculaPosicao();

    assert(cumpreInvariante());
}

inline int Slang::MenuSimples::opcaoActual() const
{
    assert(cumpreInvariante());

    return opcao_corrente;
} 

inline void Slang::MenuSimples::calculaPosicao()
{
    posicao.mudaLinhaPara((ecra.dimensao().numeroDeLinhas() - 
			   dimensao.numeroDeLinhas()) / 2);
    posicao.mudaColunaPara((ecra.dimensao().numeroDeColunas() - 
			    dimensao.numeroDeColunas()) / 2);
}

inline void Slang::MenuSimples::desenhaItem(int const numero_do_item) const 
{
    if(numero_do_item == opcao_corrente)
	ecra << objectoCorDoItemCorrente();
    else
	ecra << objectoCorDosItens();

    ecra << cursor(posicao + Dimensao(2 + numero_do_item, 1)) 
	 << largura(comprimento_maximo_dos_itens) << itens[numero_do_item];

    // Cursor no canto do ecrã:
    ecra << ecra.extremo();
}


// MenuDeCores:

inline Slang::MenuDeCores::MenuDeCores(std::string const& titulo)
    : MenuSimples(titulo, nomes_das_cores, numero_de_cores) 
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo));
}


// MenuDeSimOuNao:
inline Slang::MenuDeSimOuNao::MenuDeSimOuNao(std::string const& titulo)
    : MenuSimples(titulo, "Sim\nNão") 
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo));
}

inline int Slang::MenuDeSimOuNao::opcaoActual() const 
{
    return not MenuSimples::opcaoActual();
}


// Aviso:

inline Slang::Aviso::Aviso(std::string const& mensagem)
    : menu(mensagem, "Tá bem...") 
{
    assert(mensagem != "" and Utilitarios::eImprimivel(mensagem));

    assert(cumpreInvariante());
}

inline Slang::Aviso::~Aviso() 
{
    assert(cumpreInvariante());
}

inline void Slang::Aviso::interage() 
{
    assert(cumpreInvariante());

    menu.interage();

    assert(cumpreInvariante());
}

inline bool Slang::Aviso::cumpreInvariante() const
{
    return true;
}


// CaixaDeTexto: 

inline Slang::CaixaDeTexto::
CaixaDeTexto(std::string const& titulo,
	     std::string const& texto_inicial,
	     std::string const& caracteres_admissiveis,
	     bool impede_caixa_vazia,
	     std::string::size_type numero_de_espacos_visiveis_)
    : titulo_(titulo), 
      numero_de_espacos_visiveis(std::max(numero_de_espacos_visiveis_,
					  titulo.length())),
      texto_corrente(texto_inicial), 
      caracteres_admissiveis(caracteres_admissiveis),
      inicio_da_parte_visivel_do_texto(texto_corrente.length() < 
				       numero_de_espacos_visiveis? 
				       0 : texto_corrente.length() - 
				       numero_de_espacos_visiveis + 1),
      posicao_do_cursor_nos_espacos_visiveis(texto_corrente.length() - 
					     inicio_da_parte_visivel_do_texto),
      dimensao(4, numero_de_espacos_visiveis + 2),
      impede_caixa_vazia(impede_caixa_vazia)
{
    assert(titulo != "" and Utilitarios::eImprimivel(titulo) and 
	   1 <= numero_de_espacos_visiveis);

    calculaPosicao();

    assert(cumpreInvariante());
}

inline Slang::CaixaDeTexto::~CaixaDeTexto() 
{
    assert(cumpreInvariante());
}

inline std::string const& Slang::CaixaDeTexto::textoActual() const
{
    assert(cumpreInvariante());

    return texto_corrente;
}

inline std::string Slang::CaixaDeTexto::titulo() const 
{
    assert(cumpreInvariante());

    return titulo_;
}

inline void Slang::CaixaDeTexto::calculaPosicao()
{
    origem.mudaLinhaPara((ecra.dimensao().numeroDeLinhas() - 
			  dimensao.numeroDeLinhas()) / 2);
    origem.mudaColunaPara((ecra.dimensao().numeroDeColunas() - 
			   dimensao.numeroDeColunas()) / 2);
}

inline bool Slang::CaixaDeTexto::cumpreInvariante() const
{
    return titulo_ != "" and Utilitarios::eImprimivel(titulo_) and
	1 <= numero_de_espacos_visiveis and
	inicio_da_parte_visivel_do_texto <= texto_corrente.size() and
	posicao_do_cursor_nos_espacos_visiveis < numero_de_espacos_visiveis;
}


