/** \file ignoradores.H 
    
    Ficheiro de interface do m�dulo ignoradores.

    \ingroup ignoradores */

#ifndef UTILITARIOS_IGNORADORES_H
#define UTILITARIOS_IGNORADORES_H

#include <iostream>

namespace Utilitarios {

    /** \defgroup ignoradores Ignoradores

	M�dulo correspondente ao ficheiro Utilitarios/ignoradores.H. Cont�m
	manipuladores para ignorar caracteres de um canal. */

    /** \class Ignorador ignoradores.H Utilitarios/ignoradores.H

        Representa manipuladores de canais de entrada (istream) que descartam
        caracteres.

	\see Utilitatios::il
	\see Utilitarios::ill

	\ingroup ignoradores */
    class Ignorador {
    public:
	/** Constro� um ignorador de caracteres.  Este ignorador ignora todos
	    os caracteres encontrados at� chegar a um #terminador.  Se
	    #deve_limpar_o_canal for verdadeira, antes de tentar ignorar
	    caracteres limpa as poss�veis condi��es de erro do canal.

	    \pre V. */
        Ignorador(char const terminador, 
		  bool const deve_limpar_o_canal = false);

	/** Devolve o caractere que termina a sequ�ncia de caracteres
	    descartados.  I.e., ser�o descartados todos os caracteres
	    encontrados at� se encontrar o chamado "caractere terminador.

	    \pre V.
	
	    \post terminador = caractere terminador da sequ�ncia de caracteres
	    descartados. */
	char terminador() const;

	/** Indica se o ignorador deve limpar poss�veis condi��es de erro do
	    canal antes de descartar caracteres.

	    \pre V.

	    \post deveLimparOCanal = o ignorador deve limpar poss�veis
	    condi��es de erro do canal antes de descartar caracteres. */
	bool deveLimparOCanal() const;

    private:
        char terminador_;
        bool deve_limpar_o_canal;
    };
    
    /** Operador de extrac��o para os manipuladores de ignorar/descartar
	caracteres. � usado com os manipuladores pr�-definidos #il e #ill.

	\pre V.

	\post O canal #entrada foi esvaziado dos caracteres dispon�veis at� ao
	primeiro caractere ignorador.terminador, tendo as suas poss�veis
	condi��es de erro sido limpas no caso de ignorador.deve_limpar_o_canal
	ser verdadeira.

	\ingroup ignoradores */
    std::istream& operator>>(std::istream& entrada, 
			     Ignorador const& ignorador);

    /**\name Manipuladores extra para std::istream

       \ingroup ignoradores */
    //@{

    /** Manipulador que descarta todos os caracteres at� ao pr�ximo
	fim-de-linha (<tt>'\\n'</tt>).  O nome � uma abreviatura de "ignora
	linha".

	Se num ficheiro estiverem guardados em linhas consecutivas um inteiro
	e o nome completo de uma passoa, pode-se tentar ler estes valores como
	se segue (admite-se que #entrada � um canal ligado ao
	ficheiro):

	\code
	int numero;
	entrada >> numero;
	string nome;
	getline(entrada, nome);
	\endcode

	Esta solu��o n�o funciona, pois o operador de extrac��o do inteiro
	deixa o fim-de-linha no canal, o que leva getline() a ler uma cadeia
	vazia!  A solu��o passa por ignorar todos os caracteres at� ao
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

	Neste caso o ficheiro de entrada at� pode possuir um coment�rio depois
	do inteiro, que ser� ignorado.  Por exemplo, o ficheiro poderia ser:

	\verbatim
	12345 N�mero do aluno
	Xisto Ximenes
	\endverbatim

	(Que se teria de fazer para que se pudessem colocar coment�rios ap�s o
	nome?) 

	\hideinitializer */
    Ignorador const il('\n');

    /** Manipulador que descarta todos os caracteres at� ao pr�ximo
       fim-de-linha (<tt>'\\n'</tt>), mas primeiro limpa poss�veis condi��es
       de erro do canal.  O nome � uma abreviatura de "ignora linha limpa".

       Suponha que se pretende ler do teclado um inteiro que tem de ser
       n�o-negativo (o n�mero de um aluno, por exemplo).  A solu��o �bvia �:

       \code
       cout << "Introduza um n�mero n�o negativo: ";
       int numero;
       cin >> numero;
       cout << "O n�mero �: " << numero << endl;
       \endcode

       Esta solu��o tem dois problemas:

       -# Se a extrac��o tiver sucesso, n�o garante que o valor lido �
       n�o-negativo.
       -# Se a extrac��o n�o tiver sucesso, o canal #cin fica com uma
       condi��o de erro, o que faz com que todas as extrac��es subsequentes
       falhem.

       � importante perceber que, neste caso, se assume que ao teclado est� um 
       humano, que reconhece e espera poder corrigir os seus erros!  Assim, a
       solu��o passa por escrever um ciclo:

       \code
       int numero;
       while(true) {
           cout << "Introduza um n�mero n�o negativo: ";
           cin >> numero >> il;

           if(0 <= numero)
               break;

           cout << "Tem de ser n�o negativo!" << endl;
       }
       cout << "O n�mero �: " << numero << endl;
       \endcode

       Note-se na utiliza��o do manipulador #il, que � usado para que a
       leitura seja orientada por linha.

       Esta solu��o resolve o primeiro problema, mas n�o o segundo...  A
       solu��o passa por verificar tamb�m se a extra��o teve sucesso.  Caso
       n�o tenha tido sucesso, � necess�rio limpar a condi��o de erro e
       ignorar toda a linha.  Dessa forma o utilizador pode voltar a tentar
       introduzir um n�mero:

       \code
       int numero;
       while(true) {
           cout << "Introduza um n�mero n�o negativo: ";
	   cin >> numero >> il;

           if(cin.good() and numero >= 0)
               break;

           if(cin.good())
               cout << "Tem de ser n�o negativo!" << endl;
           else {
               cout << "Isso n�o � um n�mero!" << endl;
               // Ignora resto da linha limpando condi��o de erro.
               cin >> ill;
           }
       }
       cout << "O n�mero �: " << numero << endl;
       \endcode

       Idealmente esta solu��o seria encapsulada numa fun��o que devolvesse o
       n�mero e fosse parametrizada pela condi��o a verificar pelo valor
       (neste caso tem de ser n�o negativo) e pelas mensagens a escrever no
       ecr�. 

       \see il

       \hideinitializer */
    Ignorador const ill('\n', true);

    //@}
}

#include <Utilitarios/ignoradores_impl.H>

#endif // UTILITARIOS_IGNORADORES_H
