/** \file menu1.C

    Programa que demostra a utilização de menus simples.

    \ingroup menus */
#include <string> 

#include <Slang++/slang.H> 

using namespace std; 

using namespace Slang; 

int main () 
{ 
    string opcoes[] = {"Basar",
		       "Nao faz nada...",
		       "Esta também não!",
		       "Nem esta..."};
    int numero_de_opcoes = sizeof(opcoes) / sizeof(string);
    
    MenuSimples menu("Um menu que não faz nada!", opcoes, numero_de_opcoes); 
    
    while(true) {
	menu.interage();
	
	if(menu.opcaoActual() == 0)
	    break;
	
	ecra << parado << largura(20) << opcoes[menu.opcaoActual()] << refresca; 
    } 
}
