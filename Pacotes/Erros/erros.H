/** \file erros.H 
    
    Ficheiro de interface da biblioteca \c Erros e do módulo erros.  Define as
    classe Erros::Erro, Erros::ErroAoCarregar e Erros::ErroAoGuardar.

    \ingroup erros */
#ifndef ERROS_ERROS_H
#define ERROS_ERROS_H

/** \namespace Erros

    Este espaço nominativo envolve todas as ferramentas da biblioteca \c
    Erros.  Em particular envolve o módulo erros.  A biblioteca \c Erros
    define algumas classes representando erros genéricos e erros associados ao
    armazenamento e carregamento de dados em e a partir de canais.

    Os ficheiros fonte devem incluir o ficheiro de interface Erros/erros.H. */
namespace Erros {

    /** \defgroup erros Erros genéricos

        Módulo correspondente ao ficheiro Erros/erros.H. Contém
        ferramentas para lidar com erros genéricos. */

    /** \class Erro erros.H Erros/erros.H  

	Base de uma pequena hierarquia de classes representando excepções. 

	\ingroup erros */
    class Erro {
    public:
        /** Constrói um erro guardando a mensagem de erro recebida como
            parâmetro. */
        Erro(std::string const& mensagem);

        /// Destrutor virtual para poder sofrer derivações...   
        virtual ~Erro();

        /** Inspector da mensagem explicando a origem da excepção na forma de
            uma conversão implícita para \c std::string. */
        virtual operator std::string () const;

    private:
        /// A mensagem explicando a origem da excepção.
        std::string mensagem;
    };

    /** \class ErroAoCarregar erros.H Erros/erros.H 

	Representa excepções ocorridas durante o carregamento de objectos a
	partir de canais.

	\ingroup erros */
    class ErroAoCarregar : public Erro {
    public:
        /** Constrói erro ao carregar recebendo como parâmetro o nome da
	    classe que originou a excepção. */
        ErroAoCarregar(std::string const& classe);
    };

    /** \class ErroAoGuardar erros.H Erros/erros.H 

	Representa excepções ocorridas durante o armazenamento de objectos
	usando canais.

	\ingroup erros */
    class ErroAoGuardar : public Erro {
    public:
        /** Constrói erro ao guardar recebendo como parâmetro o nome da
	    classe que originou a excepção. */
        ErroAoGuardar(std::string const& classe);
    };
}

#include <Erros/erros_impl.H>

#endif // ERROS_ERROS_H
