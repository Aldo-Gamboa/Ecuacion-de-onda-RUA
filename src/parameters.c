/* Script para inicializar los parámetros utilizados a lo
largo del código. */

#include <stdio.h>
#include <math.h>
#include "parameters.h"

extern int N, n, Nx, Nt, res, sys;
extern double xi, xf, ti, tf, rho, dx, dt;

int parameters(){

/*  Esta función inicializa los valores de los parámetros
    utilizados en el código. Algunos de estos parámetros
    deben ser asignados por el usuario.
    
    Descripción de los parámetros:

    'sys' es igual a '0' si es que alpha = 1 y beta = 0, 
    y es igual a '1' en otro caso. El código tiene dos 
    versiones caracterizadas por esta variable 'sys'. 
    Si sys = 0, entonces estamos en el caso en que α = 1 
    y β = 0, y por lo tanto hay solución analítica; en 
    este caso se calcula la solución numérica de φ y se 
    compara con la solución analítica, y se calcula la 
    norma L2 del error para la resolución seleccionada. 
    Si sys = 1, entonces α y β son funciones arbitrarias 
    que podemos modificar en el script 'analytic.c', y 
    en este caso solamente se calcula la solución 
    numérica del sistema y se realiza un análisis de 
    autoconvergencia para φ.

    'N' es el número de variables independientes del 
    sistema. En nuestro sistema de primer orden de la 
    ecuación de onda tenemos N = 3 ('phi', 'pi','psi').

    'n' indica cada cuántos renglones se guardarán los
    datos en archivos txt.

    'Nx' es el número de celdas espaciales en la malla,
    tal que 'Nx+1' es el número de puntos en esta malla
    (contando los puntos iniciales y finales).

    'Nt' es el número de celdas temporales en la malla,
    tal que 'Nt+1' es el número de puntos en esta malla
    (contando los puntos iniciales y finales).

    'xi' y 'xf' son los puntos espaciales iniciales y 
    finales.

    'ti' y 'tf' son los puntos temporales iniciales y 
    finales.
    
    'dx' es el espaciamiento (homogéneo) entre puntos 
    espaciales.

    'dt' es el espaciamiento (homogéneo) entre puntos 
    temporales.

    'rho' es el factor de CFL, tal que rho = dt/dx.

    'res' es la resolución de la malla, donde res = 1
    representa el tamaño original de la malla (el cual
    escoge el usuario al seleccionar 'xi', 'xf' y 'Nx'), 
    res = 2 indicará una malla con el doble de resolución, 
    y res = 4 indicará una malla con el cuádruple de la
    resolución original. Este parámetro es útil para 
    hacer el análisis de errores numéricos.

*/
   
    N = 3;
    n = 2;
    sys = 1;
    res = 1;

    /* Seleccionaremos el número de espaciamientos en la 
    malla espacial, así como los puntos iniciales y 
    finales. Eso nos determinará a 'dx'.
    */
    Nx = 500;
    xi = -1.;
    xf = 1.;
    dx = (xf - xi)/Nx;
 
    /* Elegiremos el factor de CFL y los puntos
    temporales iniciales y finales. Eso nos determinará 
    a 'dt' y 'Nt'. 
    */
    rho = 0.5;
    ti = 0.;
    tf = 1.5;
	dt = rho * dx;
	Nt = ceil((tf - ti)/dt);
    /* Se utiliza la función 'ceil' para obtener un número
    entero de espaciamientos temporales. */ 

    /* Imprimimos en pantalla los parámetros de la malla. */
    printf("dx = %f\n", dx);
	printf("dt = %f\n", dt);
	printf("Nx = %d\n", Nx);
	printf("Nt = %d\n", Nt);
 
    /* Imprimimos en un txt algunos parámetros de la malla. Notar
    que debe existir un directorio llamado 'Files' (en el mismo
    directorio donde se encuentra el archivo 'exe'. 
    El orden de estos parámetros está coordinado con el script
    para graficar de python, 'animations.py'. */
    FILE *params;
    params = fopen("./Files/params.txt", "w");
    fprintf(params, "#sys:\n%d\n", sys);
    fclose(params); 

    return 0;
}
