/** \file data_impl.H 

    Ficheiro auxiliar de implementação do módulo datas.

    \ingroup datas */

#include <cassert>

#include <Utilitarios/ignoradores.H>
#include <Erros/erros.H>


// Rotinas soltas:

inline bool Utilitarios::eBissexto(Ano const ano) 
{
    return ano % 4 == 0 and (ano % 100 != 0 or ano % 400 == 0);
}

inline int Utilitarios::numeroDeDiasEm(Mes const mes, Ano const ano) 
{
    assert(janeiro <= mes and mes <= dezembro);

    static int numero_de_dias[numero_total_de_meses + 1][2] = {
	{0, 0}, // lixo; não há dia 0...
	{31, 31},
	{28, 29},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31}
    };

    return numero_de_dias[mes][eBissexto(ano)];
}


// Mes:

inline Utilitarios::Mes& Utilitarios::operator++(Mes& mes) 
{
    assert(janeiro <= mes and mes <= dezembro);

    if(mes == dezembro)
	mes = janeiro;
    else
	mes = Mes(int(mes) + 1);

    return mes;
}

inline Utilitarios::Mes& Utilitarios::operator--(Mes& mes) 
{
    assert(janeiro <= mes and mes <= dezembro);

    if(mes == janeiro)
	mes = dezembro;
    else
	mes = Mes(int(mes) - 1);

    return mes;
}

inline Utilitarios::Mes Utilitarios::operator++(Mes& mes, int) 
{
    assert(janeiro <= mes and mes <= dezembro);

    Mes mes_antigo = mes;
    ++mes;

    return mes_antigo;
}

inline Utilitarios::Mes Utilitarios::operator--(Mes& mes, int) 
{
    assert(janeiro <= mes and mes <= dezembro);

    Mes mes_antigo = mes;
    --mes;

    return mes_antigo;
}

inline Utilitarios::Mes& Utilitarios::operator+=(Mes& mes, 
						 int numero_de_meses)
{
    assert(janeiro <= mes and mes <= dezembro);

    if(numero_de_meses < 0)
	numero_de_meses = numero_total_de_meses - 
	    (-numero_de_meses % numero_total_de_meses);

    mes = Mes((int(mes) - 1 + numero_de_meses) % numero_total_de_meses + 1);

    return mes;
}

inline Utilitarios::Mes& Utilitarios::operator-=(Mes& mes, 
						 int const numero_de_meses)
{
    assert(janeiro <= mes and mes <= dezembro);

    mes += -numero_de_meses;

    return mes;
}

inline Utilitarios::Mes Utilitarios::operator+(Mes mes, 
					       int const numero_de_meses)
{
    assert(janeiro <= mes and mes <= dezembro);

    mes += numero_de_meses;

    return mes;
}

inline Utilitarios::Mes Utilitarios::operator+(int const numero_de_meses, 
					       Mes mes)
{
    assert(janeiro <= mes and mes <= dezembro);

    return mes + numero_de_meses;
}

inline int Utilitarios::operator-(Mes const um_mes, Mes const outro_mes)
{
    assert(janeiro <= um_mes    and    um_mes <= dezembro and
	   janeiro <= outro_mes and outro_mes <= dezembro);

    if(um_mes >= outro_mes)
	return int(um_mes) - int(outro_mes);
    else
	return numero_total_de_meses + int(um_mes) - int(outro_mes);
}

inline Utilitarios::Mes Utilitarios::operator-(Mes mes, 
					       int const numero_de_meses) 
{
    assert(janeiro <= mes and mes <= dezembro);

    return mes + -numero_de_meses;
}

inline std::ostream& Utilitarios::operator<<(std::ostream& saida, 
					     Mes const mes) 
{
    assert(janeiro <= mes and mes <= dezembro);

    return saida << nomes_dos_meses[mes];
}


// DiaDaSemana:

inline 
Utilitarios::DiaDaSemana& Utilitarios::operator++(DiaDaSemana& dia_da_semana) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    if(dia_da_semana == sabado)
	dia_da_semana = domingo;
    else
	dia_da_semana = DiaDaSemana(int(dia_da_semana) + 1);

    return dia_da_semana;
}

inline 
Utilitarios::DiaDaSemana& Utilitarios::operator--(DiaDaSemana& dia_da_semana) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    if(dia_da_semana == domingo)
	dia_da_semana = sabado;
    else
	dia_da_semana = DiaDaSemana(int(dia_da_semana) - 1);

    return dia_da_semana;
}

inline
Utilitarios::DiaDaSemana Utilitarios::operator++(DiaDaSemana& dia_da_semana, 
						 int) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    DiaDaSemana dia_antigo = dia_da_semana;
    ++dia_da_semana;

    return dia_antigo;
}

inline 
Utilitarios::DiaDaSemana Utilitarios::operator--(DiaDaSemana& dia_da_semana, 
						 int) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    DiaDaSemana dia_antigo = dia_da_semana;
    --dia_da_semana;

    return dia_antigo;
}

