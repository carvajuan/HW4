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
void paso(double *m, double *u_f, double delta_x, double delta_t, double condicion);



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
	
	
    ofstream archivo;
    archivo.open("inicial.txt");

    int z, k, pos;

    for (z = 0; z < N; z++)
    {
	for (k = 0; k < N; k++)
	{
		pos = posicion(z, k);
		if (archivo.is_open())
		{

			archivo << T_ANTES[pos] << " ";

		}

	}
		archivo << "\n";
     }

     archivo.close();
	

    return 0;
    
}

int posicion(int i, int j)
{
	return i + j * N;
}

void iniciales(double *matriz) {

	int i, j, posi;
	int mitad=50;
	for (i = 0; i < N; i++)
	{
		double xx = i-mitad;
		for (j = 0; j < N; j++)
		{
			double yy = j - mitad;
			posi = posicion(i, j);
			matriz[posi] = TEMP_FRONTERA;
			if (sqrt(xx*xx + yy * yy) <= 5)
			{
				matriz[posi] = TEMP_VARILLA;
			}
			
		}
	}

}

void paso(double *m, double *u_f, double delta_x, double delta_t, double condicion)
{
	int i, j;
	int p;
	double arriba, abajo, izquierda, derecha;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			p = posicion(i, j);
			if (i < N - 1)
			{
				abajo = m[posicion(i + 1, j)];
			}
			if (i > 0)
			{
				arriba = m[posicion(i - 1, j)];
			}
			if (j < N - 1)
			{
				derecha = m[posicion(i, j + 1)];
			}
			if (j > 0)
			{
				izquierda = m[posicion(i, j - 1)];
			}

			if ((j > 0) && (j < N - 1) && (i > 0) && (i < N - 1))
			{
				u_f[p] = m[p] + (COEF*delta_t / delta_x)*(arriba + abajo + izquierda + derecha - 4 * m[p]);
			}
		}
	}
}
