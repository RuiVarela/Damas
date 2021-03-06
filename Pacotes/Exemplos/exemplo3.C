/** \file exemplo3.C

    Programa que demostra a utiliza��o do teclado e do ecr� de forma simples.
    As teclas lidas s�o escritas no ecr� atrav�s do seu c�digo e, no caso de
    correspoderem a caracteres, tamb�m na forma de caracteres (embora entre
    par�nteses).

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
