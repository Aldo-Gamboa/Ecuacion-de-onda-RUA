/* Script principal para resolver la ecuación de onda. */

/* Cargamos paqueterías de C. */
#include <stdio.h>
#include <math.h>
#include <malloc.h> 

/* Cargamos los archivos que contienen funciones utilizadas
por la función main. */
#include "parameters.h"
#include "tx_arrays.h" 
#include "initial.h" 
#include "evolution.h" 
#include "analytic.h" 

/* Definimos variables globales. (Ver archivo 'parameters.c'
para una descripción de estas variables.) */	
int N, n, Nx, Nt, res, sys;
double xi, xf, ti, tf, rho, dx, dt;

int main(void){
	
	/* Inicializamos los parámetros. */
	parameters();
	
	/* Creamos dos arrays de 2 dimensiones para guardar temporalmente
	dos pasos de tiempo de las soluciones. 
	Con la función malloc asignamos nuestros arrays a un segmento de
	la memoria de la computadora. Esto se hace para no tener problema
	con la gran cantidad de puntos que tienen los arrays. */
	double **sol1 = (double**)malloc(sizeof(double*) * N); 
	double **sol2 = (double**)malloc(sizeof(double*) * N);
	for (int k = 0; k < N; k++){
		sol1[k] = (double*)malloc(sizeof(double) * (Nx+1));
		sol2[k] = (double*)malloc(sizeof(double) * (Nx+1));
	}
	
	/* Definimos los arrays de espacio y de tiempo del grid. */
	double x[Nx+1], t[Nt+1];

	/* Llenamos los arrays 'x' y 't' de acuerdo a nuestros parámetros: */
	tx(x, t);

	/* Calculamos la solución analítica si es que alpha = 1 y beta = 0: */
	if(sys == 0){
		analytic(x, t); 
	}

	/* Implementamos las condiciones iniciales: */
	initial(x, t, sol1);

	/* Hacemos la evolución del sistema: */
	evolution(x, t, sol1, sol2);
}
