/** \file objectocor1.C

    Programa que demostra o efeito dos objectos cor e da alter��o das suas
    cores j� depois de feitas inser��es por seu interm�dio.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    Ecra::ObjectoCor cor1(amarelo, azul); 
    Ecra::ObjectoCor cor2(azul, amarelo); 

    ecra << parado << "Cor do fundo..." << baixaCursor;
    ecra << cor1 << parado << "Amarelo sobre azul..." << baixaCursor;
    ecra << fundo << parado << "De novo cor do fundo..." << baixaCursor;

    ecra.mudaObjectoCorEmUsoPara(cor2);
    ecra << parado << "Azul sobre amarelo..." << baixaCursor;

    ecra << refresca;

    teclado.leProximaTeclaDisponivel();
}
