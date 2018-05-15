/** \file simbolo1.C

    Programa que mostra os símbolos possíveis de inserir no ecrã.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    for(int s = int(diamante); s != int(diferente) + 1; ++s)
	ecra << largura(2) << Simbolo(s);

    ecra << refresca;

    teclado.leProximaTeclaDisponivel();
}
