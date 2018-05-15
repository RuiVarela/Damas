/** \file cadeia.H 

    Ficheiro de interface do módulo cadeias.

    \ingroup cadeias */
#ifndef UTILITARIOS_CADEIA_H
#define UTILITARIOS_CADEIA_H

#include <string> 

namespace Utilitarios {
    
    /** \defgroup cadeias Ferramentas complementares para cadeias de caracteres

        Módulo correspondente ao ficheiro Utilitarios/cadeia.H. Contém
        ferramentas para somar valores inteiros a cadeias de caracteres. */

    /** \name Operações de concatenação de cadeias de caracteres com
	inteiros. */
    //*{

    /** Acrescenta a representação em base decimal posicional de um inteiro a
	uma cadeia. 
    
	\pre cadeia = c.

	\post operator+= := cadeia = c + representação de valor. */
    template <typename Char>
    std::basic_string<Char>& operator+=(std::basic_string<Char>& cadeia, 
					int const valor);

    /** Devolve a concatenação de uma cadeia com a representação na base
	decimal posicional de um inteiro. 

	\pre V.

	\post operator+ = cadeia + representação de valor. */
    template <typename Char>
    std::basic_string<Char> operator+(std::basic_string<Char> cadeia, 
				      int const valor);

    /** Devolve a concatenação de uma cadeia com a representação na base
	decimal posicional de um inteiro. 

	\pre V.

	\post operator+ = cadeia + representação de valor. */
    template <typename Char>
    std::basic_string<Char> operator+(int const valor, 
				      std::basic_string<Char> cadeia);
    //*}
}

#include <Utilitarios/cadeia_impl.H>

#endif //  UTILITARIOS_CADEIA_H
