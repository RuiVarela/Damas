/** \file ecra2.C

    Programa que demostra a utiliza��o do tro�os de ecr� e respectiva c�pia e
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

    // Preenche o ecr� com um padr�o de letras:
    for(int i = 0; i != ecra.dimensao().numeroDeLinhas(); ++i) {
	ecra << cursor(i, 0);
	for(int j = 0; j != ecra.dimensao().numeroDeColunas(); ++j)
	    ecra << letras[(i * ecra.dimensao().numeroDeColunas() +
			    j) % letras.size()];
    }

    ecra << refresca;

    Aviso("Ecr� preenchido.").interage();

    // Cria uma caixa de dimens�o 10 � 20 com origem na posi��o (0, 0):
    Caixa caixa(Posicao(0, 0), Dimensao(10, 20));  
        
    // Obt�m c�pia do tro�o de ecr� que se encontra sob a caixa:
    Ecra::Troco troco = ecra.trocoDe(caixa); 

    Aviso("Tro�o copiado.  Tome aten��o �s altera��es que "
	  "ocorrer�o no ecr�!").interage();

    // Move o cursor para a posi��o (11, 21), cola o tro�o copiado acima nessa
    // posi��o e refresca o ecr� de modo a que estas modifica��es se tornem
    // vis�veis:
    ecra << cursor(11, 21) << troco << refresca;

    Aviso("Tro�o colado.  N�o viu?  Vou colar em sequ�ncia...").interage();

    for(int j = 22; j != 80; ++j) {
	// Move o cursor para a posi��o (11, j), cola o tro�o copiado acima nessa
	// posi��o e refresca o ecr� de modo a que estas modifica��es se tornem
	// vis�veis:
	ecra << cursor(11, j) << troco << refresca;
	
	// Espera 1 segundo:
	sleep(1);
    }

    Aviso("Agora viu...").interage();
}
