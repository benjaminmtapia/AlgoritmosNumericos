#include <iostream>
#include <armadillo>
#include <fstream>
#include <string>
using namespace std;
using namespace arma;

class Minimos{
private:
	vec tablaCuadrado;

	vector <long double> evaluarCua(vector<long double> xInt,vec matriz,int largo,int largo2){
		vector <long double> poli(largo2);
		for(int j=0;j<largo2;j++){
			long double yi = matriz(0,0);
			for(int i=0;i<largo;i++){
				yi = yi+matriz(i+1)*pow(xInt[j],i+1);
			}
			poli[j] = yi;
		}
		return poli;
	}
	//sumatoria de las potencias y *x
	long double sumPotxy(vector<long double> xOut,vector<long double> yOut,int grado,int elem){
		long double suma = 0.0;
		for(int i=0;i<elem;i++){
			double xElem = pow(xOut[i],grado);
			suma+=yOut[i]*xElem;
		}
		return suma;
	}
	//sumatoria de potencias de x 
	long double sumPotx(vector<long double> xOut,int pot,int elem){
		if(pot == 0){
			return elem;
		}
		else{
			long double suma = 0.0;
			for(int i=0;i<elem;i++){
				suma+=pow(xOut[i],pot);
			}
			return suma;
		}
	}
	vec minimosCuadrados(vector<long double> xOut,vector<long double> yOut,int grado,int elem){
		mat matriz(grado+1,grado+1);
		mat result(grado+1,1);
		for(int i=0;i<grado+1;i++){
			int k = i;
			for(int j=0;j<grado+1;j++){
				matriz(i,j) = sumPotx(xOut,k,elem);
				k++;
			}
		}
		for(int i=0;i<grado+1;i++){
			result(i,0) = sumPotxy(xOut,yOut,i,elem);
		}
		//mat fin = pinv(matriz)*result;
		vec fin = solve(matriz,result);
		//result.print();
		//fin.print();
		return fin;
	}
	void setMinimos(vector<long double> xOut,vector<long double>yOut,int elem,int grado){
		tablaCuadrado = minimosCuadrados(xOut,yOut,grado,elem);
	}

public:
	vector <long double> getPolinomio(vector<long double> xOut,vector<long double>yOut,vector<long double> xInt,int large,int largo2,int grado) {
		setMinimos(xOut,yOut,large,grado);
		//return tablaCuadrado;
		return evaluarCua(xInt,tablaCuadrado,grado,largo2);
	}
};