/** \file localizacao.C

    Ficheiro de implementa��o do m�dulo localizacao.  Define ferramentas de
    localiza��o para portugal.

    \ingroup localizacao */
#include <Utilitarios/localizacao.H>

using namespace std;




#ifdef TESTE

#include <cassert>

using namespace std;
using namespace Utilitarios;

int main()
{
    assert(eImprimivel('�'));
    assert(eImprimivel(string("��der45678")));
    assert(eImprimivel(string("")));

    assert(not eImprimivel('\n'));
    assert(not eImprimivel(string("��de\nr45678")));
}

#endif // TESTE
