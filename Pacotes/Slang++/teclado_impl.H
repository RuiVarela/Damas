/** \file teclado_impl.H 

    Ficheiro auxiliar de implementação do módulo teclados.

    \ingroup teclados */

#include <cassert>

extern "C" {
#include <slang.h>
}

// Definição de métodos inline da classe Tecla:

inline Slang::Tecla::Tecla(TeclaEnum tecla) 
    : tecla(tecla) {
}

inline Slang::Tecla::operator Slang::Tecla::TeclaEnum() const {
    return tecla;
}

inline char Slang::Tecla::comoChar() const 
{
    assert(eChar());

    return char(tecla);
}

inline bool Slang::Tecla::eDeDeslocamento() const 
{
    return tecla == cima or tecla == baixo or tecla == esquerda or 
	tecla == direita;
}

inline bool Slang::Tecla::eChar() const 
{
    return (32 <= tecla and tecla < 127) or (160 <= tecla and tecla < 256);
}

// Definição de métodos inline da classe Teclado:

inline Slang::Teclado::~Teclado()  {
    // Terminação do slang:
    SLang_reset_tty();
}

inline bool 
Slang::Teclado::haTeclaDisponivel(int const decimos_de_segundo) const 
{
    return SLang_input_pending(decimos_de_segundo) != 0;
}

inline Slang::Tecla Slang::Teclado::teclaLida() const 
{
    return tecla_lida;
}

inline void Slang::Teclado::leProximaTeclaDisponivel() 
{
    tecla_lida = Tecla::TeclaEnum(SLkp_getkey());
}

inline void Slang::Teclado::descartaTeclasDisponiveis() 
{
     SLang_flush_input();
}

