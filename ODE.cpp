#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

#define M_PI 3.14159265359

void reinicia(double *time, double *eje_x, double *eje_y, double *ve_x, double *ve_y, double angulo);
double dzdt(double v_x,double v_y) ;
double dxdt(double Z);
double dfdt(double v_x, double v_y);
double dydt(double F);

void Kutta(double *t,double *x, double *y, double *z,double *f, double h);

void reinicia(double *time, double *eje_x,double *eje_y, double *ve_x, double *ve_y, double angulo )
{
	*time = 0.0;
	*eje_x = 0.0;
	*eje_y = 0.0;
	*ve_x = 300 * cos(angulo);
	*ve_y = 300 * sin(angulo);

}
double dzdt(double v_x, double v_y)
{
	return -0.2*pow(v_x*v_x + v_y * v_y, 0.5)*v_x;
}
double dxdt(double Z)
{
	return Z;
}
double dfdt(double v_x,double v_y)
{
	return -10-0.2*pow(v_x*v_x + v_y * v_y, 0.5)*v_y;
}
double dydt(double F)
{
	return F;
}


void Kutta(double *t, double *x,double *y, double *z,double *f, double h) {
	double t_in, x_in,y_in, z_in,f_in;
	double kx_1, kx_2, kx_3, kx_4;
	double kz_1, kz_2, kz_3, kz_4;
	double ky_1, ky_2, ky_3, ky_4;
	double kf_1, kf_2, kf_3, kf_4;

	t_in = *t;
	x_in = *x;
	y_in = *y;
	z_in = *z;
	f_in = *f;


	kx_1 = dxdt(z_in);
	kz_1 = dzdt(z_in,f_in);

	ky_1 = dydt(f_in);
	kf_1 = dfdt(z_in,f_in);



	kx_2 = dxdt(z_in + kz_1 * h / 2);
	kz_2 = dzdt( z_in + kz_1 * h / 2, f_in + kf_1 * h / 2);

	ky_2 = dydt(f_in + kf_1 * h / 2);
	kf_2 = dfdt(z_in + kz_1 * h / 2, f_in + kf_1 * h / 2);




	kx_3 = dxdt(z_in + kz_2 * h / 2);
	kz_3 = dzdt(z_in + kz_2 * h / 2, f_in + kf_2 * h / 2);

	ky_3 = dydt(f_in + kf_2 * h / 2);
	kf_3 = dfdt(z_in + kz_2 * h / 2, f_in + kf_2 * h / 2);




	kx_4 = dxdt(z_in + kz_3 * h);
	kz_4 = dzdt( z_in + kz_3 * h, f_in + kf_3 * h);

	ky_4 = dydt( f_in + kf_3 * h);
	kf_4 = dfdt( z_in + kz_3 * h, f_in + kf_3 * h);




	t_in = t_in + h;
	x_in = x_in + h * (kx_1 + 2 * kx_2 + 2 * kx_3 + kx_4) / 6.0;
	z_in = z_in + h * (kz_1 + 2 * kz_2 + 2 * kz_3 + kz_4) / 6.0;

	y_in = y_in + h * (ky_1 + 2 * ky_2 + 2 * ky_3 + ky_4) / 6.0;
	f_in = f_in + h * (kf_1 + 2 * kf_2 + 2 * kf_3 + kf_4) / 6.0;



	*t = t_in;
	*x = x_in;
	*y = y_in;
	*z = z_in;
	*f = f_in;



}

int main() {
	double t, x,y, z,f, h;
	h = 0.01;
	int i,k,o;
	int j = 1;
	double *angulos;
	double *datos;

	angulos = new double[7];
	datos = new double[500];

	for (o = 0; o < 500; o++)
	{
		datos[o] = -1.0;
	
	}

	for (i=0;i<7;i++)
	{
		angulos[i] = 10*j;
		j = j + 1;
	}



	reinicia(&t,&x,&y,&z,&f,45*M_PI/180);


	ofstream archivo;
	archivo.open("45.txt");
	while (y>=0.0)
	{
		Kutta(&t, &x,&y, &z, &f,h);

		if (archivo.is_open()) 
		{
			
			archivo << x << " "<<y<< "\n";

		}
	}
	archivo.close();
	cout<<"La distancia recorrida en x cuando se lanza con un angulo de 45 grados es "<<x<<endl;


	ofstream a;
	a.open("angulo.txt");
	int s;
	int r;
	ofstream file;
	file.open("longitud.txt");
	



	for (k=0;k<7;k++)
	{


		reinicia(&t, &x, &y, &z, &f, angulos[k] * M_PI / 180);
		s = 0; 
		r = 0;
		while (y >=0.0) 
		{

			
			datos[s] = x;
			s = s + 1;
			
			
			Kutta(&t, &x, &y, &z, &f, h);

		}
		
		

		if (file.is_open())
		{
			file << s << " ";

		}



		for (r = 0; r < 500; r++)
		{

			if (a.is_open())
			{
				a << datos[r] << " ";

			}

		}
		a << "\n";




		reinicia(&t, &x, &y, &z, &f, angulos[k] * M_PI / 180);
		s = 0;
		r = 0;
		while (y >= 0.0) 
		{
			datos[s] = y;
			s = s + 1;


		
			Kutta(&t, &x, &y, &z, &f, h);
		}
		

		
		if (file.is_open())
		{
			file << s<< " ";

		}
		file<< "\n";

		for (r = 0; r < 500; r++)
		{

			if (a.is_open())
			{
				a << datos[r] << " ";

			}

		}
		a << "\n";


	}
	
	a.close();
	file.close();
	cout<<"El proyectil alcanza su mayor distancia en x cuando se lanza con un angulo de 20 grados"<<endl;
	return 0;
}

