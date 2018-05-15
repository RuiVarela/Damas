/** \file justificacao1.C

    Programa que demostra os vários tipos de justificação e o seu efeito.

    \ingroup ecras */
#include <string>
#include <Slang++/slang.H> 
        
using namespace std; 
using namespace Slang; 
        
int main() 
{ 
    char caractere = '*';
    string cadeia("abcde");

    Ecra::ObjectoCor cor(amarelo, azul); 
        
    ecra << cor; 

    ecra << parado << largura(10) << a_esquerda << caractere << baixaCursor; 
    ecra << parado << largura(10) << ao_centro << caractere << baixaCursor; 
    ecra << parado << largura(10) << a_direita << caractere << baixaCursor; 

    ecra << parado << largura(10) << a_esquerda << cadeia << baixaCursor; 
    ecra << parado << largura(10) << ao_centro << cadeia << baixaCursor; 
    ecra << parado << largura(10) << a_direita << cadeia << baixaCursor; 

    ecra << parado << largura(3) << a_esquerda << cadeia << baixaCursor; 
    ecra << parado << largura(3) << ao_centro << cadeia << baixaCursor; 
    ecra << parado << largura(3) << a_direita << cadeia << baixaCursor; 
    
    ecra << refresca;

    teclado.leProximaTeclaDisponivel();
} 
