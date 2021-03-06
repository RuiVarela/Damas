/** \file segmentos1.C

    Programa que demonstra a utiliza��o de segmentos de recta horizontais e
    verticais.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    // Guardar dimens�o do ecr�:
    int const altura = ecra.dimensao().numeroDeLinhas();
    int const largura = ecra.dimensao().numeroDeColunas();

    // Desenhar segmento de recta horizontal a meio do ecr� e com meia largura
    // do ecr�: 
    ecra << cursor(altura / 2, largura / 4) 
	 << segmento_horizontal(largura / 2);

    // Desenhar segmento de recta vertical a meio do ecr� e com meia altura do
    // ecr�: 
    ecra << cursor(altura / 4, largura / 2) 
	 << segmento_vertical(altura / 2);

    // Refescar e esperar por tecla:
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    ecra << apaga << refresca;
    teclado.leProximaTeclaDisponivel();

    // O mesmo, mas usando opera��es da classe Ecra:

    ecra << cursor(altura / 2, largura / 4);
    ecra.desenhaSegmentoHorizontalCom(largura / 2);

    ecra << cursor(altura / 4, largura / 2);
    ecra.desenhaSegmentoVerticalCom(altura / 2);

    // Refescar e esperar por tecla:
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}

