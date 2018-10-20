#include <iostream>
#include <fstream>
#include <string>
#include <armadillo>
#include <vector>
#include "unistd.h"
using namespace std;
using namespace arma;

//se recibe como parametro un numero y lo evalua en la funcion, entregando el resultado
long double funcion (long double x){
	long double y;
	y = pow(2,x);
	y = y - 2*x;
	return y;
}
//metodo del trapecio simple
long double trapecio(long double a, long double b){
	return (b-a) * (funcion(a) + funcion(b)) /2.0;
}

//metodo del trapecio adaptativo, recursion arborea
long double TrapecioAdaptativo(long double a, long double b, long double tol, int &iteraciones){
	long double IntegralReal = trapecio(a,b);
	long double m = (a + b) / 2.0;
	long double Error = abs(IntegralReal - (trapecio(a,m) + trapecio(m,b)));
	//cout<< Error <<endl;
	iteraciones++;
	//cout<< iteraciones << endl;
	if(Error < tol){
		return trapecio(a,m) + trapecio(m,b);
	}
	else{
		return TrapecioAdaptativo(a,m,tol,iteraciones) + TrapecioAdaptativo(m,b,tol,iteraciones);
	}
}
//metodo de simpson 1/3 simple
long double SimsponUntercio(long double a, long double b){
	long double Fa,Fb,Fm,m,h;
	m = (a + b) / 2;
	h = (b - a) / 6;
	Fa = funcion(a);
	Fb = funcion(b);
	Fm = funcion(m);
	long double simpson = h*(Fa + Fb + 4*Fm);
	return simpson;
}
//metodo de simpson 1/3 adaptativo con recursion arborea
long double SimpsonUnTercioAdaptativo(long double a,long double b, long double tol, int &iteraciones){
	long double IntegralReal = SimsponUntercio(a,b);
	long double m = (a + b) /2.0;
	iteraciones++;
	long double Error = abs (IntegralReal - (SimsponUntercio(a,m) + SimsponUntercio(m,b)));
	if(Error < tol){
		return SimsponUntercio(a,m) + SimsponUntercio(m,b);
	}
	else{
		return SimpsonUnTercioAdaptativo(a,m,tol,iteraciones) + SimpsonUnTercioAdaptativo(m,b,tol,iteraciones);
	}
}

//metodo de simpson 3/8 simple
long double SimpsonTresOctavos(long double a, long double b){
	long double x1,x2,Fa,Fb,Fx1,Fx2,h;
	h = (b-a)/3.0;
	x1 = a+h;
	x2 = x1+h;
	Fa = funcion(a);
	Fb = funcion(b);
	Fx1 = funcion(x1);
	Fx2 = funcion(x2);

	long double simpson = (3*h/8) * (Fa + 3*Fx1 + 3*Fx2 + Fb);
	return simpson;
}
//metodo de simpson 3/8 adaptativo, recursion arborea 
long double SimsponTresOctavosAdaptativo(long double a, long double b, long double tol,int &iteracionesSimsponTresOctavos){
	long double IntegralReal = SimpsonTresOctavos(a,b);
	iteracionesSimsponTresOctavos++;
	long double m = (a + b) /2.0;
	long double Error = abs (IntegralReal - (SimpsonTresOctavos(a,m) + SimpsonTresOctavos(m,b)));
	if(Error < tol){
		return SimpsonTresOctavos(a,m) + SimpsonTresOctavos(m,b);
	}
	else{
		return SimsponTresOctavosAdaptativo(a,m,tol,iteracionesSimsponTresOctavos) + SimsponTresOctavosAdaptativo(m,b,tol,iteracionesSimsponTresOctavos);
	}
}

int main(int argc, char *const *argv)
{
	//iteraciones necesarias, inicio de variables
	int iteracionesTrapecio=0;
	int iteracionesSimsponUnTercio=0;
	int iteracionesSimsponTresOctavos=0;
	long double a;
	long double b;
	long double tolerancia;
	
	int c;
	string fun;
	//recepcion de parametros con getopt
	while( (c = getopt(argc, argv, "t:a:b:I: ")) != -1){
      switch(c){
        case 't':
          tolerancia = atof(optarg);
          
          break;
        case 'a':
          a = atof(optarg);
          break;
        case 'b':
          b = atof(optarg);
          break;
        case 'I':
          fun= optarg;
          break;
        case '?':
          printf("Opción desconocida: %c\n",c);
        default:
          printf("parametros mal ingresados\n");
          return 1;
      }
  }
  //para trapecio se imprime el resultado y sus iteraciones
  	if(fun == "trap" ) {
		cout << "metodo del trapecio: "<<TrapecioAdaptativo(a,b,tolerancia,iteracionesTrapecio)<<endl;
		cout << "iteraciones trapecio: "<<iteracionesTrapecio<<endl;
	}
	//simpson un tercio
	else if(fun == "sim3"){
		cout << "simpson un tercio: " <<SimpsonUnTercioAdaptativo(a,b,tolerancia,iteracionesSimsponUnTercio)<<endl;
		cout << "iteraciones simpson un tercio: "<< iteracionesSimsponUnTercio<< endl;
	}
	//simpson tres octavos
	else if(fun == "sim8"){
		cout << "simpson tres octavos: "<< SimsponTresOctavosAdaptativo(a,b,tolerancia,iteracionesSimsponTresOctavos)<<endl;
		cout << "iteraciones simpson tres octavos: "<<iteracionesSimsponTresOctavos<< endl;
	}


	return 0;
}