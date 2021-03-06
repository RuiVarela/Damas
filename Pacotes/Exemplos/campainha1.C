/** \file campainha1.C

    Este programa toca a campainha do ecr� a cada tecla premida, saindo quando
    se pressiona 's'.

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    ecra << refresca;

    while(true) {
	teclado.leProximaTeclaDisponivel();
	Tecla tecla_premida = teclado.teclaLida();

	if(tecla_premida.eChar() and tecla_premida.comoChar() == 's')
	    break;

	ecra << campainha;
    }
}
