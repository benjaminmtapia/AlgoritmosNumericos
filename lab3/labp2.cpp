#include <armadillo>
#include <iostream>

using namespace arma;
using namespace std;


double ti(double i,int n){
  return -2*n -1;
}

double ti_1(double i, int n){
    return n + 1;
}



int main(){
  int n = 5;
  int a = 1;
  int b = 0;
  double constante = -2;
  double te = 50;
  mat matriz = mat(n,n);
  vec vector = vec(n);


  matriz.zeros();

  matriz(0,0) = -1;
  matriz(0,1) = 1;
  vector(0) = constante/2;

  while(a < n-1){
    matriz(a,b+1) = ti(a,a);
    matriz(a,b+2) = ti_1(a,a);
    matriz(a,b) = a;
    vector(a) = constante*a;
    b++;
    
    a++;
  }
  matriz(a,b) = a;
  matriz(a,b+1) = ti(a,a);
  vector(a) = a*constante-a+1*te;

  matriz.print();
  vector.print();

  vec x = solve(matriz,vector);
    x.print();
  return 0;

}
