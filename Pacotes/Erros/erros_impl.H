/** \file erros_impl.H 

    Ficheiro auxiliar de implementação do módulo erros.

    \ingroup erros */

// Erro:

inline Erros::Erro::Erro(std::string const& mensagem)
    : mensagem(mensagem) 
{
}

inline Erros::Erro::~Erro() 
{
}

inline Erros::Erro::operator std::string() const
{
    return mensagem;
}


// ErroAoCarregar:

inline Erros::ErroAoCarregar::ErroAoCarregar(std::string const& classe)
    : Erro("Erro ao carregar '" + classe + "'") 
{
}


// ErroAoGuardar:

inline Erros::ErroAoGuardar::ErroAoGuardar(std::string const& classe)
    : Erro(std::string("Erro ao guardar '") + classe + "'") 
{
}
