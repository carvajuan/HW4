#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#define N 50  //tamaño de la matriz 
#define K 16200.0 //conductividad termica
#define CP 0.82 //calor especifico
#define ROH 2.71 //densidad
#define TEMP_VARILLA 373.15 //temperatura permanente de la varilla
#define TEMP_FRONTERA 283.15 // temperatura de condicion de frontera

using namespace std;

int posicion(int i, int j);
void iniciales(double *matriz);
void paso(double *m, double *u_f, double delta_x, double delta_t, double condicion);
void copia(double *viejo, double *nuevo);
double promedio(double *ma);


double COEF=K/(CP*ROH); //coeficiente de difusion

int main(){
    double *mat = (double *)malloc(N*N * sizeof(double));
    double *T_ANTES = (double*)malloc(N*N*sizeof(double)); 
    double *T_DESPUES =(double*)malloc(N*N*sizeof(double));
    double dx=1.0; //paso espacial
    double dt=0.00003429; //paso temporal
    double alpha =(dt*COEF)/(dx*dx); 
    double *promedio_1, *promedio_2, *promedio_3;
    double T_max = 0.8;
    int ta = T_max / dt;
    int e;
    promedio_1 = new double[ta];
    promedio_2 = new double[ta];
    promedio_3 = new double[ta];
	
    ofstream pro; 
    pro.open("Temperatura_promedio.txt");
	
	
    ofstream graficas;
    graficas.open("Graficas.txt");
	
	
    //SE INICIALIZA
    iniciales(T_ANTES);
  
	
    ofstream archivo;
    archivo.open("Temperatura_inicial.txt");

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
	
	
	
     //SE HACE LA EVOLUCION CON FRONTERAS FIJAS
     double t = 0;
     e = 0;
     z = 0;
     k = 0;
     while (t<T_max)
     {
	paso(T_ANTES,T_DESPUES,dx,dt,1);
	promedio_1[e] = promedio(T_DESPUES);

	if (pro.is_open())
	{

		pro << promedio_1[e] << " ";

	}   
	if (t>0.001 && t<0.00104 )
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}
			

		}
		z = 0;
		k = 0;
		if (t > 0.01 && t < 0.01004)
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}
			

		}	     
	    
	copia(T_DESPUES,T_ANTES);
	t = t + dt;
	e=e+1;
     }
     pro<< "\n";

	
	
   //SE ARCHIVA LA SOLUCION CON FRONTERAS FIJAS
   ofstream a;
   a.open("Fronteras_fijas.txt");

	
   z = 0;
   k = 0;
   for (z = 0; z < N; z++)
   {
	for (k = 0; k < N; k++)
	{
		pos = posicion(z, k);
		if (a.is_open())
		{

			a << T_DESPUES[pos] << " ";

		}

	}
	a << "\n";
    }

    a.close();
	
	
    //SE HACE LA EVOLUCION CON FRONTERAS ABIERTAS
    iniciales(T_ANTES);

    z = 0;
    k = 0;
    t = 0;
    e = 0;
    while (t < T_max)
    {
	paso(T_ANTES, T_DESPUES, dx, dt, 3);

	promedio_2[e] = promedio(T_DESPUES);

	if (pro.is_open())
	{

		pro << promedio_2[e] << " ";

	}
	if (t > 0.01 && t < 0.01004)
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}


		}
		z = 0;
		k = 0;
		if (t > 0.1 && t < 0.10004)
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}
			

		}
        copia(T_DESPUES, T_ANTES);
	t = t + dt;
	e=e+1;
	    
    }


    pro << "\n";


    //SE ARCHIVA LA SOLUCION CON FRONTERAS ABIERTAS
    ofstream f;
    f.open("Fronteras_abiertas.txt");

    z = 0;
    k = 0;
    for (z = 0; z < N; z++)
    {
	for (k = 0; k < N; k++)
	{
		pos = posicion(z, k);
		if (f.is_open())
		{

			f << T_DESPUES[pos] << " ";

		}

	}
	f << "\n";
     }

     f.close();

	
	
	
    //SE DESARROLLA CON FRONTERAS PERIODICAS

    iniciales(T_ANTES);
    z = 0;
    k = 0;
    t = 0;
    e = 0;
    while (t < T_max)
    {
	paso(T_ANTES, T_DESPUES, dx, dt, 2);
	promedio_3[e] = promedio(T_DESPUES);

	if (pro.is_open())
	{

		pro << promedio_3[e] << " ";

	}
	if (t > 0.01 && t < 0.01004)
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}


		}
		z = 0;
		k = 0;
		if (t > 0.1 && t < 0.10004)
		{
			for (z = 0; z < N; z++)
			{
				for (k = 0; k < N; k++)
				{
					pos = posicion(z, k);
					if (graficas.is_open())
					{

						graficas << T_DESPUES[pos] << " ";

					}

				}
				graficas << "\n";
			}
			graficas.close();

		}   
	    
	    
	    
	    

        copia(T_DESPUES, T_ANTES);
	t = t + dt;
	e=e+1;
     }
     pro << "\n";
     pro.close();

     //SE ARCHIVA LA SOLUCION CON FRONTERAS PERIODICAS
     ofstream file;
     file.open("Fronteras_periodicas.txt");


    z = 0;
    k = 0;
    for (z = 0; z < N; z++)
    {
	for (k = 0; k < N; k++)
	{
		pos = posicion(z, k);
		if (file.is_open())
		{

			file << T_DESPUES[pos] << " ";

		}

	}
	file << "\n";
    }

    file.close();

    return 0;
    
}

