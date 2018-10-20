#include <iostream>
#include <armadillo>
#include <fstream>
#include <string>
using namespace std;
using namespace arma;

class Spline
{
public:

	vector <long double> Coeficientes(vector<long double>x, vector<long double>y, int n){

		vector <long double> h(n);
		vector <long double> b(n);

		for (int i = 0; i < n-1; i++){
			h[i]=static_cast <long double> (x[i+1]-x[i]);
			b[i]=static_cast <long double> (6*(y[i+1]-y[i]));

		}

		vector <long double> u(n);
		vector <long double> v(n);
		u[1]= 2*(h[0]+h[1]);
		v[1]= b[1] - b[0];

		for (int i = 2; i < n-1; i++){
			long double aux=h[i-1]*v[i-1]/u[i-1];
			long double aux2=b[i]-b[i-1];
			u[i]= (2*(h[i]+h[i-1])) - static_cast <long double>(pow(h[i-1],2))/u[i-1];
			v[i]= static_cast<long double>(aux2-aux);
			//cout <<v[i]<<" ";
		}

		vector <long double> z(n);
		u[0]=1.0;
		z[n-1]=0;

		
		for (int i=n-1; i>1; i--){
			if(v[i]!=0){
				z[i]= (v[i]-h[i]*z[i+1])/u[i];
			}
			
		}
		z[0]=0;

		return z;
		
		}
		long double resolverSistema(vector <long double>x, vector <long double>y, vector <long double>z, long double dist, long double xi){
			long double A,B,C;
			long double ans;
			int n=0;
		//	cout << dist << endl;
			for (int i = -200; i <= 200; i=i+dist){

				//long double iAux = static_cast<long double>(i);
				//if(iAux <= xi && xi <= iAux + dist){
					A = ((1.0/6.0)*dist)*(z[n+1]-z[n]);
					B = z[n]/2.0;
					C = -1.0*(dist/6.0)*z[n+1] - (dist/3.0)*z[n] + (1.0/dist)*(y[n+1]-y[n]);
					ans = x[n] + (xi - x[n])*(C + (xi - x[n])*(B + (xi - x[n])*A));
					//printf("Soy coef 0 :%Le  1 :%Le, Y valor: %Le\n", z[n], z[i+1], valor);
					//cout << ans << endl;
					return ans;
				//}
				n++;

			}
			return 0.0;
		}
		
		vector <long double> getSpline(vector<long double>x,vector<long double> y,vector<long double>xi, int n, long double dist){
		vector <long double> out(8001);
		vector <long double> z=Coeficientes(x,y,n);
		ofstream salida("spline.txt");
		//cout << dist << endl;
		for (int i = 0; i < 8001; ++i)
		{
			out[i] = resolverSistema(x,y,z,dist,xi[i]);
			salida<<out[i]<<endl;
		}
		return out;
	}

};