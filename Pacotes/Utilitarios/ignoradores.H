/** \file ignoradores.H 
    
    Ficheiro de interface do módulo ignoradores.

    \ingroup ignoradores */

#ifndef UTILITARIOS_IGNORADORES_H
#define UTILITARIOS_IGNORADORES_H

#include <iostream>

namespace Utilitarios {

    /** \defgroup ignoradores Ignoradores

	Módulo correspondente ao ficheiro Utilitarios/ignoradores.H. Contém
	manipuladores para ignorar caracteres de um canal. */

    /** \class Ignorador ignoradores.H Utilitarios/ignoradores.H

        Representa manipuladores de canais de entrada (istream) que descartam
        caracteres.

	\see Utilitatios::il
	\see Utilitarios::ill

	\ingroup ignoradores */
    class Ignorador {
    public:
	/** Constroí um ignorador de caracteres.  Este ignorador ignora todos
	    os caracteres encontrados até chegar a um #terminador.  Se
	    #deve_limpar_o_canal for verdadeira, antes de tentar ignorar
	    caracteres limpa as possíveis condições de erro do canal.

	    \pre V. */
        Ignorador(char const terminador, 
		  bool const deve_limpar_o_canal = false);

	/** Devolve o caractere que termina a sequência de caracteres
	    descartados.  I.e., serão descartados todos os caracteres
	    encontrados até se encontrar o chamado "caractere terminador.

	    \pre V.
	
	    \post terminador = caractere terminador da sequência de caracteres
	    descartados. */
	char terminador() const;

	/** Indica se o ignorador deve limpar possíveis condições de erro do
	    canal antes de descartar caracteres.

	    \pre V.

	    \post deveLimparOCanal = o ignorador deve limpar possíveis
	    condições de erro do canal antes de descartar caracteres. */
	bool deveLimparOCanal() const;

    private:
        char terminador_;
        bool deve_limpar_o_canal;
    };
    
    /** Operador de extracção para os manipuladores de ignorar/descartar
	caracteres. É usado com os manipuladores pré-definidos #il e #ill.

	\pre V.

	\post O canal #entrada foi esvaziado dos caracteres disponíveis até ao
	primeiro caractere ignorador.terminador, tendo as suas possíveis
	condições de erro sido limpas no caso de ignorador.deve_limpar_o_canal
	ser verdadeira.

	\ingroup ignoradores */
    std::istream& operator>>(std::istream& entrada, 
			     Ignorador const& ignorador);

    /**\name Manipuladores extra para std::istream

       \ingroup ignoradores */
    //@{

    /** Manipulador que descarta todos os caracteres até ao próximo
	fim-de-linha (<tt>'\\n'</tt>).  O nome é uma abreviatura de "ignora
	linha".

	Se num ficheiro estiverem guardados em linhas consecutivas um inteiro
	e o nome completo de uma passoa, pode-se tentar ler estes valores como
	se segue (admite-se que #entrada é um canal ligado ao
	ficheiro):

	\code
	int numero;
	entrada >> numero;
	string nome;
	getline(entrada, nome);
	\endcode

	Esta solução não funciona, pois o operador de extracção do inteiro
	deixa o fim-de-linha no canal, o que leva getline() a ler uma cadeia
	vazia!  A solução passa por ignorar todos os caracteres até ao
	fim-de-linha:

	\code
	#include <Slang++/util.H>

	using namespace Slang;

	...

	int numero;
	entrada >> numero >> il;
	string nome;
	getline(entrada, nome);
	\endcode

	Neste caso o ficheiro de entrada até pode possuir um comentário depois
	do inteiro, que será ignorado.  Por exemplo, o ficheiro poderia ser:

	\verbatim
	12345 Número do aluno
	Xisto Ximenes
	\endverbatim

	(Que se teria de fazer para que se pudessem colocar comentários após o
	nome?) 

	\hideinitializer */
    Ignorador const il('\n');

    /** Manipulador que descarta todos os caracteres até ao próximo
       fim-de-linha (<tt>'\\n'</tt>), mas primeiro limpa possíveis condições
       de erro do canal.  O nome é uma abreviatura de "ignora linha limpa".

       Suponha que se pretende ler do teclado um inteiro que tem de ser
       não-negativo (o número de um aluno, por exemplo).  A solução óbvia é:

       \code
       cout << "Introduza um número não negativo: ";
       int numero;
       cin >> numero;
       cout << "O número é: " << numero << endl;
       \endcode

       Esta solução tem dois problemas:

       -# Se a extracção tiver sucesso, não garante que o valor lido é
       não-negativo.
       -# Se a extracção não tiver sucesso, o canal #cin fica com uma
       condição de erro, o que faz com que todas as extracções subsequentes
       falhem.

       É importante perceber que, neste caso, se assume que ao teclado está um 
       humano, que reconhece e espera poder corrigir os seus erros!  Assim, a
       solução passa por escrever um ciclo:

       \code
       int numero;
       while(true) {
           cout << "Introduza um número não negativo: ";
           cin >> numero >> il;

           if(0 <= numero)
               break;

           cout << "Tem de ser não negativo!" << endl;
       }
       cout << "O número é: " << numero << endl;
       \endcode

       Note-se na utilização do manipulador #il, que é usado para que a
       leitura seja orientada por linha.

       Esta solução resolve o primeiro problema, mas não o segundo...  A
       solução passa por verificar também se a extração teve sucesso.  Caso
       não tenha tido sucesso, é necessário limpar a condição de erro e
       ignorar toda a linha.  Dessa forma o utilizador pode voltar a tentar
       introduzir um número:

       \code
       int numero;
       while(true) {
           cout << "Introduza um número não negativo: ";
	   cin >> numero >> il;

           if(cin.good() and numero >= 0)
               break;

           if(cin.good())
               cout << "Tem de ser não negativo!" << endl;
           else {
               cout << "Isso não é um número!" << endl;
               // Ignora resto da linha limpando condição de erro.
               cin >> ill;
           }
       }
       cout << "O número é: " << numero << endl;
       \endcode

       Idealmente esta solução seria encapsulada numa função que devolvesse o
       número e fosse parametrizada pela condição a verificar pelo valor
       (neste caso tem de ser não negativo) e pelas mensagens a escrever no
       ecrã. 

       \see il

       \hideinitializer */
    Ignorador const ill('\n', true);

    //@}
}

#include <Utilitarios/ignoradores_impl.H>

#endif // UTILITARIOS_IGNORADORES_H
