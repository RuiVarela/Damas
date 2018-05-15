/** \file cadeia.C

    Ficheiro de implementação do módulo cadeias. Define ferramentas para somas
    valores a cadeias.

    \ingroup cadeiass */
#include <Utilitarios/cadeia.H>

#include <cassert>

using namespace std;


#ifdef TESTE

using namespace Utilitarios;

int main()
{
    assert(string("teste") + 100 == "teste100");
}

#endif // TESTE
