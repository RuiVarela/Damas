/** \file ecra2.C

    Programa que demostra a utilização do troços de ecrã e respectiva cópia e
    colagem.

    \ingroup ecras */
#include <string>

#include <Slang++/slang.H>

extern "C" {
#include <unistd.h>  // para sleep()
}

using namespace std;

using namespace Slang;

// Este exemplo deve ser testado em janelas com pelo menos 80 colunas!
int main()
{
    string letras = "abcdefghijklmnopqrstuvwxyz";

    // Preenche o ecrã com um padrão de letras:
    for(int i = 0; i != ecra.dimensao().numeroDeLinhas(); ++i) {
	ecra << cursor(i, 0);
	for(int j = 0; j != ecra.dimensao().numeroDeColunas(); ++j)
	    ecra << letras[(i * ecra.dimensao().numeroDeColunas() +
			    j) % letras.size()];
    }

    ecra << refresca;

    Aviso("Ecrã preenchido.").interage();

    // Cria uma caixa de dimensão 10 × 20 com origem na posição (0, 0):
    Caixa caixa(Posicao(0, 0), Dimensao(10, 20));  
        
    // Obtém cópia do troço de ecrã que se encontra sob a caixa:
    Ecra::Troco troco = ecra.trocoDe(caixa); 

    Aviso("Troço copiado.  Tome atenção às alterações que "
	  "ocorrerão no ecrã!").interage();

    // Move o cursor para a posição (11, 21), cola o troço copiado acima nessa
    // posição e refresca o ecrã de modo a que estas modificações se tornem
    // visíveis:
    ecra << cursor(11, 21) << troco << refresca;

    Aviso("Troço colado.  Não viu?  Vou colar em sequência...").interage();

    for(int j = 22; j != 80; ++j) {
	// Move o cursor para a posição (11, j), cola o troço copiado acima nessa
	// posição e refresca o ecrã de modo a que estas modificações se tornem
	// visíveis:
	ecra << cursor(11, j) << troco << refresca;
	
	// Espera 1 segundo:
	sleep(1);
    }

    Aviso("Agora viu...").interage();
}
