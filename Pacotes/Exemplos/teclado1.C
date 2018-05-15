/** \file teclado1.C

    Programa que demostra a utilização do teclado de forma simples.

    \ingroup teclados */
#include <Slang++/slang.H> 

using namespace Slang; 

#include <cctype> // para isprint().

using namespace std;

int main () 
{ 
    Ecra::ObjectoCor cor_normal(amarelo, preto); 
    Ecra::ObjectoCor cor_aviso(vermelho, preto); 
    
    while(true) { 
	if(teclado.haTeclaDisponivel(10)) { 
	    teclado.leProximaTeclaDisponivel();
	    Tecla tecla_premida = teclado.teclaLida(); 
	    
	    if(tecla_premida.eDeDeslocamento())
		ecra.moveCursorDeAcordoCom(tecla_premida); 
	    else if(tecla_premida.eChar())
		if(isprint(tecla_premida.comoChar()))
		    ecra << cor_normal << tecla_premida.comoChar();
		else
		    ecra << cor_aviso << parado 
			 << "Este nao se pode imprimir!";
	    else
		ecra << cor_aviso << parado << "Tecla inválida!"; 
	    if(tecla_premida == 's')
		break;
	} 
	ecra.refresca(); 
    }
}

