/** \file localizacao_impl.H 

    Ficheiro auxiliar de implementa��o do m�dulo localizacao.

    \ingroup localizacao */
#include <stdexcept>

template<typename C>
inline bool Utilitarios::eImprimivel(C const caractere) 
{
    try {
	std::locale const portugal("pt_PT");
	
	return std::isprint(caractere, portugal);
    } catch(std::runtime_error&) {
	// P�ssimo!  Mas que fazer?  Usar o isprint do locale "C" proibia os
	// caracteres portugueses...
	return true;
    }
}

template<typename C>
inline bool Utilitarios::eImprimivel(std::basic_string<C> const& cadeia)
{
    using namespace std;

    try {
	locale const portugal("pt_PT");
	
	return (use_facet<ctype<C> >(portugal).scan_not(ctype_base::print, 
							cadeia.c_str(), 
							cadeia.c_str() + 
							cadeia.length()) ==
		cadeia.c_str() + cadeia.length());
    } catch(runtime_error&) {
	// P�ssimo!  Mas que fazer?  Usar o isprint do locale "C" proibia os
	// caracteres portugueses...
	return true;
    }

}
