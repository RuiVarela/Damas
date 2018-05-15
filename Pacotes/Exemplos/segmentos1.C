/** \file segmentos1.C

    Programa que demonstra a utilização de segmentos de recta horizontais e
    verticais.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    // Guardar dimensão do ecrã:
    int const altura = ecra.dimensao().numeroDeLinhas();
    int const largura = ecra.dimensao().numeroDeColunas();

    // Desenhar segmento de recta horizontal a meio do ecrã e com meia largura
    // do ecrã: 
    ecra << cursor(altura / 2, largura / 4) 
	 << segmento_horizontal(largura / 2);

    // Desenhar segmento de recta vertical a meio do ecrã e com meia altura do
    // ecrã: 
    ecra << cursor(altura / 4, largura / 2) 
	 << segmento_vertical(altura / 2);

    // Refescar e esperar por tecla:
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    ecra << apaga << refresca;
    teclado.leProximaTeclaDisponivel();

    // O mesmo, mas usando operações da classe Ecra:

    ecra << cursor(altura / 2, largura / 4);
    ecra.desenhaSegmentoHorizontalCom(largura / 2);

    ecra << cursor(altura / 4, largura / 2);
    ecra.desenhaSegmentoVerticalCom(altura / 2);

    // Refescar e esperar por tecla:
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}

