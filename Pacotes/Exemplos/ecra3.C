/** \file ecra3.C

    Programa que permite ao utilizador deslocar o cursor através das setas do
    teclado, indicando em cada instante se o cursor está ou não visível.  É
    capaz de se adaptar a redimensionamentos do ecrã.

    \ingroup ecras */
#include <string>
#include <Slang++/slang.H>

using namespace std;
using namespace Slang;

int main()
{
    while(true) { 
	if(teclado.haTeclaDisponivel(10)) { 
	    teclado.leProximaTeclaDisponivel();
	    Tecla tecla_premida = teclado.teclaLida(); 
	    
	    if(tecla_premida.eDeDeslocamento())
		ecra.moveCursorDeAcordoCom(tecla_premida); 
	    else if(tecla_premida == 's')
		break;
	} 
	
	if(ecra.foiRedimensionado())
	    ecra << apaga;

	string mensagem;
	if(ecra.cursorEstaVisivel())
	    mensagem = "Visível";
	else
	    mensagem = "Invisível";

	Posicao posicao_do_cursor = ecra.posicaoDoCursor();

	ecra << cursor(ecra.dimensao().numeroDeLinhas() / 2, 0)
	     << largura(ecra.dimensao().numeroDeColunas()) << ao_centro 
	     << mensagem;

	ecra << posicao_do_cursor << refresca; 
    }
}
    
