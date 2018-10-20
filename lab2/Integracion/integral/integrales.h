#include <armadillo>
#include <vector>
using namespace std;
using namespace arma;

class metodosDeIntegracion{
public:
		long double trapecio(vector<long double>x,vector<long double> y, long double h){
		int largo;
		largo=x.size();
		//(ancho b-a)

		//f(xi)+f(xn)
		long double suma= y[0]+ y[largo-1];
		for(int i=1; i<largo-1;i++){
			suma+=2*y[i];
		}
		long double resultado= h*suma/2;
		//cout << resultado;
		return resultado;
	}


			long double simpson(vector <long double>x, vector <long double> y,long double h){
			long double factor=h/3;
			int n=y.size();
			long double factor2;
			factor2=y[0]+y[n-1];
			long double sum1,sum2;
			sum1=0;sum2=0;
			//SUMATORIAS
			for (int i = 2; i <= n/2; i++){
				sum1= sum1 + 2* y[2*i-2];
				sum2= sum2 + 4* y[2*i-1];
			}

			long double result;
			result = factor*(factor2+sum1+sum2);
		//	cout << result << "\n";
			return result;
		}

};
