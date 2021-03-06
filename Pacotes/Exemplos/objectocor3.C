/** \file objectocor3.C

    Programa que demonstra que a altera��o de um objecto cor altera todas as
    c�lulas do ecr� que com ele tenham sido desenhadas.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    Ecra::ObjectoCor cor(branco, verde); 

    ecra << cor << parado << "Branco sobre verde..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    // A cor do texto j� inserido no ecr� mudar� com a altera��o do
    // correspondente objecto cor:
    cor.mudaCorDoTextoPara(vermelho);
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}
