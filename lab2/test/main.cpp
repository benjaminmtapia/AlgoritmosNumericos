#include <iostream>
#include <fstream>
#include <string>
#include <armadillo>
#include <math.h>
#include <cmath>
#include <iomanip>

#include "divididas.h"
#include "Minimos.h"
#include "spline.h"
#include "rmse.h"
#include "dFinitas.h"
#include "integrales.h"

using namespace std;

long double fun1(long double x){
	long double y;
	y= exp(x) + x -2;
	return y;
}
long double fun2(long double x){
	long double y;
	y= pow(x,3)+ 4*(pow(x,2))-5*x+2;
	return y;
}

vector <long double> funcion1_05(vector<long double> xi){
	int n=xi.size();
	vector<long double> resultado(n);
	for (int i = 0; i < n; ++i)
	{
		resultado[i]= fun1(xi[i]) ;
	}
	return resultado;

}

vector <long double> funcion2_05(vector<long double> xi){
	int n=xi.size();
	vector<long double> resultado(n);
	for (int i = 0; i < n; ++i)
	{
		resultado[i]= fun2(xi[i]) ;
	}
	return resultado;

}

int main(int argc, char const *argv[])
{
	//archivos para escribir intervalo de x
	ofstream myfile ("x05.txt");
	ofstream myfile2 ("x1.txt");
	ofstream myfile3 ("x5.txt");
	ofstream myfile4 ("x10.txt");

	vector<long double> x1(801);
	vector<long double> y1(801);vector <long double> y11(801);
	//intervalo de 1
	vector<long double> x2(401);
	vector<long double> y2(401);vector<long double>y22(401);
	//intervalo de 5
	vector<long double>x3(81);
	vector<long double>y3(81); 
	vector<long double> y33(81);
	//intervalo de 10
	vector<long double> x4(41);
	vector<long double> y4(41);vector<long double> y44(41);

//========CREACION DE INTERVALOS===========
	int i=0;
	long double aux=-200;
	//para intervalo de 10 en 10
	while(i < 41){
		x4[i]=i;
		y4[i]=fun1(aux);
		y44[i]=fun2(aux);
		myfile4 << aux <<"\n";
		aux = aux + 10.0;
		i++;
	}
	//para intervalo de 5 en 5
	i=0;
	aux=-200;
	while(i<81){
		x3[i]=aux;
		y3[i]=fun1(aux);
		y33[i]=fun2(aux);
		myfile3 << aux <<"\n";
		aux=aux+5.0;
		i++;
	}
	//para intervalo de 1 en 1
	i=0;
	aux=-200;
	while(i<401){
		x2[i]=aux;
		y2[i]=fun1(aux);
		y22[i]=fun2(aux);
		myfile2 << aux <<"\n";
		aux=aux+1.0;
		i++;
	}
	//para intervalo de 0.5 en 0.5
	i=0;
	aux=-200;
	while(i<801){
		x1[i]=aux;
		y1[i]=fun1(aux);
		y11[i]=fun2(aux);
		myfile << y11[i] <<"\n";
		aux=aux+0.5;
		i++;
	}
 string line;
 long double numero;
vector<long double> valor(8001);
 int a=0;

 //INTERVALOS:  MODIFICAR NOMBRE DE ARCHIVO PARA CAMBIAR DE FUNCION
  ifstream archivo ("intervalosf2.txt");
  if (archivo.is_open())
  {
    while ( getline (archivo,line) )
    {
    numero=atof(line.c_str());
     valor[a]=numero;
      a++;
    }
    archivo.close();
  }
  else{
  	cout << "unable to open file";
  }

//==================INTERPOLACION================
 
divididas Div;
vector <long double> divididasOut;
//divididasOut = Div.escribirDivididas(x1,y1,801,valor);
divididasOut = Div.escribirDivididas(x1,y11,801,valor);
//divididasOut = Div.escribirDivididas(x2,y2,401,valor);
//divididasOut = Div.escribirDivididas(x2,y22,401,valor);
//divididasOut = Div.escribirDivididas(x3,y3,81,valor);
//divididasOut = Div.escribirDivididas(x3,y33,81,valor);
//divididasOut = Div.escribirDivididas(x4,y4,41,valor);
//divididasOut = Div.escribirDivididas(x4,y44,41,valor);

Spline sp;
vector<long double> splineOut;
//splineOut = sp.getSpline(x1,y1,valor,801,0.5);
splineOut = sp.getSpline(x1,y11,valor,801,0.5);
//splineOut = sp.getSpline(x2,y2,valor,401,1);
//splineOut = sp.getSpline(x2,y22,valor,401,1);
//splineOut = sp.getSpline(x3,y3,valor,81,5);
//splineOut = sp.getSpline(x3,y33,valor,81,5);
//splineOut = sp.getSpline(x4,y4,valor,41,10);
//splineOut = sp.getSpline(x4,y44,valor,41,10);




dFinitas df;
vector<long double> finitasOut;
//finitasOut = df.obtenerFinitas(x1,y1,801,0.5,valor);
finitasOut =df.obtenerFinitas(x1,y11,801,0.5,valor);
//finitasOut =df.obtenerFinitas(x2,y2,401,1,valor);
//finitasOut =df.obtenerFinitas(x2,y22,401,1,valor);
//finitasOut =df.obtenerFinitas(x3,y3,81,5,valor);
//finitasOut =df.obtenerFinitas(x3,y33,81,5,valor);
//finitasOut =df.obtenerFinitas(x4,y4,41,10,valor);
//finitasOut =df.obtenerFinitas(x4,y44,41,10,valor);


Minimos Mc;
vector <long double> minimosOut;
//minimosOut = Mc.getPolinomio(x1,y1,valor,801,8001,2);
minimosOut =Mc.getPolinomio(x1,y11,valor,801,8001,3);
//minimosOut =Mc.getPolinomio(x2,y2,valor,401,8001,2);
//minimosOut =Mc.getPolinomio(x2,y22,valor,401,8001,3);
//minimosOut =Mc.getPolinomio(x3,y3,valor,81,8001,2);
//minimosOut =Mc.getPolinomio(x3,y33,valor,81,8001,3);
//minimosOut =Mc.getPolinomio(x4,y4,valor,41,8001,2);
//minimosOut =Mc.getPolinomio(x4,y44,valor,41,8001,3);


ofstream salidaMinimos("MinCuadrados.txt");

for (int i = 0; i < 8001; ++i){ 
	salidaMinimos<< minimosOut[i] << "\n";
}

RMSE error;
long double error1,error2,error3,error4;


//=======================CALCULO DE ERRORES=============

error1= error.calcularError(y11,divididasOut,801);
error2= error.calcularError(y11,splineOut,801);
error3= error.calcularError(y11,finitasOut,801);
error4= error.calcularError(y11,minimosOut,801);

ofstream errores("erroresf1.txt");
errores << "Error Divididas: "<< setprecision(30) <<error1<<endl;
errores << "Error Spline: "<< setprecision(30) <<error2<<endl;
errores << "Error Finitas: "<< setprecision(30) <<error3<<endl;
errores << "Error Minimos: "<< setprecision(30) <<error4<<endl;

//=======================CALCULO INTEGRAL===============

metodosDeIntegracion integral;

vector <long double> y05= funcion1_05(valor);
vector <long double> y052= funcion2_05(valor);

long double integralTrapecio=integral.trapecio(valor,splineOut,0.5);
long double integralSimpson=integral.simpson(valor,splineOut,0.5);

long double trapecioreal=integral.trapecio(valor,y11,0.5);
long double simpsonreal= integral.simpson(valor,y11,0.5);

ofstream salidaIntegral("integralesF2.txt");

long double errorTrapecio,errorSimpson;

errorTrapecio= (integralTrapecio - trapecioreal)/trapecioreal;
errorSimpson = (integralSimpson - simpsonreal)/simpsonreal;

salidaIntegral << "metodo del trapecio: "<< integralTrapecio << endl;
salidaIntegral << "metodo de simpson: "<< integralSimpson<<endl;
salidaIntegral << "error de trapecio: "<< errorTrapecio<<endl;
salidaIntegral << "error de simpson: "<< errorSimpson<<endl;

}
