/** \file mensageiro1.C

    Programa que demostra a utiliza��o de mensageiros para comunicar
    entre processos.  Aten��o!  Execute duas inst�ncias (processos)
    este programa em simult�neo!  Se n�o funcionar, d� o comando:
    \verbatim
    ipcrmall
    \endverbatim

    \ingroup mensageiros */
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <IPC++/mensageiro.H>

using namespace std;
using namespace IPC;

int main() 
{
    // Se n�o se fizer isto os jogadores geram sempre o mesmo n�mero
    // aleat�rio...
    srand(time(0));

    try {
	// Construir mensageiro:
	Mensageiro mensageiro;
	
	// Escrever identifica��es:
	cout << "Eu sou o " << mensageiro.meuIdentificador() << endl;
	cout << "Ele � o " << mensageiro.identificadorDoOutro() << endl;
	
	// Gerar n�mero aleat�rio:
	int meu = rand();
	
	// Envi�-lo ao advers�rio:
	mensageiro.envia(meu);
	
	// Receber n�mero do adevers�rio:

	mensageiro.leMensagem();
	int dele = mensageiro.mensagemLida<int>();
	
	// Verificar resultado:
	if(meu < dele)
	    cout << "Perdi " << meu << " contra " << dele << "..." 
		 << endl;
	else if(meu > dele)
	    cout << "Ganhei " << meu << " contra " << dele << '!' 
		 << endl;
	else
	    cout << "Empat�mos " << meu << " a " << dele << '.' 
		 << endl;
    } catch(IPC::Erro& erro) {
	cerr << string(erro) << endl;
    }
}