inline 
Utilitarios::DiaDaSemana& Utilitarios::operator+=(DiaDaSemana& dia_da_semana, 
						  int numero_de_dias) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    if(numero_de_dias < 0)
	numero_de_dias = numero_total_de_dias_da_semana - 
	    (-numero_de_dias % numero_total_de_dias_da_semana);

    dia_da_semana = DiaDaSemana((int(dia_da_semana) + numero_de_dias) % 
				numero_total_de_dias_da_semana);

    return dia_da_semana;
}

inline 
Utilitarios::DiaDaSemana& Utilitarios::operator-=(DiaDaSemana& dia_da_semana, 
						  int const numero_de_dias) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    return dia_da_semana += -numero_de_dias;
}

inline 
Utilitarios::DiaDaSemana Utilitarios::operator+(DiaDaSemana dia_da_semana, 
						int const numero_de_dias) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    dia_da_semana += numero_de_dias;

    return dia_da_semana;
}

inline Utilitarios::DiaDaSemana 
Utilitarios::operator+(int const numero_de_dias,
		       DiaDaSemana const dia_da_semana) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    return dia_da_semana + numero_de_dias;
}

inline int Utilitarios::operator-(DiaDaSemana const um_dia_da_semana,
				  DiaDaSemana const outro_dia_da_semana)
{
    assert(domingo <= um_dia_da_semana    and    um_dia_da_semana <= sabado and
           domingo <= outro_dia_da_semana and outro_dia_da_semana <= sabado);

    if(um_dia_da_semana >= outro_dia_da_semana)
	return int(um_dia_da_semana) - int(outro_dia_da_semana);
    else
	return numero_total_de_dias_da_semana + 
	    int(um_dia_da_semana) - int(outro_dia_da_semana);
}

inline Utilitarios::DiaDaSemana 
Utilitarios::operator-(DiaDaSemana const dia_da_semana, 
		       int const numero_de_dias) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    return dia_da_semana + -numero_de_dias;
}

inline std::ostream& Utilitarios::operator<<(std::ostream& saida, 
					     DiaDaSemana const dia_da_semana) 
{
    assert(domingo <= dia_da_semana and dia_da_semana <= sabado);

    saida << nomes_dos_dias_da_semana[dia_da_semana];

    return saida;
}


// Data:

inline Utilitarios::Data::Data(Ano const ano, Mes const mes, Dia const dia) 
    : ano_(ano), mes_(mes), dia_(dia)
{
    assert(ano_minimo <= ano and 
	   janeiro <= mes and mes <= dezembro and 
	   1 <= dia and dia <= numeroDeDiasEm(mes, ano));

    assert(cumpreInvariante());
}

inline Utilitarios::Data::Data() 
    : ano_(2003), mes_(janeiro), dia_(1)
{

    assert(cumpreInvariante());
}

inline Utilitarios::Data::Data(long const dia_juliano) 
{
    long l = dia_juliano + 68569;

    long const n = (4 * l) / 146097;

    l -= (146097 * n + 3) / 4;

    long const i = (4000 * (l + 1)) / 1461001;

    l += -(1461 * i) / 4 + 31;

    long const j = (80 * l) / 2447;

    dia_ = Dia(l - (2447 * j) / 80);

    l = j / 11;

    mes_ = Mes(j + 2 - (12 * l));
    ano_ = Ano(100 * (n - 49) + i + l);

    assert(cumpreInvariante());
}

inline Utilitarios::Ano const& Utilitarios::Data::ano() const 
{
    assert(cumpreInvariante());

    return ano_;
}
      
inline Utilitarios::Mes const& Utilitarios::Data::mes() const 
{
    assert(cumpreInvariante());

    return mes_;
}
      
inline Utilitarios::Dia const& Utilitarios::Data::dia() const 
{
    assert(cumpreInvariante());

    return dia_;
}
      
inline Utilitarios::DiaDaSemana Utilitarios::Data::diaDaSemana() const 
{
    assert(cumpreInvariante());

    return DiaDaSemana((diaJuliano() + 1) % numero_total_de_dias_da_semana); 
}
      
inline long int Utilitarios::Data::diaJuliano() const 
{
    assert(cumpreInvariante());

    return ((1461 * (ano_ + 4800 + (int(mes_) - 14) / 12)) / 4 +
	    (367 * (int(mes_) - 2 - 12 * ((int(mes_) - 14) / 12))) / 12 -
	    (3 * ((ano_ + 4900 + (int(mes_) - 14) / 12) / 100)) / 4 +
	    dia_ - 32075);   
}

inline int Utilitarios::Data::numeroDeDiasNoMes() const 
{
    assert(cumpreInvariante());

    return numeroDeDiasEm(mes_, ano_);
}

inline bool Utilitarios::Data::anoEBissexto() const 
{
    assert(cumpreInvariante());

    return eBissexto(ano_);
}
      
inline Utilitarios::Data::Data(std::istream& entrada) 
{
    assert(entrada);

    int mes;

    entrada >> ano_ >> il
	    >> mes  >> il
	    >> dia_ >> il;

    if(mes < janeiro or dezembro < mes)
	throw Erros::ErroAoCarregar("Utilitarios::Data");

    mes_ = Mes(mes);

    if(not entrada or not cumpreInvariante())
	throw Erros::ErroAoCarregar("Utilitarios::Data");

    assert(cumpreInvariante());
}

