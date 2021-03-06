/** \file data.H 
    
    Ficheiro de interface do m�dulo datas.

    \ingroup datas */
#ifndef UTILITARIOS_DATA_H
#define UTILITARIOS_DATA_H

#include <iostream>
#include <string>

namespace Utilitarios {

    /** \defgroup datas Ferramentas de data e tempo

        M�dulo correspondente ao ficheiro Utilitarios/data.H. Cont�m
        ferramentas para manipular data e tempo. */

    ///@name Tipos b�sicos para datas e tempos
    //@{
    
    /** Representa dura��es em dias. 
	
        As dura��es podem ser positivas ou negativas.  N�o s�o represent�veis
        dura��es superiores ao maior dos long int nem inferiores ao menor dos
        long int.  Para resolver este problema (se ele for relevante), tem de
        se mudar o tipo b�sico para outro com maior gama ou para uma classe
        desenvolvida para o efeito.

	\ingroup datas */
    typedef long Duracao;
    
    /** Representa o dia do m�s de uma data.

	\ingroup datas */
    typedef int Dia;
    
    /** Representa o ano de uma data.

	\ingroup datas */
    typedef int Ano;
    
    /** Representa os meses do ano.

	\ingroup datas */
    enum Mes {
	janeiro = 1,
	fevereiro,
	marco,
	abril,
	maio,
	junho,
	julho,
            agosto,
	setembro,
	outubro,
	novembro,
	dezembro
    };

    /** A n�mero de meses no ano.

	\ingroup datas */
    int const numero_total_de_meses = 12;

    /** Os nomes dos meses do ano.  Index�vel com o os valores enumerados do
	tipo Mes.

	\ingroup datas */
    extern std::string nomes_dos_meses[numero_total_de_meses + 1];

    /** Representa os dias da semana.

	\ingroup datas */
    enum DiaDaSemana {
	domingo = 0,
	segunda_feira,
	terca_feira,
	quarta_feira,
	quinta_feira,
	sexta_feira,
	sabado
    };
    
    /** O n�mero de dias na semana.

	\ingroup datas */
    int const numero_total_de_dias_da_semana = 7;
    
    /** Os nomes dos dias da semana.  Index�vel com o os valores enumerados do
	tipo DiaDaSemana.

	\ingroup datas */
    extern std::string 
    nomes_dos_dias_da_semana[numero_total_de_dias_da_semana];

    //@}

    ///@name Fun��es utilit�rios para c�lculo de datas.
    //@{

    /** Indica se o ano dado � bissexto.

        \pre Data::ano_minimo <= ano.
	
	\post eBissexto = ano � bissexto segundo o calend�rio gregoriano. */
    bool eBissexto(Ano const ano);
    
    /** Devolve o n�mero de dias numa dado mes de um dado ano.

        \pre Data::ano_minimo < ano.

	\post numeroDeDiasEm = n�mero de dias do m�s \a mes no ano \a ano. */
    int numeroDeDiasEm(Mes const mes, Ano const ano);
    
    //@}
    
    ///@name Opera��es associadas ao tipo Mes
    //@{

    /** Incrementa��o prefixa de meses.

        \pre mes = m.
	
	\post operator++ := mes = m�s ap�s m, passando-se de Dezembro a
	Janeiro.

	\ingroup datas */
    Mes& operator++(Mes& mes);
    
    /** Decrementa��o prefixa de meses.

        \pre mes = m.
	
	\post operator-- := mes = m�s antes de m, passando-se de Janeiro a
	Dezembro.

	\ingroup datas */
    Mes& operator--(Mes& mes);
    
    /** Incrementa��o sufixa de meses.

        \pre mes = m.
	
	\post operator++ = m e mes = m�s ap�s m, passando-se de Dezembro a
	Janeiro.

	\ingroup datas */
    Mes operator++(Mes& mes, int);
    
