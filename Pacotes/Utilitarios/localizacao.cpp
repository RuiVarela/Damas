/** \file localizacao.C

    Ficheiro de implementação do módulo localizacao.  Define ferramentas de
    localização para portugal.

    \ingroup localizacao */
#include <Utilitarios/localizacao.H>

using namespace std;




#ifdef TESTE

#include <cassert>

using namespace std;
using namespace Utilitarios;

int main()
{
    assert(eImprimivel('à'));
    assert(eImprimivel(string("àçder45678")));
    assert(eImprimivel(string("")));

    assert(not eImprimivel('\n'));
    assert(not eImprimivel(string("àçde\nr45678")));
}

#endif // TESTE