inline void Utilitarios::Data::carregaDe(std::istream& entrada) 
{
    assert(cumpreInvariante());
    assert(entrada);

    *this = Data(entrada);

    assert(cumpreInvariante());
}

inline void Utilitarios::Data::guardaEm(std::ostream& saida) const 
{
    assert(cumpreInvariante());
    assert(saida);

    saida << ano_ << std::endl
	  << int(mes_) << std::endl
	  << dia_ << std::endl;

    if(not saida)
	throw Erros::ErroAoGuardar("Utilitarios::Data");
}
      
inline Utilitarios::Data& Utilitarios::Data::operator++() 
{
    assert(cumpreInvariante());

    *this += 1;

    assert(cumpreInvariante());

    return *this;
}
      
inline Utilitarios::Data& Utilitarios::Data::operator--() 
{
    assert(cumpreInvariante());
    assert(Data(ano_minimo, janeiro, 1) + 1 <= *this);

    *this -= 1;

    assert(cumpreInvariante());

    return *this;
}
      
inline Utilitarios::Data Utilitarios::Data::operator++(int) 
{
    assert(cumpreInvariante());

    Data data_anterior = *this;
    ++*this;

    assert(cumpreInvariante());

    return data_anterior;
}
      
inline Utilitarios::Data Utilitarios::Data::operator--(int) 
{
    assert(cumpreInvariante());
    assert(Data(ano_minimo, janeiro, 1) + 1 <= *this);

    Data data_anterior = *this;
    --*this;

    assert(cumpreInvariante());

    return data_anterior;
}
      
// desdeinicio: inclusive ambos atefim 
inline Utilitarios::Data& Utilitarios::Data::operator+=(Duracao const& duracao)
{
    assert(cumpreInvariante());
    assert(0 <= duracao or Data(ano_minimo, janeiro, 1) - duracao <= *this);

    *this = *this + duracao;

    assert(cumpreInvariante());

    return *this;
}
      
inline Utilitarios::Data& Utilitarios::Data::operator-=(Duracao const& duracao)
{
    assert(cumpreInvariante());
    assert(duracao <= 0 or Data(ano_minimo, janeiro, 1) + duracao <= *this);

    *this = *this - duracao;

    assert(cumpreInvariante());

    return *this;
}
      
inline void Utilitarios::Data::estabeleceDataActualPedidaAoUtilizador()
{
    data_actual_obtida_do_sistema = false;
}
      
inline void Utilitarios::Data::estabeleceDataActualObtidaDoSistema()
{
    data_actual_obtida_do_sistema = true;
}
      
inline bool Utilitarios::Data::cumpreInvariante() const 
{
    return ano_minimo <= ano_ and 
	0 < dia_ and dia_ <= numeroDeDiasEm(mes_, ano_);
}

inline bool Utilitarios::operator==(Data const& uma_data, 
				    Data const& outra_data) 
{
    return uma_data.ano() == outra_data.ano() and
	uma_data.mes() == outra_data.mes() and
	uma_data.dia() == outra_data.dia();
}

inline bool Utilitarios::operator!=(Data const& uma_data, 
				    Data const& outra_data) 
{
    return not (uma_data == outra_data);
}

inline bool Utilitarios::operator<(Data const& uma_data, 
				   Data const& outra_data) 
{
    return uma_data.diaJuliano() < outra_data.diaJuliano();
}

inline bool Utilitarios::operator>(Data const& uma_data,
				   Data const& outra_data) 
{
    return outra_data < uma_data;
}

inline bool Utilitarios::operator<=(Data const& uma_data, 
				    Data const& outra_data) 
{
    return not (uma_data > outra_data);
}

inline bool Utilitarios::operator>=(Data const& uma_data, 
				    Data const& outra_data) 
{
    return not (uma_data < outra_data);
}

inline Utilitarios::Duracao Utilitarios::operator-(Data const& uma_data, 
						   Data const& outra_data) 
{
    return uma_data.diaJuliano() - outra_data.diaJuliano();
}

inline Utilitarios::Data Utilitarios::operator-(Data const& data, 
						Duracao const& duracao) 
{
    assert(duracao <= 0 or 
	   Data(Data::ano_minimo, janeiro, 1) + duracao <= data);

    return data + -duracao;
}

inline Utilitarios::Data Utilitarios::operator+(Data const& data, 
						Duracao const& duracao) 
{
    assert(0 <= duracao or 
	   Data(Data::ano_minimo, janeiro, 1) - duracao <= data);

    return Data(data.diaJuliano() + duracao);
}

inline Utilitarios::Data Utilitarios::operator+(Duracao const& duracao, 
						Data const& data) 
{
    assert(0 <= duracao or 
	   Data(Data::ano_minimo, janeiro, 1) - duracao <= data);

    return Data(data.diaJuliano() + duracao);
}

inline std::ostream& Utilitarios::operator<<(std::ostream& saida, 
					     Data const& data) 
{
    return saida << data.ano() << '/' << int(data.mes()) << '/' << data.dia();
}
