/** \file ecra4.C

    Programa que demonstra que a altera��o das cores do fundo do ecr� altera
    todas as c�lulas do ecr� que com ele tenham sido desenhadas. 

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

    // A cor do texto j� inserido como fundo no ecr� mudar�:
    ecra.mudaCoresDasCelulasDoFundoPara(vermelho, branco);

    ecra << refresca;
    teclado.leProximaTeclaDisponivel();

    ecra << fundo << parado 
	 << "Mais com a cor do fundo, que passou a vermelho sobre branco...";
	 
    ecra << refresca;
    teclado.leProximaTeclaDisponivel();
}
