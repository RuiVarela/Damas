/** \file objectocor2.C

    Programa que demonstra o efeito do tempo de vida sobre os objectos cor.
    Quando um objecto cor é destruído, as células do ecrã com ele desenhadas
    ficam "órfãs", sendo "adoptadas" logo que se constrói um novo objecto cor.
    O resultado é que podem mudar de cor.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

Ecra::ObjectoCor const cor1(verde, branco); 

void procedimento1()
{
    Ecra::ObjectoCor cor2(amarelo, azul); 

    ecra << cor2 << parado << "Amarelo sobre azul..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
} 

void procedimento2()
{
    Ecra::ObjectoCor cor3(azul, amarelo); 

    ecra << cor3 << parado << "Azul sobre amarelo..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}   

int main()
{
    ecra << cor1 << parado << "Verde sobre branco..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    procedimento1();

    procedimento2();

    Ecra::ObjectoCor cor4(branco, verde); 

    ecra << cor4 << parado << "Branco sobre verde..." << baixaCursor;
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}
