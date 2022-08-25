/* Script para calcular derivadas con diferencias finitas. */

#include <stdio.h>
#include "finite_differences.h"

extern int Nx;
extern double dx;

double centered(int j, double f[]){
	/* Función que calcula la derivada en el punto x[j].
	Si estamos en los extremos de la malla (j=0 o j=Nx),
	entonces se calcula una derivada ladeada. */

	double r;
	if(j != 0 && j != Nx){
	/* Calcula la derivada centrada alrededor de j. */
		r = (f[j+1] - f[j-1])/(2. * dx);
	}
	else if (j == 0){
	/* Calcula la derivada en un punto j con puntos a la derecha. */
		r = (-f[j+2] + 4 * f[j+1] - 3 * f[j])/(2.*dx);
	}
	else{
	/* Calcula la derivada en un punto j con puntos a la izquierda. */
		r = (f[j-2] - 4 * f[j-1] + 3 * f[j])/(2.*dx);
	}

	return r;
}
