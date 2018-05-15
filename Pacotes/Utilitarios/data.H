/** \file data.H 
    
    Ficheiro de interface do módulo datas.

    \ingroup datas */
#ifndef UTILITARIOS_DATA_H
#define UTILITARIOS_DATA_H

#include <iostream>
#include <string>

namespace Utilitarios {

    /** \defgroup datas Ferramentas de data e tempo

        Módulo correspondente ao ficheiro Utilitarios/data.H. Contém
        ferramentas para manipular data e tempo. */

    ///@name Tipos básicos para datas e tempos
    //@{
    
    /** Representa durações em dias. 
	
        As durações podem ser positivas ou negativas.  Não são representáveis
        durações superiores ao maior dos long int nem inferiores ao menor dos
        long int.  Para resolver este problema (se ele for relevante), tem de
        se mudar o tipo básico para outro com maior gama ou para uma classe
        desenvolvida para o efeito.

	\ingroup datas */
    typedef long Duracao;
    
    /** Representa o dia do mês de uma data.

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

    /** A número de meses no ano.

	\ingroup datas */
    int const numero_total_de_meses = 12;

    /** Os nomes dos meses do ano.  Indexável com o os valores enumerados do
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
    
    /** O número de dias na semana.

	\ingroup datas */
    int const numero_total_de_dias_da_semana = 7;
    
    /** Os nomes dos dias da semana.  Indexável com o os valores enumerados do
	tipo DiaDaSemana.

	\ingroup datas */
    extern std::string 
    nomes_dos_dias_da_semana[numero_total_de_dias_da_semana];

    //@}

    ///@name Funções utilitários para cálculo de datas.
    //@{

    /** Indica se o ano dado é bissexto.

        \pre Data::ano_minimo <= ano.
	
	\post eBissexto = ano é bissexto segundo o calendário gregoriano. */
    bool eBissexto(Ano const ano);
    
    /** Devolve o número de dias numa dado mes de um dado ano.

        \pre Data::ano_minimo < ano.

	\post numeroDeDiasEm = número de dias do mês \a mes no ano \a ano. */
    int numeroDeDiasEm(Mes const mes, Ano const ano);
    
    //@}
    
    ///@name Operações associadas ao tipo Mes
    //@{

    /** Incrementação prefixa de meses.

        \pre mes = m.
	
	\post operator++ := mes = mês após m, passando-se de Dezembro a
	Janeiro.

	\ingroup datas */
    Mes& operator++(Mes& mes);
    
    /** Decrementação prefixa de meses.

        \pre mes = m.
	
	\post operator-- := mes = mês antes de m, passando-se de Janeiro a
	Dezembro.

	\ingroup datas */
    Mes& operator--(Mes& mes);
    
    /** Incrementação sufixa de meses.

        \pre mes = m.
	
	\post operator++ = m e mes = mês após m, passando-se de Dezembro a
	Janeiro.

	\ingroup datas */
    Mes operator++(Mes& mes, int);
    
    /** Decrementação sufixa de meses.

        \pre mes = m.
	
	\post operator-- = m e mes = mês antes de m, passando-se de Janeiro a
	Dezembro.

	\ingroup datas */
    Mes operator--(Mes& mes, int);

    /** Avança mês de um número de meses.

        \pre mes = m.
	
	\post operator+= := mes = mês numero_de_meses após m, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes& operator+=(Mes& mes, int const numero_de_meses);
    
    /** Recua mês de um número de meses.

        \pre mes = m.
	
	\post operator-= := mes = mês numero_de_meses antes de m, passando-se
	de Janeiro a Dezembro.

	\ingroup datas */
    Mes& operator-=(Mes& mes, int const numero_de_meses);

    /** Devolve a adição de um mês com um dado número de meses.

        \pre V.
	
	\post operator+ = mês numero_de_meses após mes, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes operator+(Mes const mes, int const numero_de_meses);
    

    /** Devolve a adição de um mês com um dado número de meses.

        \pre V.
	
	\post operator+ = mês numero_de_meses após mes, passando-se de
	Dezembro a Janeiro.

	\ingroup datas */
    Mes operator+(int const numero_de_meses, Mes const mes);
    
    /** Devolve a distância em número de meses entre dois meses.

        \pre V.
	
	\post operator- = numero_de_meses entre outro_mes e um_mes.

	\ingroup datas */
    int operator-(Mes const um_mes, Mes const outro_mes);
    