    /** Decrementa��o sufixa de meses.

        \pre mes = m.
	
	\post operator-- = m e mes = m�s antes de m, passando-se de Janeiro a
	Dezembro.

	\ingroup datas */
    Mes operator--(Mes& mes, int);

    /** Avan�a m�s de um n�mero de meses.

        \pre mes = m.
	
	\post operator+= := mes = m�s numero_de_meses ap�s m, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes& operator+=(Mes& mes, int const numero_de_meses);
    
    /** Recua m�s de um n�mero de meses.

        \pre mes = m.
	
	\post operator-= := mes = m�s numero_de_meses antes de m, passando-se
	de Janeiro a Dezembro.

	\ingroup datas */
    Mes& operator-=(Mes& mes, int const numero_de_meses);

    /** Devolve a adi��o de um m�s com um dado n�mero de meses.

        \pre V.
	
	\post operator+ = m�s numero_de_meses ap�s mes, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes operator+(Mes const mes, int const numero_de_meses);
    

    /** Devolve a adi��o de um m�s com um dado n�mero de meses.

        \pre V.
	
	\post operator+ = m�s numero_de_meses ap�s mes, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes operator+(int const numero_de_meses, Mes const mes);
    
    /** Devolve a dist�ncia em n�mero de meses entre dois meses.

        \pre V.
	
	\post operator- = numero_de_meses entre outro_mes e um_mes.

	\ingroup datas */
    int operator-(Mes const um_mes, Mes const outro_mes);
    
    /** Devolve a subtrac��o de um m�s de um dado n�mero de meses.

        \pre V.
	
	\post operator- = m�s numero_de_meses antes de mes, passando-se de
	Janeiro a Dezembro.

	\ingroup datas */
    Mes operator-(Mes const mes, int const numero_de_meses);
    
    /** Insere um m�s num canal.
	
        \pre V.

	\post saida cont�m o m�s (formato textual) ou n�o saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, Mes const mes);
    
    /** Extrai um m�s de um canal.
	
        \pre V.

	\post entrada.good() e j� n�o cont�m o m�s, que est� em \a mes.
	Alternativamente, n�o entrada.good().. 

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, Mes& mes);
    
    //@}
    
    ///@name Opera��es associadas ao tipo DiaDaSemana
    //@{
    
    /** Incrementa��o prefixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ := dia_de_semana = dia da semana ap�s d, passando-se
	de sabado a domingo.

	\ingroup datas */
    DiaDaSemana& operator++(DiaDaSemana& dia_da_semana);
    
    /** Decrementa��o prefixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator-- := dia_de_semana = dia da semana antes de d,
	passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana& operator--(DiaDaSemana& dia_da_semana);
    
    /** Incrementa��o sufixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ = d e dia_de_semana = dia da semana ap�s d,
	passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator++(DiaDaSemana& dia_da_semana, int);
    
    /** Incrementa��o sufixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ = d e dia_de_semana = dia da semana ap�s d,
	passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator--(DiaDaSemana& dia_da_semana, int);
    
    /** Avan�a dia da semana de um n�mero de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator+= := dia_de_semana = dia da semana
	numero_de_dias_de_semana ap�s d, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana& operator+=(DiaDaSemana& dia_da_semana, 
			    int const numero_de_dias);
    
    /** Recua dia da semana de um n�mero de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator-= := dia_de_semana = dia da semana
	numero_de_dias_de_semana antes de d, passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana& operator-=(DiaDaSemana& dia_da_semana, 
			    int const numero_de_dias);

    /** Devolve a adi��o de um dia da semana com um dado n�mero de dias da
	semana.

        \pre V.
	
	\post operator+ = dia da semana numero_de_dias_de_semana ap�s
	dia_de_semana, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator+(DiaDaSemana const dia_da_semana, 
			  int const numero_de_dias);
    
    /** Devolve a adi��o de um dia da semana com um dado n�mero de dias da
	semana.

        \pre V.
	
	\post operator+ = dia da semana numero_de_dias_de_semana ap�s
	dia_de_semana, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator+(int const numero_de_dias, 
			  DiaDaSemana const dia_da_semana);
    
    /** Devolve a dist�ncia em n�mero de dias da semana entre dois dias da
	semana.

        \pre V.
	
	\post operator- = numero_de_dias_de_semana entre outro_dia_de_semana e
	um_dia_de_semana.

	\ingroup datas */
    int operator-(DiaDaSemana const um_dia_da_semana, 
		  DiaDaSemana const outro_dia_da_semana);
    
