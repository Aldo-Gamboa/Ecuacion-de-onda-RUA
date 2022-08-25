/* Script que implementa el método integrador de Runge Kutta con 
3 pasos, para el sistema de primer orden. (Ver ecs. posteriores a la
ec. (35) del artículo de Guzmán.) Nótese que esta implementación es
para un sistema autónomo, pues en el 'right hand side' no aparece
dependencia en la variable independiente 't'.*/

#include <stdio.h>
#include <malloc.h> 
#include <math.h>

#include "time_integrators.h"

extern int N, Nx;
extern double dt;

int RK3_grid(double x[], double **sol1 , double **sol2, int (*rhs)(), int (*boundary)()){ 
	
	double RHS[N];
	int j, k;

	double **K_RHS = (double**)malloc(sizeof(double*) * N);
	for (k = 0; k < N; k++)
		K_RHS[k] = (double*)malloc(sizeof(double) * (Nx+1));
	

	//------------Primer paso------------
	for(j = 0; j <= Nx; j++){
		(*rhs)(j, x, sol1, RHS);
		for(k = 0; k < N; k++)
			K_RHS[k][j] = RHS[k];
	}
	for(j = 0; j <= Nx; j++){
		for(k = 0; k < N; k++)
			sol2[k][j] = sol1[k][j] + dt * K_RHS[k][j];
	}
	(*boundary)(x, sol2);
	/* Nótese que se aplican las condiciones de frontera después de
	cada paso intermedio! */
	
	//------------Segundo paso------------
	for(j = 0; j <= Nx; j++){
		(*rhs)(j, x, sol2, RHS);
		for(k = 0; k < N; k++)
			K_RHS[k][j] = RHS[k];
	}
	for(j = 0; j <= Nx; j++){
		for(k = 0; k < N; k++)
			sol2[k][j] = 0.75 * sol1[k][j] + 0.25 * sol2[k][j] + 0.25 * dt * K_RHS[k][j]; 
	}
	(*boundary)(x, sol2);

	//------------Tercer paso------------
	for(j = 0; j <= Nx; j++){
		(*rhs)(j, x, sol2, RHS);
		for(k = 0; k < N; k++)
			K_RHS[k][j] = RHS[k];
	}
	for(j = 0; j <= Nx; j++){
		for(k = 0; k < N; k++)
			sol2[k][j] = sol1[k][j] / 3. + 2. * sol2[k][j] / 3. + 2. * dt * K_RHS[k][j] / 3.;
	}
	(*boundary)(x, sol2);

	return 0;
}