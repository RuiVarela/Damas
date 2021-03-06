/** \file erros.H 
    
    Ficheiro de interface da biblioteca \c Erros e do m�dulo erros.  Define as
    classe Erros::Erro, Erros::ErroAoCarregar e Erros::ErroAoGuardar.

    \ingroup erros */
#ifndef ERROS_ERROS_H
#define ERROS_ERROS_H

/** \namespace Erros

    Este espa�o nominativo envolve todas as ferramentas da biblioteca \c
    Erros.  Em particular envolve o m�dulo erros.  A biblioteca \c Erros
    define algumas classes representando erros gen�ricos e erros associados ao
    armazenamento e carregamento de dados em e a partir de canais.

    Os ficheiros fonte devem incluir o ficheiro de interface Erros/erros.H. */
namespace Erros {

    /** \defgroup erros Erros gen�ricos

        M�dulo correspondente ao ficheiro Erros/erros.H. Cont�m
        ferramentas para lidar com erros gen�ricos. */

    /** \class Erro erros.H Erros/erros.H  

	Base de uma pequena hierarquia de classes representando excep��es. 

	\ingroup erros */
    class Erro {
    public:
        /** Constr�i um erro guardando a mensagem de erro recebida como
            par�metro. */
        Erro(std::string const& mensagem);

        /// Destrutor virtual para poder sofrer deriva��es...   
        virtual ~Erro();

        /** Inspector da mensagem explicando a origem da excep��o na forma de
            uma convers�o impl�cita para \c std::string. */
        virtual operator std::string () const;

    private:
        /// A mensagem explicando a origem da excep��o.
        std::string mensagem;
    };

    /** \class ErroAoCarregar erros.H Erros/erros.H 

	Representa excep��es ocorridas durante o carregamento de objectos a
	partir de canais.

	\ingroup erros */
    class ErroAoCarregar : public Erro {
    public:
        /** Constr�i erro ao carregar recebendo como par�metro o nome da
	    classe que originou a excep��o. */
        ErroAoCarregar(std::string const& classe);
    };

    /** \class ErroAoGuardar erros.H Erros/erros.H 

	Representa excep��es ocorridas durante o armazenamento de objectos
	usando canais.

	\ingroup erros */
    class ErroAoGuardar : public Erro {
    public:
        /** Constr�i erro ao guardar recebendo como par�metro o nome da
	    classe que originou a excep��o. */
        ErroAoGuardar(std::string const& classe);
    };
}

#include <Erros/erros_impl.H>

#endif // ERROS_ERROS_H
