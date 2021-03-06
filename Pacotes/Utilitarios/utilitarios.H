/** \file utilitarios.H 

    Ficheiro de interface da biblioteca \c Utilitarios.  Usa-se
    se n�o se pretender discriminar entre os m�dulos f�sicos realmente
    necess�rios. */
#ifndef UTILITARIOS_UTILITARIOS_H
#define UTILITARIOS_UTILITARIOS_H

#include <Utilitarios/ignoradores.H>
#include <Utilitarios/data.H>
#include <Utilitarios/cadeia.H>
#include <Utilitarios/localizacao.H>

/**  \namespace Utilitarios

    Este espa�o nominativo envolve todas as ferramentas da biblioteca \c
    Utilitarios.  Em particular envolve os m�dulos ignoradores, datas e
    cadeias.  A biblioteca \c Utilitarios cont�m utilit�rios variados, desde
    manipuladores extra para os canais de entrada e sa�da at� classes para
    representar datas.
    
    Para construir um programa (neste caso teste_data.C) que utilize esta
    biblioteca deve dar o seguinte comando:
    
    \verbatim 
    c++ op��es_de_compila��o -o teste_data teste_data.C -lUtilitarios 
    \endverbatim */

#endif // UTILITARIOS_UTILITARIOS_H
