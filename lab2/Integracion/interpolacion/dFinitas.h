#include <iostream>
#include <fstream>
#include <string>
#include <armadillo>
#include <math.h>
using namespace std;
using namespace arma;

class dFinitas
{
public:

	long double fact(long double n){
		if(n==0 || n==1){
			return 1.0;
		}
		else{
			return n*fact(n-1);
		}
	}
long double setFinitas(long double xi,int n, vector<long double> x, mat matriz){
	long double xt=1;
	long double yi=matriz(0,0);

	for(int j = 0; j<n-1;j++){
		xt=static_cast<long double> (xt*(xi-x[j]));
		yi=static_cast <long double> (yi+matriz(0,j+1)*xt);
	}
	
	return yi;
}
mat finitas(vector<long double>x, vector<long double>y, int n, long double dist){
		mat matriz(n,n);
		matriz.zeros();
		for(int i=0;i<n;i++){
		matriz(i,0) = y[i];
		}
		for(int j=1;j<n;j++){
			for(int k=0;k<n-j;k++){
				matriz(k,j) = matriz(k+1,j-1)-matriz(k,j-1);
			}
		}
		mat F(1,n);
		F.zeros();
		F(0,0) = matriz(0,0);
		for(int i=1;i<n;i++){
			F(0,i) = matriz(0,i)/(fact(static_cast<long double>(i))*static_cast<long double>(pow(dist,i)));
		}
		return F;
}
vector <long double> obtenerFinitas(vector<long double> x,vector <long double>y, int n, long double dist,vector<long double> xi){
	mat matriz=finitas(x,y,n,dist);
	string nombre;
	ofstream archivo("dFinitas.txt");
	vector <long double> result(8001);
	for (int i = 0; i < 8001; ++i){
		result[i]=setFinitas(xi[i],n,x,matriz);
		archivo << result[i] <<" \n";
	}
	return result;
}

};