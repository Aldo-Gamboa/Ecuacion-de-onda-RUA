/*  Script para construir el grid espacial y temporal.	
	
	El grid espacial comienza desde 'xi' hasta 'xf' con
	un espaciamiento homogéneo de 'dx', y el grid temporal 
	comienza desde 'ti' hasta 'tf' con espaciamiento
	homogéneo de 'dt', que están relacionados a través 
	del factor de Courant-Friedrichs-Lewy 'rho = dt/dx'. */

#include <stdio.h>
#include "tx_arrays.h"

extern int Nx, Nt, res, n;
extern double xi, xf, ti, tf, dx, dt;

int tx(double x[], double t[]){
	/* Esta función crea los arrays de tiempo y distancia
	   que se usarán en el código, y los imprime en un 
	   archivo txt.
	   Recibe dos arrays 1-dimensionales, 'x' y 't'.	*/

	/* Definimos las variables que usaremos en este	script. 
		'i' y 'j' son variables para contar en ciclos.
		'n' es el número que indica cada cuántos renglones
		de los arrays de distancia 'x' y tiempo 't' se van
		a guardar en un txt. Por ejemplo, si n = 1, se 
		guardarán todos los valores de los arrays, y si
		n = 2 se guardará un renglón sí y el siguiente no,
		sucesivamente. 	*/
	int i, j;

	/* Creamos los pointers para los arrays de tiempo y 
	distancia. */
	FILE *p_t, *p_x;

	/* Creamos unas variables tipo 'char' para ponerle
	nombre a los txt generados.	
	El número 40 se escogió arbitrariamente, y significa
	que la longitud de caracteres de estos txt no puede
	exceder de 40. */
 	char t_s[40], x_s[40];

	/* Los arrays se guardarán en la carpeta 'Files' y su
	nombre dependerá de la resolución con la que se esté
	trabajando. Por ejemplo, si trabajamos con la 
	resolución número 1, entonces los nombres de los 
	archivos serán 't_res1.txt' y 'x_res1.txt'. */
	sprintf(t_s, "./Files/t_res%d.txt", res);  
	sprintf(x_s, "./Files/x_res%d.txt", res);
	
 	/* Creamos el array de tiempo: */
	p_t = fopen(t_s, "w"); 
	for(i = 0; i <= Nt; i++){
		t[i] = ti + i*dt;
		if(i % n == 0)
			fprintf(p_t, "%f\n", t[i]);
	}
	fclose(p_t);
	
	/* Creamos el array de espacio: */
	p_x = fopen(x_s, "w"); 
	for(j = 0; j <= Nx; j++){
		x[j] = xi + j*dx;
		if(j % n == 0)
			fprintf(p_x, "%f\n", x[j]);
	}		
	fclose(p_x);
	
	return 0;
}
