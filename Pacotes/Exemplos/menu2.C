/** \file menu2.C

    Programa que demonstra como se usa um menu simples. 

    \ingroup menu */
#include <string> 

#include <Slang++/slang.H> 

using namespace std; 

using namespace Slang; 

int main () 
{     
    MenuSimples menu("Um menu que n�o faz nada!",
		     "Basar\n"
		     "Nao faz nada...\n"
		     "Esta tamb�m n�o!\n"
		     "Nem esta..."); 
    
    while(true) {
	menu.interage();
	
	if(menu.opcaoActual() == 0)
	    break;
	
	ecra << parado << largura(20) << menu.opcaoActual() << refresca; 
    } 
}