    /** Devolve a subtracção de um mês de um dado número de meses.

        \pre V.
	
	\post operator- = mês numero_de_meses antes de mes, passando-se de
	Janeiro a Dezembro.

	\ingroup datas */
    Mes operator-(Mes const mes, int const numero_de_meses);
    
    /** Insere um mês num canal.
	
        \pre V.

	\post saida contém o mês (formato textual) ou não saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, Mes const mes);
    
    /** Extrai um mês de um canal.
	
        \pre V.

	\post entrada.good() e já não contém o mês, que está em \a mes.
	Alternativamente, não entrada.good().. 

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, Mes& mes);
    
    //@}
    
    ///@name Operações associadas ao tipo DiaDaSemana
    //@{
    
    /** Incrementação prefixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ := dia_de_semana = dia da semana após d, passando-se
	de sabado a domingo.

	\ingroup datas */
    DiaDaSemana& operator++(DiaDaSemana& dia_da_semana);
    
    /** Decrementação prefixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator-- := dia_de_semana = dia da semana antes de d,
	passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana& operator--(DiaDaSemana& dia_da_semana);
    
    /** Incrementação sufixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ = d e dia_de_semana = dia da semana após d,
	passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator++(DiaDaSemana& dia_da_semana, int);
    
    /** Incrementação sufixa de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator++ = d e dia_de_semana = dia da semana após d,
	passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator--(DiaDaSemana& dia_da_semana, int);
    
    /** Avança dia da semana de um número de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator+= := dia_de_semana = dia da semana
	numero_de_dias_de_semana após d, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana& operator+=(DiaDaSemana& dia_da_semana, 
			    int const numero_de_dias);
    
    /** Recua dia da semana de um número de dias da semana.

        \pre dia_de_semana = d.
	
	\post operator-= := dia_de_semana = dia da semana
	numero_de_dias_de_semana antes de d, passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana& operator-=(DiaDaSemana& dia_da_semana, 
			    int const numero_de_dias);

    /** Devolve a adição de um dia da semana com um dado número de dias da
	semana.

        \pre V.
	
	\post operator+ = dia da semana numero_de_dias_de_semana após
	dia_de_semana, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator+(DiaDaSemana const dia_da_semana, 
			  int const numero_de_dias);
    
    /** Devolve a adição de um dia da semana com um dado número de dias da
	semana.

        \pre V.
	
	\post operator+ = dia da semana numero_de_dias_de_semana após
	dia_de_semana, passando-se de sabado a domingo.

	\ingroup datas */
    DiaDaSemana operator+(int const numero_de_dias, 
			  DiaDaSemana const dia_da_semana);
    
    /** Devolve a distância em número de dias da semana entre dois dias da
	semana.

        \pre V.
	
	\post operator- = numero_de_dias_de_semana entre outro_dia_de_semana e
	um_dia_de_semana.

	\ingroup datas */
    int operator-(DiaDaSemana const um_dia_da_semana, 
		  DiaDaSemana const outro_dia_da_semana);
    
    /** Devolve a subtracção de um dia da semana de um dado número de dias da
	semana.

        \pre V.
	
	\post operator- = dia da semana numero_de_dias_de_semana antes de
	dia_de_semana, passando-se de domingo a sabado.

	\ingroup datas */
    DiaDaSemana operator-(DiaDaSemana const dia_da_semana, 
			  int const numero_de_dias);
    
    /** Insere um dia da semana num canal.
	
        \pre V.

	\post saida contém o dia da semana (formato textual) ou não
	saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, 
			     DiaDaSemana const dia_da_semana);
    
    /** Extrai um dia da semana de um canal.
	
        \pre V.

	\post entrada.good() e já não contém o dia da semana, que está em \a
	dia_de_semana.  Alternativamente, não entrada.good()..

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, 
			     DiaDaSemana& dia_da_semana);
    
    //@}

    /** \class Data data.H Utilitarios/DataTempo/data.H 

	Representa datas posteriores a 1582, i.e., datas no calendário
	Gregoriano, adoptado por Portugal e outros países católicos em 1582.
	Esta classe ainda não está completa, pois não permite ainda o
	acrescento de meses ou anos, apenas de dias.

	Note-se que em muitos países o calendário gregoriano foi adoptado mais
	tarde: 1752 no Reino Unido, por exemplo.  Ver
	http://www.geocities.com/calendopaedia/gregory.htm para as datas
	precisas da mudança em vários países.
	
        Segue abaixo um pequeno exemplo de utilização que se espera seja
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

	/** Constrói uma nova data com o ano, mes e dia dados.

	    \pre ano_minimo <= ano e janeiro <= mes <= fevereiro e 0
	    <= dia <= numeroDeDiasEm(mes, ano). */
	Data(Ano const ano, Mes const mes, Dia const dia);
	
