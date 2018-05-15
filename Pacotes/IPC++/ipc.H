/** \file ipc.H 

    Ficheiro de interface da biblioteca \c IPC++.  Usa-se se não se pretender
    discriminar entre os módulos físicos realmente necessários. */
#ifndef IPC_IPC_H
#define IPC_IPC_H

#include <IPC++/mensageiro.H>

/** \namespace IPC

    Este espaço nominativo envolve todas as ferramentas da biblioteca \c
    IPC++.  Em particular envolve o módulo mensageiro.  A biblioteca \c IPC++
    permite a utilização simplificada de comunicações entre processos (IPC, de
    Inter Process Communications).  A biblioteca consiste de um pacote IPC++
    (representado pelo espaço nominativo IPC) consistindo, para já, apenas no
    módulo fisico mensageiros e no módulo físico erros, com os correspondentes
    ficheiros de interface IPC++/mensageiro.H e IPC++/erros.H.

    Para construir um programa (neste caso teste_ipc.C) que utilize estas
    biblioteca deve dar o seguinte comando:

    \verbatim
    c++ opções_de_compilação -o teste_ipc teste_ipc.C -lIPC++ -lUtilitarios
    \endverbatim

    A opção \c -lIPC++ destina-se a fundir o ficheiro objecto de \c teste_ipc
    com a biblioteca \c IPC++.  A opção \c -lUtilitarios destina-se a fundir o
    ficheiro objecto com a biblioteca \c Utilitarios, da qual a biblioteca \c
    IPC++ depende.

    Os ficheiros fonte devem incluir o ficheiro de interface IPC++/ipc.H, que
    por sua vez inclui os ficheiros de interface dos módulos físicos, ou
    incluir apenas o ficheiro de interface do módulo pretendido. */

#endif //IPC_IPC_H
