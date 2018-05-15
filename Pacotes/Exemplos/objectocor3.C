/** \file objectocor3.C

    Programa que demonstra que a alteração de um objecto cor altera todas as
    células do ecrã que com ele tenham sido desenhadas.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    Ecra::ObjectoCor cor(branco, verde); 

    ecra << cor << parado << "Branco sobre verde..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    // A cor do texto já inserido no ecrã mudará com a alteração do
    // correspondente objecto cor:
    cor.mudaCorDoTextoPara(vermelho);
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}
