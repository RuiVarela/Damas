/** \file localizacao.H 
    
    Ficheiro de interface do módulo localizacao.

    \ingroup localizacao */

#ifndef UTILITARIOS_LOCALIZACAO_H
#define UTILITARIOS_LOCALIZACAO_H

#include <string>
#include <locale>

namespace Utilitarios {

    /** \defgroup localizacao Localização para português

	Módulo correspondente ao ficheiro Utilitarios/localizacao.H. Contém
	ferramentas para localização para português. */

    /**\name Ferramentas de localização para português.

       \ingroup localizacao */
    //@{

    /** Indica se o caractere recebido como argumento é imprimível de acordo
	com as convenções portuguesas.

	\bug Se a localização para portugal não estiver disponível na máquina,
	esta função limita-se a devolver verdadeiro!

	\pre V.

	\post eImprimivel = caractere é imprimível de acordo com as convenções
	portuguesas.

        \ingroup localizacao */
    template<typename C>
    bool eImprimivel(C const caractere);

    /** Indica se a cadeia de caracteres recebida como argumento é imprimível
	de acordo com as convenções portuguesas.

	\bug Se a localização para portugal não estiver disponível na máquina,
	esta função limita-se a devolver verdadeiro!

	\pre V.

	\post eImprimivel = cadeia é imprimível de acordo com as convenções
	portuguesas.
	
	\ingroup localizacao */
    template<typename C>
    bool eImprimivel(std::basic_string<C> const& cadeia);

    //@}
}

#include <Utilitarios/localizacao_impl.H>

#endif // UTILITARIOS_LOCALIZACAO_H
