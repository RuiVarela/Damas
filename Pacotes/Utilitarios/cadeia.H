/** \file cadeia.H 

    Ficheiro de interface do m�dulo cadeias.

    \ingroup cadeias */
#ifndef UTILITARIOS_CADEIA_H
#define UTILITARIOS_CADEIA_H

#include <string> 

namespace Utilitarios {
    
    /** \defgroup cadeias Ferramentas complementares para cadeias de caracteres

        M�dulo correspondente ao ficheiro Utilitarios/cadeia.H. Cont�m
        ferramentas para somar valores inteiros a cadeias de caracteres. */

    /** \name Opera��es de concatena��o de cadeias de caracteres com
	inteiros. */
    //*{

    /** Acrescenta a representa��o em base decimal posicional de um inteiro a
	uma cadeia. 
    
	\pre cadeia = c.

	\post operator+= := cadeia = c + representa��o de valor. */
    template <typename Char>
    std::basic_string<Char>& operator+=(std::basic_string<Char>& cadeia, 
					int const valor);

    /** Devolve a concatena��o de uma cadeia com a representa��o na base
	decimal posicional de um inteiro. 

	\pre V.

	\post operator+ = cadeia + representa��o de valor. */
    template <typename Char>
    std::basic_string<Char> operator+(std::basic_string<Char> cadeia, 
				      int const valor);

    /** Devolve a concatena��o de uma cadeia com a representa��o na base
	decimal posicional de um inteiro. 

	\pre V.

	\post operator+ = cadeia + representa��o de valor. */
    template <typename Char>
    std::basic_string<Char> operator+(int const valor, 
				      std::basic_string<Char> cadeia);
    //*}
}

#include <Utilitarios/cadeia_impl.H>

#endif //  UTILITARIOS_CADEIA_H