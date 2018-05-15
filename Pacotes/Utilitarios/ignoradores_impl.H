/** \file ignoradores_impl.H 

    Ficheiro auxiliar de implementação do módulo ignoradores.

    \ingroup ignoradores */

// Ignorador:

inline Utilitarios::Ignorador::Ignorador(char const terminador, 
				   bool const deve_limpar_o_canal) 
    : terminador_(terminador), 
      deve_limpar_o_canal(deve_limpar_o_canal) 
{
}

inline char Utilitarios::Ignorador::terminador() const
{
    return terminador_;
}

inline bool Utilitarios::Ignorador::deveLimparOCanal() const
{
    return deve_limpar_o_canal;
}

