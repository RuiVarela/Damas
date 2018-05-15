/** \file mensageiro1.C

    Programa que demostra a utilização de mensageiros para comunicar
    entre processos.  Atenção!  Execute duas instâncias (processos)
    este programa em simultâneo!  Se não funcionar, dê o comando:
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
    // Se não se fizer isto os jogadores geram sempre o mesmo número
    // aleatório...
    srand(time(0));

    try {
	// Construir mensageiro:
	Mensageiro mensageiro;
	
	// Escrever identificações:
	cout << "Eu sou o " << mensageiro.meuIdentificador() << endl;
	cout << "Ele é o " << mensageiro.identificadorDoOutro() << endl;
	
	// Gerar número aleatório:
	int meu = rand();
	
	// Enviá-lo ao adversário:
	mensageiro.envia(meu);
	
	// Receber número do adeversário:

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
	    cout << "Empatámos " << meu << " a " << dele << '.' 
		 << endl;
    } catch(IPC::Erro& erro) {
	cerr << string(erro) << endl;
    }
}
