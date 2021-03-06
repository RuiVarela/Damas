/** \file exemplo1.C

    Programa que demostra a utiliza��o simult�nea do teclado e do ecr� de
    forma simples.  Captura todas as teclas premidas at� ser premido o
    caracter 's'.  Se forem deslocamentos procede ao deslocamento respectivo
    do cursor.  Se forem caracteres escreve-os no ecr�.  Se a tecla
    pressionada corresponder a um caractere que n�o se pode imprimir no ecr� �
    mostrada uma mensagem adequada.  Se for outra tecla aparece outra mensagem
    apropriada.

    \ingroup teclados */
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

        if(tecla_premida.eDeDeslocamento()) {
            // Se for uma tecla de deslocamento, desloca:
            ecra.moveCursorDeAcordoCom(tecla_premida);
            ecra << refresca;
        } else if(tecla_premida.eChar())
            // Se for um caractere:
            if(tecla_premida.comoChar() == 's')
                // Se for 's' termina-se o ciclo:
                break;
            else if(isprint(tecla_premida.comoChar()))
                // Se for imprim�vel escreve-se:
                ecra << tecla_premida.comoChar() << refresca;
            else
                // Se n�o for avisa-se:
                ecra << parado << "Este nao se pode imprimir!" << refresca;
        else
            // Se n�o for um caractere nem tecla de deslocamento, avisa:
            ecra << parado << "Tecla inv�lida!" << refresca;
    }
}