    /** Devolve a subtrac��o de um dia da semana de um dado n�mero de dias da
	semana.

        \pre V.
	
	\post operator- = dia da semana numero_de_dias_de_semana antes de
	dia_de_semana, passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana operator-(DiaDaSemana const dia_da_semana, 
			  int const numero_de_dias);
    
    /** Insere um dia da semana num canal.
	
        \pre V.

	\post saida cont�m o dia da semana (formato textual) ou n�o
	saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, 
			     DiaDaSemana const dia_da_semana);
    
    /** Extrai um dia da semana de um canal.
	
        \pre V.

	\post entrada.good() e j� n�o cont�m o dia da semana, que est� em \a
	dia_de_semana.  Alternativamente, n�o entrada.good()..

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, 
			     DiaDaSemana& dia_da_semana);
    
    //@}

    /** \class Data data.H Utilitarios/DataTempo/data.H 

	Representa datas posteriores a 1582, i.e., datas no calend�rio
	Gregoriano, adoptado por Portugal e outros pa�ses cat�licos em 1582.
	Esta classe ainda n�o est� completa, pois n�o permite ainda o
	acrescento de meses ou anos, apenas de dias.

	Note-se que em muitos pa�ses o calend�rio gregoriano foi adoptado mais
	tarde: 1752 no Reino Unido, por exemplo.  Ver
	http://www.geocities.com/calendopaedia/gregory.htm para as datas
	precisas da mudan�a em v�rios pa�ses.
	
        Segue abaixo um pequeno exemplo de utiliza��o que se espera seja
        auto-explicativo:

	\include data1.C

	\invariant ano_minimo <= ano_ e 0 < dia_ e
	dia_ <= numeroDeDiasEm(mes_, ano_)

	\see Mes, Ano, Dia, DiaDaSemana 

	\ingroup datas */
    class Data {
    public:
        ///@name Construtores
        //@{

	/** Constr�i uma nova data com o ano, mes e dia dados.

	    \pre ano_minimo <= ano e janeiro <= mes <= fevereiro e 0
	    <= dia <= numeroDeDiasEm(mes, ano). */
	Data(Ano const ano, Mes const mes, Dia const dia);
	
	/** Constr�i por omiss�o uma data com 2003/1/1.

	    \pre V.

	    \post ano() = 2003 e mes()= janeiro e dia() = 1. */
	Data();
	
	/** Constr�i a classe a partir do dia Juliano.

            \pre dia_juliano � mesmo dia Juliano.

	    \post Data tem a data correspondente aos dias da data juliana:
	    Data(long const dia_juliano). */
	Data(long const dia_juliano);

        //@}

        ///@name Inspectores
        //@{

	/** Devolve o ano correspondente � data.

	    \pre V.

	    \post ano = ano correspondente � data. */
	Ano const& ano() const;
	
	/** Devolve o mes correspondente � data.

	    \pre V.

	    \post mes = m�s correspondente � data. */
	Mes const& mes() const;
	
	/** Devolve o dia correspondente � data.

	    \pre V.

	    \post dia = dia correspondente � data. */
	Dia const& dia() const;
	
	/** Devolve o dia da semana correspondente � data.

	    \pre V.

	    \post diaDaSemana = dia da semana correspondente � data. */
	DiaDaSemana diaDaSemana() const;
	
