/** \file ipc.H 

    Ficheiro de interface da biblioteca \c IPC++.  Usa-se se n�o se pretender
    discriminar entre os m�dulos f�sicos realmente necess�rios. */
#ifndef IPC_IPC_H
#define IPC_IPC_H

#include <IPC++/mensageiro.H>

/** \namespace IPC

    Este espa�o nominativo envolve todas as ferramentas da biblioteca \c
    IPC++.  Em particular envolve o m�dulo mensageiro.  A biblioteca \c IPC++
    permite a utiliza��o simplificada de comunica��es entre processos (IPC, de
    Inter Process Communications).  A biblioteca consiste de um pacote IPC++
    (representado pelo espa�o nominativo IPC) consistindo, para j�, apenas no
    m�dulo fisico mensageiros e no m�dulo f�sico erros, com os correspondentes
    ficheiros de interface IPC++/mensageiro.H e IPC++/erros.H.

    Para construir um programa (neste caso teste_ipc.C) que utilize estas
    biblioteca deve dar o seguinte comando:

    \verbatim
    c++ op��es_de_compila��o -o teste_ipc teste_ipc.C -lIPC++ -lUtilitarios
    \endverbatim

    A op��o \c -lIPC++ destina-se a fundir o ficheiro objecto de \c teste_ipc
    com a biblioteca \c IPC++.  A op��o \c -lUtilitarios destina-se a fundir o
    ficheiro objecto com a biblioteca \c Utilitarios, da qual a biblioteca \c
    IPC++ depende.

    Os ficheiros fonte devem incluir o ficheiro de interface IPC++/ipc.H, que
    por sua vez inclui os ficheiros de interface dos m�dulos f�sicos, ou
    incluir apenas o ficheiro de interface do m�dulo pretendido. */

#endif //IPC_IPC_H
