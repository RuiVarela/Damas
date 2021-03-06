/** \file exemplo2.C

    Programa que demostra a utiliza��o do ecr� e dos menus de forma simples.

    \ingroup menus */
#include <cstdlib> // para atoi().
#include <string>  // para string.

#include <Slang++/slang.H>

using namespace std;

using namespace Slang;

int main()
{
    // A defini��o dos menus e caixas de texto fora do ciclo leva a que estes
    // tenham mem�ria, preservando as escolhas do utilizador entre interac��es
    // indenpendentes:
    MenuSimples menu("Um menu que n�o faz nada...",
		     "Perguntar se sim ou n�o\n"
		     "Pedir uma cor\n"
		     "Abrir caixa para inserir texto\n"
		     "Abrir caixa para inserir n�mero\n"
		     "Sair");
    MenuDeSimOuNao menu_de_sim_ou_nao("Responda sim ou n�o:");
    MenuDeCores menu_de_cores("Escolha uma cor");
    CaixaDeTexto caixa_para_texto("Escreva um texto:");
    CaixaDeTexto caixa_para_numeros("Escreva um n�mero:", "", "0123456789", 
				    true);

    do {
	menu.interage();

	Posicao const posicao_original_do_cursor = ecra.posicaoDoCursor();

        switch(menu.opcaoActual()) {
          case 0: {
	      menu_de_sim_ou_nao.interage();

              ecra << "Escolheu: ";
              if(menu_de_sim_ou_nao.opcaoActual() == true)
                  ecra << "Sim";
              else
                  ecra << "N�o";

              break;
          }
          case 1: {
	      menu_de_cores.interage();

              ecra << "Escolheu: " << Cor(menu_de_cores.opcaoActual());

              break;
          }
          case 2: {
	      caixa_para_texto.interage();

              ecra << "Texto: " << caixa_para_texto.textoActual();

              break;
          }
          case 3: {
	      caixa_para_numeros.interage();

              ecra << "N�mero: " 
		   << atoi(caixa_para_numeros.textoActual().c_str());

              break;
          }
        }
        ecra << posicao_original_do_cursor << baixaCursor << refresca;
    } while(menu.opcaoActual() != 4);

    Aviso("Vou terminando...").interage();
}
