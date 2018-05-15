/** \file ignoradores.C

    Ficheiro de implementação do módulo ignoradores. Define manipuladores para
    ignorar caracteres.

    \ingroup ignoradores */
#include <Utilitarios/ignoradores.H>

using namespace std;

istream& Utilitarios::operator>>(istream& entrada, Ignorador const& ignorador) 
{
    if(ignorador.deveLimparOCanal())
	entrada.clear();

    char c;
    do
	entrada.get(c);
    while(entrada.good() and c != ignorador.terminador());

    return entrada;
}


#ifdef TESTE

#include <fstream>
#include <string>
#include <cassert>

using namespace std;
using namespace Utilitarios;

int main()
{
    ofstream saida("ignoradores.lixo");

    saida << 123 << endl
	  << "Zé" << endl
	  << "Lixo!" << endl
	  << 456 << endl;

    saida.close();

    ifstream entrada("ignoradores.lixo");

    int valor;
    entrada >> valor >> il;

    assert(valor == 123);

    string nome;
    getline(entrada, nome);

    assert(nome == "Zé");

    entrada >> valor;

#ifndef _STLP_IOSTREAM
    // O STLPort tem um erro monumental, pois altera o valor de um inteiro
    // mesmo quando a leitura falha!  Pelos vistos não têm testes de unidade
    // :-)
    assert(valor == 123);
#endif
    assert(not entrada.good());

    entrada >> ill >> valor;

    assert(valor == 456);
    assert(entrada.good());
}

#endif // TESTE

