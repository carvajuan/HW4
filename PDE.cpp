#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#define N 50  //tamaño de la matriz 
#define K 16200.0 //conductividad termica
#define CP 820.0 //calor especifico
#define ROH 2.71 //densidad
#define TEMP_VARILLA 100.0 //temperatura permanente de la varilla
#define TEMP_FRONTERA 10.0 // temperatura de condicion de frontera

using namespace std;

int posicion(int i, int j);
void iniciales(double *matriz);




double COEF=K/(CP*ROH); //coeficiente de difusion

int main(){
  
    double *T_ANTES = (double*)malloc(N*N*sizeof(double)); 
    double *T_DESPUES =(double*)malloc(N*N*sizeof(double));
    double dx=0.5; //paso espacial
    double dt=0.01; //paso temporal
    double alpha =(dt*COEF)/(dx*dx); 
    iniciales(T_ANTES);
  
    int i, j, posi;

	  for (i = 0; i < N; i++)
	  {
		  for (j = 0; j < N; j++)
		    {
			    posi = posicion(i, j);
			    cout<<T_ANTES[posi]<<" " ;

		    }
		  cout << endl;
	  }
    return 0;
    
}

int posicion(int i, int j)
{
	return i + j * N;
}

void iniciales(double *matriz) {

	int i, j, posi;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			posi = posicion(i, j);
			matriz[posi] = TEMP_FRONTERA;
			
		}
	}

}


