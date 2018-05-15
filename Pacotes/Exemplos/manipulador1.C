/** \file manipulador1.C

    Programa que define um manipulador que move o cursor para uma posição
    arbitrária mas visível do ecrã.

    \ingroup ecras */
#include <cstdlib>

#include <Slang++/slang.H>

using namespace std;

using namespace Slang;

void cursor_aleatorio(Ecra& ecra)
{
    ecra << cursor(rand() % ecra.dimensao().numeroDeLinhas(),
		   rand() % ecra.dimensao().numeroDeColunas());
}

int main()
{
    ecra << refresca;

    while(true) {
	teclado.leProximaTeclaDisponivel();
	Tecla tecla_premida = teclado.teclaLida();

	if(tecla_premida.eChar() and tecla_premida.comoChar() == 's')
	    break;

	ecra << cursor_aleatorio << refresca;
    }
}
