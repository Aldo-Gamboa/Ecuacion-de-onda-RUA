/* Script con las funciones analíticas que aparecen a lo largo 
del trabajo. */

#include <stdio.h>
#include <math.h>
#include "analytic.h"

extern int N, Nx, Nt, res, n, sys;

/* Función de lapso: */
double alpha(double x){
	double r;
	if(sys == 0){
		r = 1.0;
	}
	else if(sys == 1){
		//Modificar la siguiente r si se quieren explorar otras
		//funciones para alpha.
		r = 1.0;
		//r = 0.25 * tanh(10 * x) + 0.75;
	}
	return r;
}

/* Función de shift: */
double beta(double x){
	double r;
	if(sys == 0){
		r = 0.0;
	}
	else if(sys == 1){
		//Modificar la siguiente r si se quieren explorar otras
		//funciones para beta.
		//r = 0.0;
		r = x;
	}
	return r;
}

double a_f(double x, double t, int k){
	/* 	Función que calcula las soluciones analíticas phi, 
		pi y psi para la ec. de onda con alpha = 1 y beta = 0 
		en el punto espacial 'x' al tiempo 't', para datos
		iniciales Gaussianos. 

		k = 0 corresponde a Phi, 
		k = 1 corresponde a Pi,
		k = 2 corresponde a Psi. 
		
		Dada la solución analítica Phi, entonces: 
		\pi = \partial_t \phi
		\psi = \partial_x \phi
		
		Con estas fórmulas calculamos las siguientes
		expresiones en esta función a_f.
	*/

	double r;
	double A = 1., s = 0.1, x0 = 0.;
	/* 'A' es la amplitud de la Gaussiana y 's' el ancho
	de la distribución. */

	if(k == 0) // Phi
		r = 0.5*A*exp(-pow(x-x0+t,2)/pow(s,2)) + 0.5*A*exp(-pow(x-x0-t,2)/pow(s,2));

	else if(k == 1) // Pi
		r = A*( -(x-x0+t)*exp(-pow(x-x0+t,2)/pow(s,2)) + (x-x0-t)*exp(-pow(x-x0-t,2)/pow(s,2)) )/pow(s,2);

	else if(k == 2) // Psi
		r = - A*( (x-x0+t)*exp(-pow(x-x0+t,2)/pow(s,2)) + (x-x0-t)*exp(-pow(x-x0-t,2)/pow(s,2)) )/pow(s,2);	
	
	return r;
}

int analytic(double x[], double t[]){
	/* Función que guarda las soluciones analíticas en un archivo txt. */

	char filename[30];
	int i, j, k;

	/* Archivos donde colocaremos las soluciones analíticas: */
	FILE *a_sol[3]; 

	/* Este código nos permite ir cambiando el nombre de los
	txt generados, de acuerdo a si se trata de Phi, Pi o Psi,
	y la resolución involucrada. */
	for(k = 0; k < N; k++){	
		sprintf(filename, "./Files/a_sol_%d_res%d.txt", k, res);  
		a_sol[k] = fopen(filename, "w"); 
		for(i = 0; i <= Nt; i=i+n){
			for(j = 0; j <= Nx; j=j+n)
				fprintf(a_sol[k], "%.8f\t", a_f(x[j], t[i], k));
			fprintf(a_sol[k], "\n");	
		}
		fclose(a_sol[k]);
	}

	return 0;
}
