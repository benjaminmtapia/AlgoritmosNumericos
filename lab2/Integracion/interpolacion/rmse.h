#include <iostream>
#include <armadillo>
#include <fstream>
#include <string>
using namespace std;
using namespace arma;
class RMSE
{
public:
	long double calcularError(vector<long double>y, vector<long double> yi, int n){
		long double suma=0.0;
		long double aux;

		for (int i = 0; i < n; ++i){
			aux= pow(yi[i]-y[i],2);
			suma+=aux;
		}
		suma= suma / n;
		//cout << sqrt(suma)<<endl;
		return sqrt(suma);
	}
	
};