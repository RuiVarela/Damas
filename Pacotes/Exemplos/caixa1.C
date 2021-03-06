/** \file caixa1.C

    Programa que demostra o desenho de uma caixa no ecr�.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

// Mostra uma caixa com 1/4 da �rea do ecr� (metade das suas dimens�es
// horizontal e vertical) centrada no ecr�.
int main()
{
    Caixa uma_caixa(Posicao(ecra.dimensao().numeroDeLinhas() / 4,
			    ecra.dimensao().numeroDeColunas() / 4),
		    Dimensao(ecra.dimensao().numeroDeLinhas() / 2,
			     ecra.dimensao().numeroDeColunas() / 2));
    
    ecra << uma_caixa << refresca;

    teclado.leProximaTeclaDisponivel();
}
