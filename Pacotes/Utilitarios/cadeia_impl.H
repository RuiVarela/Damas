/** \file cadeia_impl.H 

    Ficheiro auxiliar de implementação do módulo cadeias.

    \ingroup cadeias */

#include <sstream>

template <typename Char>
inline std::basic_string<Char>& 
Utilitarios::operator+=(std::basic_string<Char>& cadeia, int const valor) 
{
    std::basic_ostringstream<Char> saida;
    saida << valor;
    cadeia += saida.str();

    return cadeia;
}

template <typename Char>
std::basic_string<Char> Utilitarios::operator+(std::basic_string<Char> cadeia, 
					       int const valor)
{
    return cadeia += valor;
}

template <typename Char>
std::basic_string<Char> Utilitarios::operator+(int const valor, 
					       std::basic_string<Char> cadeia)
{
    return cadeia += valor;
}
