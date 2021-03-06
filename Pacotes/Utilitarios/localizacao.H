/** \file localizacao.H 
    
    Ficheiro de interface do m�dulo localizacao.

    \ingroup localizacao */

#ifndef UTILITARIOS_LOCALIZACAO_H
#define UTILITARIOS_LOCALIZACAO_H

#include <string>
#include <locale>

namespace Utilitarios {

    /** \defgroup localizacao Localiza��o para portugu�s

	M�dulo correspondente ao ficheiro Utilitarios/localizacao.H. Cont�m
	ferramentas para localiza��o para portugu�s. */

    /**\name Ferramentas de localiza��o para portugu�s.

       \ingroup localizacao */
    //@{

    /** Indica se o caractere recebido como argumento � imprim�vel de acordo
	com as conven��es portuguesas.

	\bug Se a localiza��o para portugal n�o estiver dispon�vel na m�quina,
	esta fun��o limita-se a devolver verdadeiro!

	\pre V.

	\post eImprimivel = caractere � imprim�vel de acordo com as conven��es
	portuguesas.

        \ingroup localizacao */
    template<typename C>
    bool eImprimivel(C const caractere);

    /** Indica se a cadeia de caracteres recebida como argumento � imprim�vel
	de acordo com as conven��es portuguesas.

	\bug Se a localiza��o para portugal n�o estiver dispon�vel na m�quina,
	esta fun��o limita-se a devolver verdadeiro!

	\pre V.

	\post eImprimivel = cadeia � imprim�vel de acordo com as conven��es
	portuguesas.
	
	\ingroup localizacao */
    template<typename C>
    bool eImprimivel(std::basic_string<C> const& cadeia);

    //@}
}

#include <Utilitarios/localizacao_impl.H>

#endif // UTILITARIOS_LOCALIZACAO_H
