/** \file teclado.C

    Ficheiro de implementação do módulo teclados. Define classes que permitem
    usar o teclado.

    \ingroup teclados */
#include <Slang++/teclado.H>

void nada(int) 
{
}

Slang::Teclado::Teclado() 
    : tecla_lida(Tecla::nula)
{
    assert(not existe_instancia);

    existe_instancia = true;

    // Inicializações do slang:
    SLtt_get_terminfo();
    SLkp_init();
    if(SLang_init_tty(0, 1, 1) == -1) {
	assert(false);
    }

    SLang_set_abort_signal(nada);
}

bool Slang::Teclado::existe_instancia = false;

Slang::Teclado Slang::teclado;


#ifdef TESTE

int main()
{
    // Classes de interface gráfica não testadas.
}

#endif // TESTE
