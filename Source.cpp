#include <stdio.h>
#include <iostream>
#include "conio.h"
#include <math.h>
#include <vector>
#include <math.h>

using namespace std;

bool encuentra = false;
int edad_jubilacion_menos_edad =37;//anios q trabajara pero que para la web sera un calculo extra
//el usuario ingresa su edad y fecha de jubilacion y se restan
vector <float> v; //aqui almacenaremos cada termino del flujo del VAN para calcular la TIR
vector <float> v2;


void newTIR()
{

	double COK = 0.015309;
	double NDxA = 360.00;

	double TIR;
	double VAN;

	double Fo;
	double Maximo;
	double Minimo;
	double VA;

	for (int i = 0; i < edad_jubilacion_menos_edad * 12; i++)
	{
		Fo = Fo + v[i];
	}

	Minimo = -1;
	Maximo = 1.1;
	do
	{
		VA = 0;
		TIR = (Maximo + Minimo) / 2;
		for (int i = 0; i < edad_jubilacion_menos_edad * 12; i++)
		{
			VA = VA - v[i] / pow(1 + TIR, ((i + 1) * 30) / NDxA);
		}
		for (int i = 0; i < v2.size(); i++)
		{
			VA = VA - v2[i] / pow(1 + TIR, ((i + 1) * 30 * 12) / NDxA);
		}
		if (abs(VA) < abs(Fo))
		{
			Maximo = TIR;
		}
		else
		{
			Minimo = TIR;
		}

	} while (abs(VA + Fo) > 0.000000001);
	TIR = abs(TIR);
	VAN = Fo;
	for (int i = 0; i < edad_jubilacion_menos_edad * 12; i++)
	{
		VAN = VAN + v[i] / pow(1 + COK, i + 1);
	}
	for (int i = 0; i < v2.size(); i++)
	{
		VAN = VAN + v2[i] / pow(1 + COK, (i + 1) * 12);
	}
	cout << "El VAN DE JOHAN ES : " << VAN;
	cout << endl;
	cout << "LA TIR ES: " << TIR * 100 << "%";
	cout << endl;
}



int main()
{

	int remuneracion = 900;//salario (INGRESADO POR USUARIO)
	float PaporteAFP = 0.1;//porcentaje del salario q se agregara al fondo (calculado luego) (FIJO)

	long float fondo = 0;//(FIJO)
	long float TEM = pow((1 + 0.02),0.0833333) - 1;//lo ingresaria el usuario //0.083333 es fijo, no lo ingresa el usuario
	//lo ingresaria el usuario (VALOR PORCENTUAL, SI PONE 2 -> 0.02 ) 
	float comisionAFP;//variable de almancenamiento usada para calculos cada anio 
	float PcomisionAFP = 0.012;//lo ingresaria el usuario ( VALOR PORCENTUAL, SI PONE 1.2 -> 0.012 )

	long float fondo_i = 0;//varialble tecnicamente auxiliar
	float sumatoria = 0;//usado para el calculo del van 
	int año = 0;//nose q mierda es esto, lo puso johan pero creo q ni se usa jaja salu2
	float rentabilidad = 0;//variable comun
	float cok = 0.015309; //(FIJO) 
	float valor_renta = 0;//variable comun
	float aporte = remuneracion * PaporteAFP;//lo q cada mes aporta a su fondo

	int contador3 = 1;
	for (int i = 0; i < edad_jubilacion_menos_edad; i++){
		fondo_i = fondo;//utilizamos la variable fondo_i para ver luego del anio cuanto a crecido el fondo...cada anio el fondo inicial cambia obviamente
		float prima = 0;
		for (int j = 0; j < 12; j++){
			prima += 0.02*remuneracion;
			long float fondo_ii = fondo;//solo hago esto para guardar el valor del fondo al inicio del mes
			fondo = fondo + aporte + (TEM*fondo);//cada mes se agrega una pequena ganancia y te cobramos seguro
			cout << "MES " << j + 1 << " Anio " << i + 1 << " = " << fondo << " Remuneracion : " << remuneracion << " Aporte : " << aporte << endl;
			sumatoria += (fondo - fondo_ii) / pow((1 + cok), contador3);//calculo de un termino de la sumatoria del VAN
			v.push_back(fondo - fondo_ii);
			contador3++;
		}
		comisionAFP = PcomisionAFP*fondo; //comision afp se cobra todos los anios y sera fijo ingresado por el usuario
		fondo = fondo - comisionAFP; //al fondo se le quita la comision q le cobran anualmente
		sumatoria -= (comisionAFP*) / pow((1 + cok), contador3); //calculo de un termino de la sumatoria del VAN
		v2.push_back(comisionAFP*(-1));//tambien para VAN

		rentabilidad = ((fondo - fondo_i) / fondo_i) * 100;//pura formula
		valor_renta = fondo - fondo_i;//puraformula
		//
		fondo = fondo; //aqui sacas fondo acumulado y comisionAFP en ultima columna y prima
		prima = prima;
		//
		System::Console::ForegroundColor = System::ConsoleColor::Green;
		cout << "Rentabilidad " << rentabilidad << "%    Valor Rentabilidad: " << valor_renta << " Comision: " << comisionAFP << " TotalDsctoEnPrimaDelAnio : "<<prima <<endl;
		System::Console::ForegroundColor = System::ConsoleColor::White;
		//se imprimen los valores por anio
		cout << endl << endl;
	}

	System::Console::ForegroundColor = System::ConsoleColor::Red;

	cout << endl;
	cout << "El VAN de Kenzo es : " << sumatoria << endl;
	float TREA = (pow((fondo / 0), (360 / 360 * edad_jubilacion_menos_edad)) - 1) * 100;
	cout <<TREA <<'%'<< endl;
	newTIR();
	system("PAUSE");

	return 0;

}
