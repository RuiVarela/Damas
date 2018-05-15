/** \file caixa1.C

    Programa que demostra o desenho de uma caixa no ecrã.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

// Mostra uma caixa com 1/4 da área do ecrã (metade das suas dimensões
// horizontal e vertical) centrada no ecrã.
int main()
{
    Caixa uma_caixa(Posicao(ecra.dimensao().numeroDeLinhas() / 4,
			    ecra.dimensao().numeroDeColunas() / 4),
		    Dimensao(ecra.dimensao().numeroDeLinhas() / 2,
			     ecra.dimensao().numeroDeColunas() / 2));
    
    ecra << uma_caixa << refresca;

    teclado.leProximaTeclaDisponivel();
}
