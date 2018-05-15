/** \file data.C

    Ficheiro de implementação do módulo datas. Define ferramentas que permitem
    lidar com datas e tempos.

    \ingroup datas */
#include "Utilitarios/data.H"

#include <ctime>

using namespace std;


string Utilitarios::nomes_dos_meses[numero_total_de_meses + 1] = {
    "", // lixo; o mês 0 não existe.
    "Janeiro",
    "Fevereiro",
    "Março",
    "Abril",
    "Maio",
    "Junho",
    "Julho",
    "Agosto",
    "Setembro",
    "Outubro",
    "Novembro",
    "Dezembro"
};


string Utilitarios::nomes_dos_dias_da_semana[numero_total_de_dias_da_semana] ={
    "Domingo",
    "segunda-feira",
    "terça-feira",
    "quarta-feira",
    "quinta-feira",
    "sexta-feira",
    "Sábado"
};


istream& Utilitarios::operator>>(istream& entrada, Mes& mes) 
{
    string nome_do_mes;
    entrada >> nome_do_mes;

    for(int i = 0; i != numero_total_de_meses; ++i)
	if(nomes_dos_meses[i] == nome_do_mes) {
	    mes = Mes(i);

	    return entrada;
	}

    entrada.clear(ios_base::failbit);

    return entrada;
}

std::istream& Utilitarios::operator>>(std::istream& entrada, 
				      DiaDaSemana& dia_da_semana)
{
    string nome_do_dia;
    entrada >> nome_do_dia;

    for(int i = 0; i != numero_total_de_dias_da_semana; ++i)
	if(nomes_dos_dias_da_semana[i] == nome_do_dia) {
	    dia_da_semana = DiaDaSemana(i);
	    return entrada;
	}

    entrada.clear(ios_base::failbit);

    return entrada;
}

Utilitarios::Data Utilitarios::Data::actual() 
{
    if(data_actual_obtida_do_sistema) {
	time_t aux = time(0);
	tm tempo_actual = *localtime(&aux); 
	
	return Data(1900 + tempo_actual.tm_year, 
		    Mes(tempo_actual.tm_mon + 1),
		    tempo_actual.tm_mday); 
    } else
	while(true) {
	    cout << "Introduza a data actual (ano mes dia): ";
	    Data data;
	    cin >> data;
	    if(cin.good())
		return data;

	    cin >> ill;
	    cout << "Data errada." << endl;
	}
}
      
#ifdef _STLP_IOSTREAM
// ws no STLPort tem um problema qualquer!
namespace {
    istream& ws(istream& entrada)
    {
	char caractere;
	do
	    entrada.get(caractere);
	while(entrada.good() and isspace(caractere));

	if(entrada.good())
	    entrada.putback(caractere);
	
	return entrada;
    }
}
#endif

std::istream& Utilitarios::operator>>(std::istream& entrada, Data& data) 
{
    Ano ano;
    int mes;
    Dia dia;

    entrada >> ano >> ws;

    if(ano < Data::ano_minimo) {
	entrada.clear(ios_base::failbit);

	return entrada;
    }

    if(entrada.peek() == '/')
	entrada.get();

    entrada >> mes >> ws;

    if(mes < 1 or numero_total_de_meses < mes) {
	entrada.clear(ios_base::failbit);

	return entrada;
    }

    if(entrada.peek() == '/')
	entrada.get();

    entrada >> dia;

    if(dia < 0 or dia > numeroDeDiasEm(Mes(mes), ano)) {
	entrada.clear(ios_base::failbit);

	return entrada;
    }

    if(entrada)
	data = Data(ano, Mes(mes), dia);

    return entrada;
}

bool Utilitarios::Data::data_actual_obtida_do_sistema = true;


#ifdef TESTE

#include <fstream>

using namespace Utilitarios;