	/** Constrói por omissão uma data com 2003/1/1.

	    \pre V.

	    \post ano() = 2003 e mes()= janeiro e dia() = 1. */
	Data();
	
	/** Constrói a classe a partir do dia Juliano.

            \pre dia_juliano é mesmo dia Juliano.

	    \post Data tem a data correspondente aos dias da data juliana:
	    Data(long const dia_juliano). */
	Data(long const dia_juliano);

        //@}

        ///@name Inspectores
        //@{

	/** Devolve o ano correspondente à data.

	    \pre V.

	    \post ano = ano correspondente à data. */
	Ano const& ano() const;
	
	/** Devolve o mes correspondente à data.

	    \pre V.

	    \post mes = mês correspondente à data. */
	Mes const& mes() const;
	
	/** Devolve o dia correspondente à data.

	    \pre V.

	    \post dia = dia correspondente à data. */
	Dia const& dia() const;
	
	/** Devolve o dia da semana correspondente à data.

	    \pre V.

	    \post diaDaSemana = dia da semana correspondente à data. */
	DiaDaSemana diaDaSemana() const;
	
	/** Devolve o dia Juliano correspondente à data.  O dia
	    Juliano é o número total de dias desde o meio dia de 1 de
	    Janeiro de 4713 AC.

	    \pre V.

	    \post diaJuliano = dia Juliano correspondente à data. */
	long int diaJuliano() const;

	/** Devolve o número de dias no mês e ano da data.

	    \pre V.

	    \post numeroDediasNoMes = numero de diasno mês e ano da
	    data. */
	int numeroDeDiasNoMes() const;

	//@}
	
        ///@name Predicados
        //@{

	/** Indica se o ano da data é bissexto.

	    \pre V.

	    \post anoEBissexto = ano da data é bissexto. */
	bool anoEBissexto() const;
	
	//@}

        ///@name Serializadores
        //@{

	/** Constrói uma data a partir de um canal de entrada.

	    \pre canal.good().

	    \post Data é a data que se encontrava no canal de entrada.

            \exception ErroAoCarregar é lançada se a construção por
            carregamento falhar.  */
	Data(std::istream& entrada);

	/** Carrega uma data a partir de um canal de entrada.

	    \pre canal.good().

	    \post *this é a data que se encontrava no canal de entrada.

            \exception ErroAoCarregar é lançada se o carregamento falhar. */
	void carregaDe(std::istream& entrada);

	/** Guarda os dados da data num canal de saida.

	    \pre canal.good().

	    \post *this é a data que se encontra no canal de entrada.

            \exception ErroAoGuardar é lançada se a construção por
            carregamento falhar.  */
	void guardaEm(std::ostream& saida) const;

	//@}
	
        ///@name Operadores aritméticos
        //@{

	/** Incrementa uma data (versão prefixa).

	    \pre *this = d.

	    \post operator++ := *this = d + 1. */
	Data& operator++();
	
	/** Decrementa uma data (versão prefixa).

	    \pre Data(ano_minimo, 1, 1) < *this e *this = d.

	    \post operator-- := *this = d - 1. */
	Data& operator--();
	
	/** Incrementa uma data (versão sufixa).

	    \pre *this = d.

	    \post operator++ = d e *this = d + 1. */
	Data operator++(int);
	
	/** Decrementa uma data (versão sufixa).

	    \pre Data(ano_minimo, 1, 1) < *this e *this = d.

	    \post operator-- = d e *this = d - 1. */
	Data operator--(int);
	
	/** Avança uma data de uma dada duração.

	    \pre Data(ano_minimo, 1, 1) + duracao <= *this e *this = d.

	    \post operator+= := *this = d + duracao. */
	Data& operator+=(Duracao const& duracao);
	
	/** Recua uma data de uma dada duração.

	    \pre Data(ano_minimo, 1, 1) + duracao <= *this e *this = d.

	    \post operator-= := *this = d - duracao. */
	Data& operator-=(Duracao const& duracao);
	
	//@}
	
        ///@name Operações de classe
        //@{

	/** Devolve a data actual.
	    
            A data actual é, por omissão, obtida do sistema aquando a
            invocação do método de classe.  Mas pode ser obtida do utilizador,
            para efeitos de depuração.

	    \pre V.

	    \post actual é a data actual no sistema ou, se a data manual
	    estiver activa, é uma data pedida ao utilizador.... */
	static Data actual();
	