int posicion(int i, int j)
{
	return i + j * N;
}

void iniciales(double *matriz) {

	int i, j, posi;
	int mitad=25;
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
	int mitad = 25;
	double arriba, abajo, izquierda, derecha;
	for (i = 0; i < N; i++)
	{
		
		double xx = i - mitad;
		
		for (j = 0; j < N; j++)
		{
			
			double yy = j - mitad;
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
			
				if (sqrt(xx*xx + yy * yy) <= 5)
				{
					u_f[p] = TEMP_VARILLA;
				}
				else
				{
					u_f[p] = m[p] + (COEF*delta_t / (delta_x*delta_x))*(arriba + abajo + izquierda + derecha - 4 * m[p]);
				}
				
			}
			
			else if (condicion == 1)
				{
					if (i == N - 1)
					{
						u_f[p] = TEMP_FRONTERA;
					}
					else if (i == 0)
					{
						u_f[p] = TEMP_FRONTERA;
					}
					if (j == N - 1)
					{
						u_f[p] = TEMP_FRONTERA;
					}
					else if (j == 0)
					{
						u_f[p] = TEMP_FRONTERA;
					}
				}
			else if (condicion == 2)
			{
				if (i == N - 1)
				{
					abajo = m[posicion(1, j)];
				}
				else if (i == 0)
				{
					arriba = m[posicion(N - 2, j)];
				}
				if (j == N - 1)
				{
					derecha= m[posicion(i, 1)];
				}
				else if (j == 0)
				{
					izquierda = m[posicion(i, N - 2)];
				}
					u_f[p] = m[p] + (COEF*delta_t / (delta_x*delta_x))*(arriba + abajo + izquierda + derecha - 4 * m[p]);
			}



			else if (condicion == 3)
			{
				if (i == N - 1)
				{
					abajo = m[p];
				}
				else if (i == 0)
				{
					arriba = m[p];
				}
				if (j == N - 1)
				{
					derecha = m[p];
				}
				else if (j == 0)
				{
					izquierda = m[p];
				}
					u_f[p] = m[p] + (COEF*delta_t / (delta_x*delta_x))*(arriba + abajo + izquierda + derecha - 4 * m[p]);
			}
		}
	}
}

void copia(double *viejo, double *nuevo)
{

	
		int i, j,posi;
		for (i = 0; i < N; i++)
		{

			for (j = 0; j < N; j++)
			{

				posi = posicion(i, j);
				nuevo[posi] = viejo[posi];
			
			}
		}
}

double promedio(double *ma)
{
	int i, j;
	double p=0;
	for (i=0;i<N;i++)
	{
		for (j=0;j<N;j++)
		{
			p = p + ma[posicion(i, j)];
		}
	}
	return p / 2500;
}