void testaMes() 
{
    Mes mes = janeiro;

    assert(numero_total_de_meses == 12);

    mes += 13;

    assert(mes == fevereiro);

    --mes; 

    assert(mes == janeiro);

    mes--; 

    assert(mes == dezembro);

    ++mes; 

    Mes outro_mes = mes++;

    assert(mes == fevereiro);
    
    assert(outro_mes == janeiro);

    outro_mes -= 13;

    assert(outro_mes == dezembro);

    assert(outro_mes + 25 == janeiro);

    assert(outro_mes + -25 == novembro);

    assert(outro_mes - 25 == novembro);

    assert(mes - outro_mes == 2);
	
    ofstream saida("data.lixo");
    saida << mes << endl;
    saida.close();

    ifstream entrada("data.lixo");
    entrada >> outro_mes;

    assert(outro_mes == mes);

    assert(numeroDeDiasEm(dezembro, 2000) == 31);

    assert(numeroDeDiasEm(fevereiro, 2000) == 29);

    assert(numeroDeDiasEm(fevereiro, 1900) == 28);

    assert(numeroDeDiasEm(fevereiro, 1996) == 29);
}

void testaDiaDaSemana() 
{
    DiaDaSemana dia = segunda_feira;

    assert(numero_total_de_dias_da_semana == 7);

    dia += 8;

    assert(dia == terca_feira);

    --dia; 

    assert(dia == segunda_feira);

    dia--; 

    assert(dia == domingo);

    ++dia; 
    DiaDaSemana outro_dia = dia++;

    assert(dia == terca_feira);

    assert(outro_dia == segunda_feira);

    outro_dia -= 8;

    assert(outro_dia == domingo);

    assert(outro_dia + 15 == segunda_feira);

    assert(outro_dia + -15 == sabado);

    assert(outro_dia - 15 == sabado);

    assert(dia - outro_dia == 2);
	
    ofstream saida("data.lixo");
    saida << dia << endl;
    saida.close();

    ifstream entrada("data.lixo");
    entrada >> outro_dia;

    assert(outro_dia == dia);
}

void testaData() 
{
    Data data(1965, setembro, 14);

    assert(data.ano() == 1965);

    assert(data.mes() == setembro);

    assert(data.dia() == 14);

    assert(data == Data(1965, setembro, 14));

    assert(not (data != Data(1965, setembro, 14)));

    Data outra_data = data + 12983;

    assert(outra_data == Data(2001, abril, 1));

    ofstream saida;

    saida.open("data.lixo");
    saida << data << endl;
    saida.close();

    ifstream entrada;

    entrada.open("data.lixo");
    entrada >> outra_data;
    entrada.close();

    assert(outra_data == data);

    outra_data = data + 12983;

    saida.open("data.lixo");
    data.guardaEm(saida);
    outra_data.guardaEm(saida);
    saida.close();

    entrada.open("data.lixo");
    Data data_lida(entrada);

    assert(data_lida == data);

    data.carregaDe(entrada);
    entrada.close();

    assert(data == outra_data);

    Data data_de_transicao(1999, dezembro, 31);

    ++data_de_transicao;

    assert(data_de_transicao == Data(2000, janeiro, 1));

    --data_de_transicao;

    assert(data_de_transicao == Data(1999, dezembro, 31));

    Data anterior = data_de_transicao++;

    assert(data_de_transicao == Data(2000, janeiro, 1));

    assert(anterior == Data(1999, dezembro, 31));

    anterior = data_de_transicao--;

    assert(data_de_transicao == Data(1999, dezembro, 31));

    assert(anterior == Data(2000, janeiro, 1));

    assert(anterior.anoEBissexto());

    assert(not data_de_transicao.anoEBissexto());
	
    Data data_juliana(2452001);

    assert(data_juliana == Data(2001, abril, 1));

    assert(data_juliana.diaDaSemana() == domingo);

    --data_juliana;

    assert(data_juliana == Data(2001, marco, 31));

    assert(data_juliana.diaDaSemana() == sabado);

    Data para_juliana(2001, abril, 1);

    assert(para_juliana.diaJuliano() == 2452001);

    Data nao_bissexto(1900, fevereiro, 1);

    assert(not nao_bissexto.anoEBissexto());

    Data bissexto(1904, fevereiro, 1);

    assert(bissexto.anoEBissexto());

    assert(nao_bissexto.numeroDeDiasNoMes() == 28 or
	   bissexto.numeroDeDiasNoMes() == 29);

    data = Data(1965, setembro, 14);
    outra_data = data;
    
    outra_data += 12983;

    assert(outra_data == Data(2001, abril, 1));

    outra_data -= 12983;

    assert(outra_data == Data(1965, setembro, 14));
}

int main()
{
    testaMes();
    testaDiaDaSemana();
    testaData();
}

#endif
