/** \file mensageiro_impl.H 

    Ficheiro auxiliar de implementação do módulo mensageiros.

    \ingroup mensageiros */

#include <typeinfo>
#include <sstream>
#include <cerrno>
#include <cstring>

#include <Utilitarios/cadeia.H>

// Erro:
inline IPC::Erro::Erro(std::string const& mensagem) 
    : Erros::Erro(mensagem) 
{
}

inline IPC::Erro::Erro() 
    : Erros::Erro(std::string("Erro IPC: \"") + strerror(errno) + '"') 
{
}

// Mensageiro:

inline std::string IPC::Mensageiro::meuIdentificador() const
{
    using namespace Utilitarios;

    passwd* info = getpwuid(meu_UID);
    return std::string(info->pw_name) + " (" + meu_PID + ')';
}

inline std::string IPC::Mensageiro::identificadorDoOutro() const
{
    using namespace Utilitarios;

    passwd* info = getpwuid(UID_do_outro);
    return std::string(info->pw_name) + " (" + PID_do_outro + ')';
}

inline void IPC::Mensageiro::leMensagem()
{
    tipo_dos_dados = leBasico(meu_PID);
    mensagem = leBasico(meu_PID);
}

template <typename Tipo>
inline Tipo const IPC::Mensageiro::mensagemLida() const
{
    if(typeid(Tipo).name() != tipo_dos_dados)
	throw Erro("Conversão de mensagem de " + tipo_dos_dados + " para " + 
		   typeid(Tipo).name() + " impossível!");
    
    std::istringstream entrada(mensagem);
    Tipo valor;
    entrada >> valor;
    if(not entrada.good() and not entrada.eof())
	throw Erro("Problema na extracção da mensagem!");

    return valor;
}

// Especialização, para evitar que a cadeia devolvida contenha apenas a
// primeira palavra da mensagem:
template <>
inline std::string const IPC::Mensageiro::mensagemLida<std::string>() const
{
    if(typeid(std::string).name() != tipo_dos_dados)
	throw Erro("Conversão de mensagem de " + tipo_dos_dados + " para " + 
		   typeid(std::string).name() + " impossível!");
    
    return mensagem;
}

template <typename Tipo>
inline void IPC::Mensageiro::envia(Tipo& mensagem) const
{
    std::ostringstream saida;
    saida << mensagem;
    
    if(not saida.good())
	throw Erro("Problema ocorreu durante a inserção da mensagem!");

    escreveBasico(PID_do_outro, typeid(Tipo).name());
    escreveBasico(PID_do_outro, saida.str());
}

template <typename Tipo>
inline void IPC::Mensageiro::envia(Tipo const& mensagem) const
{
    std::ostringstream saida;
    saida << mensagem;
    
    if(not saida.good())
	throw Erro("Problema ocorreu durante a inserção da mensagem!");

    escreveBasico(PID_do_outro, typeid(Tipo).name());
    escreveBasico(PID_do_outro, saida.str());
}

template <typename Char>
inline void IPC::Mensageiro::envia(Char const*& mensagem) const
{
    envia(std::basic_string<Char>(mensagem));
}

template <typename Char>
inline void IPC::Mensageiro::envia(Char const* const& mensagem) const
{
    envia(std::basic_string<Char>(mensagem));
}

template <typename Char>
inline void IPC::Mensageiro::envia(Char* const& mensagem) const
{
    envia(std::basic_string<Char>(mensagem));
}

template <typename Char>
inline void IPC::Mensageiro::envia(Char*& mensagem) const
{
    envia(std::basic_string<Char>(mensagem));
}

template <typename Char, int dimensao>
inline void 
IPC::Mensageiro::envia(Char const (& mensagem)[dimensao]) const
{
    envia(std::basic_string<Char>(mensagem));
}

inline int IPC::Mensageiro::leBasicoInt(int const tipo, 
					bool const deve_esperar) const
{
    std::istringstream entrada(leBasico(tipo, deve_esperar));

    int valor;
    entrada >> valor;

    if(not entrada.good() and not entrada.eof())
	throw Erro("Problema na extracção da mensagem!");

    return valor;
}

inline void IPC::Mensageiro::escreveBasicoInt(int const tipo, int const valor) 
{
    std::ostringstream saida;

    saida << valor;

    if(not saida.good())
	throw Erro("Problema ocorreu durante a inserção da mensagem!");

    escreveBasico(tipo, saida.str());
}

inline void IPC::Mensageiro::estabeleceCaixaDoCorreio(key_t const chave)
{
    /* Usa-se por omissão o getuid() para que a comunicação entre utilizadores
       não seja possível, eliminando-se assim muitos problemas. */
    int permissoes = (chave == key_t(getuid()))? 0660 : 0666;

    // Criação de caixa do correio/obtenção de identificador de caixa
    // do correio existente:
    identificador_da_caixa_do_correio = msgget(chave, IPC_CREAT | permissoes);
    if(identificador_da_caixa_do_correio == -1)
	throw Erro();
}

inline void IPC::Mensageiro::removeCaixaDoCorreio()
{
    msgctl(identificador_da_caixa_do_correio, IPC_RMID, 0);
}

inline void IPC::Mensageiro::entraEmAcessoExclusivo() const
{
    sembuf vermelho = {0, -1, 0};
    
    if(semop(identificador_do_semaforo, &vermelho, 1) == -1)
	throw Erro();
}

inline void IPC::Mensageiro::saiDeAcessoExclusivo() const
{
    sembuf verde = {0, 1, 0};
    
    if(semop(identificador_do_semaforo, &verde, 1) == -1)
	throw Erro();
}

inline bool IPC::Mensageiro::cumpreInvariante() const
{
    return meu_PID == int(getpid()) and meu_UID == int(getuid()) and
	0 <= identificador_da_caixa_do_correio and
	0 <= identificador_do_semaforo;
}
