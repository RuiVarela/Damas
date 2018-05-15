/** \file ecra4.C

    Programa que demonstra que a alteração das cores do fundo do ecrã altera
    todas as células do ecrã que com ele tenham sido desenhadas. 

    \ingroup ecras */
#include <Slang++/slang.H>

using namespace Slang;

int main()
{
    ecra << parado << "Cor do fundo..." << baixaCursor;

    Ecra::ObjectoCor cor(branco, verde); 
    ecra << cor << parado << "Branco sobre verde..." << baixaCursor;

    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    // A cor do texto já inserido como fundo no ecrã mudará:
    ecra.mudaCoresDasCelulasDoFundoPara(vermelho, branco);

    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    ecra << fundo << parado 
	 << "Mais com a cor do fundo, que passou a vermelho sobre branco...";
	 
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}
