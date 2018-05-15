/** \file exemplo3.C

    Programa que demostra a utilização do teclado e do ecrã de forma simples.
    As teclas lidas são escritas no ecrã através do seu código e, no caso de
    correspoderem a caracteres, também na forma de caracteres (embora entre
    parênteses).

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

#include <cctype> // para isprint().

using namespace std;

int main ()
{
    ecra << refresca;

    while(true) {
	teclado.leProximaTeclaDisponivel();
        Tecla tecla_premida = teclado.teclaLida();

	ecra << int(tecla_premida);
	if(tecla_premida.eChar())
	    ecra << '(' << tecla_premida.comoChar() << ')';
	ecra << ' ' << refresca;
	if(tecla_premida == 's')
	    break;
   }
}
