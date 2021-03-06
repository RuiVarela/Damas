/** \file slang.H 

    Ficheiro de interface da biblioteca \c Slang++.  Usa-se se n�o se
    pretender discriminar entre os m�dulos f�sicos realmente necess�rios. */
#ifndef SLANG_SLANG_H
#define SLANG_SLANG_H

#include <Slang++/ecra.H>
#include <Slang++/teclado.H>
#include <Slang++/menu.H>

/** \namespace Slang

    Este espa�o nominativo envolve todas as ferramentas da biblioteca \c
    Slang++.  Em particular envolve os m�dulos ecras, teclados e menus.  A
    biblioteca \c Slang++ permite a utiliza��o de algumas ferramentas que
    actuam sobre o teclado e o ecr� e a cria��o de menus simples em modo
    texto.  A biblioteca consiste de um pacote Slang (representado pelo espa�o
    nominativo Slang) dividido em quatro m�dulos fisicos: teclado, ecra, menu
    e util.  Cada m�dulo f�sico possui o correspondente ficheiro de interface
    (Slang++/teclado.H, Slang++/ecra.H, Slang++/menu.H e Slang++/util.H).

    Est�o definidas nesta biblioteca as vari�veis globais teclado (do tipo
    Slang::Teclado) e ecra (do tipo Slang::Ecra), n�o sendo por isso
    necess�rio criar quaisquer vari�veis destes tipos.

    Para construir um programa (neste caso teste_slang.C) que utilize estas
    biblioteca deve dar um comando com o seguinte aspecto: 

    \verbatim
    c++ op��es_de_compila��o -o teste_slang teste_slang.C -lSlang++ -lUtilitarios -lslang
    \endverbatim

    As op��es \c -lSlang++ e \c -lslang destinam-se a fundir o ficheiro
    objecto de \c teste_slang com as bibliotecas \c Slang++ e S-Lang, na qual
    \c Slang++ se baseia.  A op��o \c -lUtilitarios destina-se a fundir o
    ficheiro objecto com a biblioteca \c Utilitarios, da qual a biblioteca \c
    Slang++ depende.

    Os ficheiros fonte devem incluir o ficheiro de interface Slang++/slang.H,
    que por sua vez inclui os ficheiros de interface dos quatro m�dulos, ou
    incluir apenas o ficheiro de interface do m�dulo pretendido.

    Sempre que se pretender executar algum programa que use a biblioteca \c
    Slang++, deve-se usar uma consola \c xterm (outras consolas podem gerar
    alguns problemas). Para lan�ar uma consola \c xterm deve-se dar o comando:

    \verbatim
    xterm& 
    \endverbatim

    numa consola normal (\c Konsole). 

    Pode-se tamb�m fazer <alt-F2> e escrever \c xterm na caixa de
    di�logo que surge no ecr�. 

    \todo Verificar todos os erros do S-Lang. */

#endif // SLANG_SLANG_H
