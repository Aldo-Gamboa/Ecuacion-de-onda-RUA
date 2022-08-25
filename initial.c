/* Script para calcular las condiciones iniciales de las 
variables involucradas. */

#include <stdio.h>
#include <math.h>
#include "initial.h"
#include "analytic.h"

extern int N, Nx, res, sys, n;
extern double xi, xf, dt;

int initial(double x[], double t[], double **sol){

	/* En este caso, las entradas de 'sol' representan las variables
	del sistema de primer orden del siguiente modo:
	sol[0][j] = Phi	
	sol[1][j] = Pi
	sol[2][j] = Psi
	*/

	int j, k;
	FILE *solutions, *L2_error;
	char filename[30];

	/* Llenado de las condiciones iniciales. */
	for(k = 0; k < N; k++){ 
		for(j = 0; j <= Nx; j++) 
			sol[k][j] = a_f(x[j], 0., k);
	}

	/*  Imprimimos en un txt los valores de las variables, cada
	n valores. */
	for(k = 0; k < N; k++){ 
		sprintf(filename, "./Files/sol_%d_res%d.txt", k, res);  
		solutions = fopen(filename, "w");

		for(j = 0; j <= Nx; j=j+n)
			fprintf(solutions, "%.8f\t", sol[k][j]);			
		
		fprintf(solutions, "\n");
		fclose(solutions);
	}

 	/* Ahora, si tenemos una solución analítica, entonces
 	damos las condiciones iniciales para el error, L2.
 	Dado que al tiempo inicial el error es 0, entonces
 	escribimos ese valor en su txt correspondiente. */
 	if(sys == 0){
	 	if(res == 1){
	 		L2_error = fopen("./Files/L2_error_res1.txt", "w");
	 		fprintf(L2_error, "0.0\n");
	 		fclose(L2_error);
	 	}
	 	else if(res == 2){
	 		L2_error = fopen("./Files/L2_error_res2.txt", "w");
	 		fprintf(L2_error, "0.0\n");
	 		fclose(L2_error);
	 	}
	 	else if(res == 4){
			L2_error = fopen("./Files/L2_error_res4.txt", "w");
			fprintf(L2_error, "0.0\n");
			fclose(L2_error);
	 	}
 	}	
		
	return 0;
}