	/** Devolve o dia Juliano correspondente � data.  O dia
	    Juliano � o n�mero total de dias desde o meio dia de 1 de
	    Janeiro de 4713 AC.

	    \pre V.

	    \post diaJuliano = dia Juliano correspondente � data. */
	long int diaJuliano() const;

	/** Devolve o n�mero de dias no m�s e ano da data.

	    \pre V.

	    \post numeroDediasNoMes = numero de diasno m�s e ano da
	    data. */
	int numeroDeDiasNoMes() const;

	//@}
	
        ///@name Predicados
        //@{

	/** Indica se o ano da data � bissexto.

	    \pre V.

	    \post anoEBissexto = ano da data � bissexto. */
	bool anoEBissexto() const;
	
	//@}

        ///@name Serializadores
        //@{

	/** Constr�i uma data a partir de um canal de entrada.

	    \pre canal.good().

	    \post Data � a data que se encontrava no canal de entrada.

            \exception ErroAoCarregar � lan�ada se a constru��o por
            carregamento falhar.  */
	Data(std::istream& entrada);

	/** Carrega uma data a partir de um canal de entrada.

	    \pre canal.good().

	    \post *this � a data que se encontrava no canal de entrada.

            \exception ErroAoCarregar � lan�ada se o carregamento falhar. */
	void carregaDe(std::istream& entrada);

	/** Guarda os dados da data num canal de saida.

	    \pre canal.good().

	    \post *this � a data que se encontra no canal de entrada.

            \exception ErroAoGuardar � lan�ada se a constru��o por
            carregamento falhar.  */
	void guardaEm(std::ostream& saida) const;

	//@}
	
        ///@name Operadores aritm�ticos
        //@{

	/** Incrementa uma data (vers�o prefixa).

	    \pre *this = d.

	    \post operator++ := *this = d + 1. */
	Data& operator++();
	
	/** Decrementa uma data (vers�o prefixa).

	    \pre Data(ano_minimo, 1, 1) < *this e *this = d.

	    \post operator-- := *this = d - 1. */
	Data& operator--();
	
	/** Incrementa uma data (vers�o sufixa).

	    \pre *this = d.

	    \post operator++ = d e *this = d + 1. */
	Data operator++(int);
	
	/** Decrementa uma data (vers�o sufixa).

	    \pre Data(ano_minimo, 1, 1) < *this e *this = d.

	    \post operator-- = d e *this = d - 1. */
	Data operator--(int);
	
	/** Avan�a uma data de uma dada dura��o.

	    \pre Data(ano_minimo, 1, 1) + duracao <= *this e *this = d.

	    \post operator+= := *this = d + duracao. */
	Data& operator+=(Duracao const& duracao);
	
	/** Recua uma data de uma dada dura��o.

	    \pre Data(ano_minimo, 1, 1) + duracao <= *this e *this = d.

	    \post operator-= := *this = d - duracao. */
	Data& operator-=(Duracao const& duracao);
	
	//@}
	
        ///@name Opera��es de classe
        //@{

	/** Devolve a data actual.
	    
            A data actual �, por omiss�o, obtida do sistema aquando a
            invoca��o do m�todo de classe.  Mas pode ser obtida do utilizador,
            para efeitos de depura��o.

	    \pre V.

	    \post actual � a data actual no sistema ou, se a data manual
	    estiver activa, � uma data pedida ao utilizador.... */
	static Data actual();
	
	/** Faz com que a data actual seja pedida ao utilizador e n�o
	    obtida do sistema.
	    
	    �til para depura��o.

	    \pre V.

	    \post Pedidos de data actual pedem valor ao utilizador. */
	static void estabeleceDataActualPedidaAoUtilizador();
	
