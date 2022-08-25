/* Script para implementar condiciones de frontera. 
En este caso se usa una extrapolación de Lagrange. */

#include <stdio.h>
#include <math.h>
#include "boundary.h"
#include "mathematica.h"

extern int Nx;

/* Ecuaciones para los eigenmodos. (Ver ecs.(34) y subsecuentes.) */

double wL(int j, double **sol){//Modo izquierdo.
	return 0.5 * (sol[1][j] + sol[2][j]);
}

double wR(int j, double **sol){//Modo derecho.
	return 0.5 * (sol[1][j] - sol[2][j]);
}

int boundary_Lagrange(double x[], double **sol){ 
	/* Función que usa extrapolaciones de Lagrange para calcular
	el valor de los eigenmodos en las fronteras. */

	int i, p = 5;
	double X[p], Y[p], l, r;
	
	/* Hacemos la extrapolación para el punto x[0]. */
	for(i = 0; i < p; i++){
		X[i] = x[i+1];
		Y[i] = wL(i+1, sol); 
	}
	
	/* Usamos la función 'Lagrange' definida en 'mathematica.c'. */
	l = Lagrange(x[0], X, Y, p);
	
	sol[1][0] = l; //Pi en x[0]
	sol[2][0] = l; //Psi en x[0]
	

	/* Hacemos la extrapolación para el punto x[Nx]. */
	for(i = 0; i < p; i++){
		X[i] = x[Nx-p+i];
		Y[i] = wR(Nx-p+i, sol); 
	}
	
	r = Lagrange(x[Nx], X, Y, p);
	
	sol[1][Nx] = r; //Pi en x[Nx]
	sol[2][Nx] = -r; //Psi en x[Nx]
	
	return 0;
} 