	/** Faz com que a data actual seja pedida ao utilizador e não
	    obtida do sistema.
	    
	    Útil para depuração.

	    \pre V.

	    \post Pedidos de data actual pedem valor ao utilizador. */
	static void estabeleceDataActualPedidaAoUtilizador();
	
	/** Faz com que a data actual seja obtida do sistema e não
	    pedida ao utilizador.
	    
	    \pre V.

	    \post Pedidos de data actual passam a recorrer ao sistema.

	    \see estabeleceDataActualPedidaAoUtilizador(). */
	static void estabeleceDataActualObtidaDoSistema();
	
	//@}

        ///@name Constantes estáticas
        //@{

	/** Constante que guarda o ano de início do calendário Gregoriano: */
	static Ano const inicio_do_calendario_gregoriano = 1582;

	/** Constante que guarda o ano mínimo das datas (poder-se-ia ser menos
	    estrito, considerando uma data mínima de dia 15 de
	    Outubro de 1582). */
	static int const ano_minimo = inicio_do_calendario_gregoriano + 1;
	
    private:
	Ano ano_;
	Mes mes_;
	Dia dia_;
	
	static bool data_actual_obtida_do_sistema;
	
	/** Indica se a condição invariante da classe se verifica.

	    \pre V.
	    
	    \post cumpreInvariante = ano_minimo <= ano_ and 
	    0 < dia_ and dia_ <= numeroDeDiasEm(mes_, ano_). */
	bool cumpreInvariante() const;
    };
    
    ///@name Operações associadas à classe Data
    //@{

    /** Indica se duas datas são iguais.
	
        \pre V.

	\post operador== = \a uma_data é igual a \a outra_data. 

	\ingroup datas */
    bool operator==(Data const& uma_data, Data const& outra_data);
    
    /** Indica se duas datas são diferentes.
	
        \pre V.

	\post operador!= = \a uma_data é diferente de \a outra_data. 

	\ingroup datas */
    bool operator!=(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data é menor que outra.
	
        \pre V.

	\post operador< = \a uma_data é menor que \a outra_data. 

	\ingroup datas */
    bool operator<(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data é maior que outra.
	
        \pre V.

	\post operador>= = \a uma_data é maior uqe \a outra_data. 

	\ingroup datas */
    bool operator>(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data é menor ou igual a outra.
	
        \pre V.

	\post operador<= = \a uma_data é menor ou igual a \a outra_data. 

	\ingroup datas */
    bool operator<=(Data const& uma_data, Data const& outra_data);
    
    /** Indica se uma data é maior ou igual a outra..
	
        \pre V.

	\post operador>= = \a uma_data é maior ou igual igual a \a outra_data. 

	\ingroup datas */
    bool operator>=(Data const& uma_data, Data const& outra_data);
    
    /** Devolve a distância entre duas datas.
	
        \pre V.

	\post operador- = distância entre \a outra_data e \a uma_data, em
	dias. 

	\ingroup datas */
    Duracao operator-(Data const& uma_data, Data const& outra_data);
    
    /** Devolve a subtracção de uma duração de uma data.
	
        \pre duracao <= 0 ou Data(ano_minimo, 1, 1) + d <= data..

	\post operador- + duracao = \a data. 

	\ingroup datas */
    Data operator-(Data const& data, Duracao const& duracao);
    
    /** Devolve a adição de uma duração a uma data.
	
        \pre 0 <= duracao ou Data(ano_minimo, 1, 1) - d <= data.

	\post operador- = \a data acrescentada de \a duracao. 

	\ingroup datas */
    Data operator+(Data const& data, Duracao const& duracao);
    
    /** Devolve a adição de uma duração a uma data.
	
        \pre 0 <= duracao ou Data(ano_minimo, 1, 1) - d <= data.

	\post operador+ = \a data acrescentada de \a duracao. 

	\ingroup datas */
    Data operator+(Duracao const& duracao, Data const& data);
    
    /** Insere uma data num canal.
	
        \pre V.

	\post saida contém a data (a/m/d) ou não saida.good().

	\ingroup datas */
    std::ostream& operator<<(std::ostream& saida, Data const& data);
    
    /** Extrai uma data de um canal.
	
        \pre V.

	\post entrada.good() e já não contém a data, que está em \a data.
	Alternativamente, não entrada.good().. 

	\ingroup datas */
    std::istream& operator>>(std::istream& entrada, Data& data);

    //@}
}

#include <Utilitarios/data_impl.H>

#endif // UTILITARIOS_DATA_H
