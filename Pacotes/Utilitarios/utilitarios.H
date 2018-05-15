/** \file utilitarios.H 

    Ficheiro de interface da biblioteca \c Utilitarios.  Usa-se
    se não se pretender discriminar entre os módulos físicos realmente
    necessários. */
#ifndef UTILITARIOS_UTILITARIOS_H
#define UTILITARIOS_UTILITARIOS_H

#include <Utilitarios/ignoradores.H>
#include <Utilitarios/data.H>
#include <Utilitarios/cadeia.H>
#include <Utilitarios/localizacao.H>

/**  \namespace Utilitarios

    Este espaço nominativo envolve todas as ferramentas da biblioteca \c
    Utilitarios.  Em particular envolve os módulos ignoradores, datas e
    cadeias.  A biblioteca \c Utilitarios contém utilitários variados, desde
    manipuladores extra para os canais de entrada e saída até classes para
    representar datas.
    
    Para construir um programa (neste caso teste_data.C) que utilize esta
    biblioteca deve dar o seguinte comando:
    
    \verbatim 
    c++ opções_de_compilação -o teste_data teste_data.C -lUtilitarios 
    \endverbatim */

#endif // UTILITARIOS_UTILITARIOS_H
