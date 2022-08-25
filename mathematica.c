/* Script que implementa métodos matemáticos, en este caso una interpolación
polinomial de Lagrange. */

#include <stdio.h>
#include <math.h>
#include "mathematica.h"

double Lagrange(double z, double x[], double y[], int p){

    /*	Método de extrapolación/interpolación de Lagrange.
	
	p: Número de puntos a extrapolar.	   */

	double a, b = 0;
	
	for(int i = 0; i < p; i++){
		a = y[i];
		for(int j = 0; j < p; j++){
			if(j == i){
			}
			else{
				a = a*(z-x[j])/(x[i]-x[j]);		
			}
		}
		b = b + a;
	}
	return b;
}