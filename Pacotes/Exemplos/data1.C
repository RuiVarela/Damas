/** \file data1.C

    Programa que demostra a utiliza��o de datas e tempos de forma simples.

    \ingroup datas */
#include <iostream>
	
#include <Utilitarios/data.H>
	
using namespace std;
	
using namespace Utilitarios;
	
int main()
{
    Data data(1965, setembro, 14);

    cout << "A data � " << data << '.' << endl;

    Data data_actual = Data::actual();

    cout << "A data actual � " << data_actual << '.' << endl;

    cout << "Passaram " << data_actual - data << " dias desde " 
	 << data << " at� " << data_actual << '.' << endl;

    // A partir deste ponto a data actual n�o � obtida do sistema mas sim
    // pedida ao utilizador.  Usar para depura��o!

    Data::estabeleceDataActualPedidaAoUtilizador();

    data_actual = Data::actual();

    cout << "A data actual � " << data_actual << '.' << endl;
}
