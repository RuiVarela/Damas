/** \file ecra1.C

    Programa que demostra a utiliza��o do ecr� de forma simples.

    \ingroup ecras */
#include <Slang++/slang.H> 
        
using namespace Slang; 
        
extern "C" {
#include <unistd.h>  // para sleep()
}
        
int main() 
{ 
    for(char c = 'a'; c != 'z' + 1; ++c) { 
	ecra << c << refresca; 
	sleep(1);
    } 
        
    teclado.leProximaTeclaDisponivel(); 
        
    Ecra::ObjectoCor cor(amarelo, azul); 
        
    ecra << cor << cursor(0, 0); 
    for(int c = 0; c != 10; ++c) { 
	ecra << baixaCursor << parado << largura(c) << ao_centro << c 
	     << refresca; 

	teclado.leProximaTeclaDisponivel();
    } 
} 
