#include <iostream>
#include <armadillo>
#include <fstream>
#include <string>
using namespace std;
using namespace arma;

class divididas
{
private:
	vector<long double> x,y,xi;
	int n;
	string salida;

public:
long double setDivididas(long double xi,int n, vector<long double> x, mat matriz){
	long double xt=1;
	long double yi=matriz(0,0);
	for (int i = 0; i < n-1; ++i)
	{
		xt=xt*(xi-x[i]);
		yi= yi + matriz(0,i+1)*xt;
	}
	
	return yi;
}
mat difDivididas(vector<long double>x, vector<long double>y, int n, vector<long double> xi){
	mat matriz(n,n);
	long double xt=0.0;

	for(int k=0; k<n; k++){
		matriz(k,0)=y[k];
	}
	//preparar matriz
	for(int j=1; j < n; j++){
		for(int i=0; i < n-j; i++){
			matriz(i,j)=(matriz(i+1,j-1)-matriz(i,j-1))/(x[i+j]-x[i]);
		}
	}
	return matriz;
}
	vector <long double> escribirDivididas(vector<long double>x,vector<long double>y,int n, vector<long double>xi){
		mat matriz(n,n);
		ofstream archivo ("divididas.txt");
		vector <long double> resultado(8001);
		matriz=difDivididas(x,y,n,xi);
		for (int i = 0; i < 8001; i++){
			resultado[i]=setDivididas(x[i],n,x,matriz);
			archivo<< resultado[i] <<"\n";
		}
		return resultado;
	}
};