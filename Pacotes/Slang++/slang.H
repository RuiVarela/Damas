/** \file slang.H 

    Ficheiro de interface da biblioteca \c Slang++.  Usa-se se não se
    pretender discriminar entre os módulos físicos realmente necessários. */
#ifndef SLANG_SLANG_H
#define SLANG_SLANG_H

#include <Slang++/ecra.H>
#include <Slang++/teclado.H>
#include <Slang++/menu.H>

/** \namespace Slang

    Este espaço nominativo envolve todas as ferramentas da biblioteca \c
    Slang++.  Em particular envolve os módulos ecras, teclados e menus.  A
    biblioteca \c Slang++ permite a utilização de algumas ferramentas que
    actuam sobre o teclado e o ecrã e a criação de menus simples em modo
    texto.  A biblioteca consiste de um pacote Slang (representado pelo espaço
    nominativo Slang) dividido em quatro módulos fisicos: teclado, ecra, menu
    e util.  Cada módulo físico possui o correspondente ficheiro de interface
    (Slang++/teclado.H, Slang++/ecra.H, Slang++/menu.H e Slang++/util.H).

    Estão definidas nesta biblioteca as variáveis globais teclado (do tipo
    Slang::Teclado) e ecra (do tipo Slang::Ecra), não sendo por isso
    necessário criar quaisquer variáveis destes tipos.

    Para construir um programa (neste caso teste_slang.C) que utilize estas
    biblioteca deve dar um comando com o seguinte aspecto: 

    \verbatim
    c++ opções_de_compilação -o teste_slang teste_slang.C -lSlang++ -lUtilitarios -lslang
    \endverbatim

    As opções \c -lSlang++ e \c -lslang destinam-se a fundir o ficheiro
    objecto de \c teste_slang com as bibliotecas \c Slang++ e S-Lang, na qual
    \c Slang++ se baseia.  A opção \c -lUtilitarios destina-se a fundir o
    ficheiro objecto com a biblioteca \c Utilitarios, da qual a biblioteca \c
    Slang++ depende.

    Os ficheiros fonte devem incluir o ficheiro de interface Slang++/slang.H,
    que por sua vez inclui os ficheiros de interface dos quatro módulos, ou
    incluir apenas o ficheiro de interface do módulo pretendido.

    Sempre que se pretender executar algum programa que use a biblioteca \c
    Slang++, deve-se usar uma consola \c xterm (outras consolas podem gerar
    alguns problemas). Para lançar uma consola \c xterm deve-se dar o comando:

    \verbatim
    xterm& 
    \endverbatim

    numa consola normal (\c Konsole). 

    Pode-se também fazer <alt-F2> e escrever \c xterm na caixa de
    diálogo que surge no ecrã. 

    \todo Verificar todos os erros do S-Lang. */

#endif // SLANG_SLANG_H
