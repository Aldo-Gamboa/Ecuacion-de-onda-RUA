/* Script para calcular la evolución del sistema visto 
como un sistema de primer orden. */

#include <stdio.h>
#include <math.h>

#include "evolution.h"
#include "finite_differences.h"
#include "time_integrators.h"
#include "boundary.h"
#include "analytic.h"

extern int Nx, Nt, N, n, res, sys;
extern double dx, dt;

int rhs(int j, double x[], double **sol, double RHS[]){	

	/* Lado derecho del sistema de ecuaciones para Phi, Pi y Psi. 

	Tenemos las siguientes identificaciones:
	sol[0][j] = Phi	
	sol[1][j] = Pi
	sol[2][j] = Psi
	*/

	/* Arrays que representarán los productos:
	alpha*Psi, alpha*Pi, beta*Psi y beta*Pi, respectivamente. */
	double aPsi[Nx+1], aPi[Nx+1], bPsi[Nx+1], bPi[Nx+1];

	/* Se llenan estos arrays así para efectuar las derivadas (ya sean
	cargadas hacia un solo lado o centradas) de manera que no se necesite
	llenar todo el array y sólo se usen los puntos que interesan. Este
	método ahorra mucho tiempo computacional. */
	if(j != 0 && j != Nx){//Malla interna.
		for(int i = j-1; i <= j+1; i=i+2){
			aPsi[i] = alpha(x[i]) * sol[2][i];
			aPi[i] = alpha(x[i]) * sol[1][i];
			bPsi[i] = beta(x[i]) * sol[2][i];
			bPi[i] = beta(x[i]) * sol[1][i];
		}
	}
 	else if(j == 0){//Extremo izquierdo de la malla.
		for(int i = 0; i <= 2; i++){
			aPsi[i] = alpha(x[i]) * sol[2][i];
			aPi[i] = alpha(x[i]) * sol[1][i];
			bPsi[i] = beta(x[i]) * sol[2][i];
			bPi[i] = beta(x[i]) * sol[1][i];
		}
	}
	else{//Extremo derecho de la malla.
		for(int i = Nx-2; i <= Nx; i++){
			aPsi[i] = alpha(x[i]) * sol[2][i];
			aPi[i] = alpha(x[i]) * sol[1][i];
			bPsi[i] = beta(x[i]) * sol[2][i];
			bPi[i] = beta(x[i]) * sol[1][i];
		}
	} 

	//Phi. Ec no numerada después de la ec(25) del artículo de Guzmán.
	RHS[0] = alpha(x[j]) * sol[1][j] + beta(x[j]) * sol[2][j];  
	//Pi. Ec (24) artículo de Guzmán.
	RHS[1] = centered(j, aPsi) + centered(j, bPi);
	//Psi. Ec (25) artículo de Guzmán.
	RHS[2] = centered(j, aPi) + centered(j, bPsi);
	
	return 0;
}

int evolution(double x[], double t[], double **sol1 , double **sol2){
	/* Función para calcular la evolución del sistema 
	de primer orden. */

	int i, j, k;
	FILE *solutions[N], *L2_error;
	double e; //Variable que almacenará los errores.
	char filename[30];

	/* Abrimos los archivos de texto de las soluciones que se van a 
		guardar. */
	for(k = 0; k < N; k++){ 
		sprintf(filename, "./Files/sol_%d_res%d.txt", k, res);  
		solutions[k] = fopen(filename, "a");
	}
	
	/* Ahora, si tenemos solución analítica, entonces 
	abrimos los archivos de texto donde se guardarán
	las normas de los errores. */
	if(sys == 0){
		if(res == 1){
			L2_error = fopen("./Files/L2_error_res1.txt", "a");
	 	}
	 	else if(res == 2){
	 		L2_error = fopen("./Files/L2_error_res2.txt", "a");
		}
		else if(res == 4){
	 		L2_error = fopen("./Files/L2_error_res4.txt", "a");
		}
	}
	
	/* Llenado de las soluciones con el método integrador. */ 
	for(i = 1; i <= Nt ; i++){ 

		/* Corremos el método integrador y obtenemos las 
		nuevas soluciones al tiempo i. */
		
		RK3_grid(x, sol1, sol2, rhs, boundary_Lagrange);
		
		/* Con las nuevas soluciones, calculamos el error numérico,
		si es que hay solución analítica (ver ec. (51) del texto
		principal): */
		if(sys == 0){
	 		e = 0.;
	 		if(i % n == 0){
	 			for(j = 0; j <= Nx; j++){
	 				e = e + pow(sol2[0][j] - a_f(x[j], t[i], 0), 2);
	 			}
	 			fprintf(L2_error, "%.8f\n", sqrt(dx * e));
	 		} 
		}
		
		/* Renovamos los arrays de soluciones: */
		for(k = 0; k < N; k++){
			for(j = 0; j <= Nx; j++)
				sol1[k][j] = sol2[k][j];
		}

		/* Guardamos en los txt algunas variables: */
		if(i % n == 0){
			for(k = 0; k < N; k++){
				for(j = 0; j <= Nx; j=j+n)
					fprintf(solutions[k], "%.8f\t", sol2[k][j]);								
				fprintf(solutions[k], "\n");
			}
		}				
	
	}

	/* Cerramos los archivos txt: */
	for(k = 0; k < N; k++){
		fclose(solutions[k]); 
	}
	
	if(sys == 0){
		fclose(L2_error);
	}

	return 0;
}