	/** Faz com que a data actual seja obtida do sistema e n�o
	    pedida ao utilizador.
	    
	    \pre V.

	    \post Pedidos de data actual passam a recorrer ao sistema.

	    \see estabeleceDataActualPedidaAoUtilizador(). */
	static void estabeleceDataActualObtidaDoSistema();
	
	//@}

        ///@name Constantes est�ticas
        //@{

	/** Constante que guarda o ano de in�cio do calend�rio Gregoriano: */
	static Ano const inicio_do_calendario_gregoriano = 1582;

	/** Constante que guarda o ano m�nimo das datas (poder-se-ia ser menos
	    estrito, considerando uma data m�nima de dia 15 de
	    Outubro de 1582). */
	static int const ano_minimo = inicio_do_calendario_gregoriano + 1;
	
    private:
	Ano ano_;
	Mes mes_;
	Dia dia_;
	
	static bool data_actual_obtida_do_sistema;
	
	/** Indica se a condi��o invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = ano_minimo <= ano_ and 
	    0 < dia_ and dia_ <= numeroDeDiasEm(mes_, ano_). */
	bool cumpreInvariante() const;
    };
    
    ///@name Opera��es associadas � classe Data
    //@{

    /** Indica se duas datas s�o iguais.
	
        \pre V.

	\post operador== = \a uma_data � igual a \a outra_data. 

	\ingroup datas */
    bool operator==(Data const& uma_data, Data const& outra_data);
    
    /** Indica se duas datas s�o diferentes.
	
        \pre V.

	\post operador!= = \a uma_data � diferente de \a outra_data. 

	\ingroup datas */
    bool operator!=(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data � menor que outra.
	
        \pre V.

	\post operador< = \a uma_data � menor que \a outra_data. 

	\ingroup datas */
    bool operator<(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data � maior que outra.
	
        \pre V.

	\post operador>= = \a uma_data � maior uqe \a outra_data. 

	\ingroup datas */
    bool operator>(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data � menor ou igual a outra.
	
        \pre V.

	\post operador<= = \a uma_data � menor ou igual a \a outra_data. 

	\ingroup datas */
    bool operator<=(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data � maior ou igual a outra..
	
        \pre V.

	\post operador>= = \a uma_data � maior ou igual igual a \a outra_data. 

	\ingroup datas */
    bool operator>=(Data const& uma_data, Data const& outra_data);
    
    /** Devolve a dist�ncia entre duas datas.
	
        \pre V.

	\post operador- = dist�ncia entre \a outra_data e \a uma_data, em
	dias. 

	\ingroup datas */
    Duracao operator-(Data const& uma_data, Data const& outra_data);
    
    /** Devolve a subtrac��o de uma dura��o de uma data.
	
        \pre duracao <= 0 ou Data(ano_minimo, 1, 1) + d <= data..

	\post operador- + duracao = \a data. 

	\ingroup datas */
    Data operator-(Data const& data, Duracao const& duracao);
    
    /** Devolve a adi��o de uma dura��o a uma data.
	
        \pre 0 <= duracao ou Data(ano_minimo, 1, 1) - d <= data.

	\post operador- = \a data acrescentada de \a duracao. 

	\ingroup datas */
    Data operator+(Data const& data, Duracao const& duracao);
    
    /** Devolve a adi��o de uma dura��o a uma data.
	
        \pre 0 <= duracao ou Data(ano_minimo, 1, 1) - d <= data.

	\post operador+ = \a data acrescentada de \a duracao. 

	\ingroup datas */
    Data operator+(Duracao const& duracao, Data const& data);
    
    /** Insere uma data num canal.
	
        \pre V.

	\post saida cont�m a data (a/m/d) ou n�o saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, Data const& data);
    
    /** Extrai uma data de um canal.
	
        \pre V.

	\post entrada.good() e j� n�o cont�m a data, que est� em \a data.
	Alternativamente, n�o entrada.good().. 

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, Data& data);

    //@}
}

#include <Utilitarios/data_impl.H>

#endif // UTILITARIOS_DATA_H
