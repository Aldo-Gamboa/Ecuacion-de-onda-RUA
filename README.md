# Resolución de la ecuación de onda usando el método líneas

Material didáctico complementario del trabajo titulado "Resolución de la ecuación de onda usando el método de líneas", para la Red Universitaria de Aprendizaje (RUA) de la Universidad Nacional Autónoma de México (UNAM). 

 Autores: Aldo Gamboa (aldojavier@ciencias.unam.mx) y Néstor Ortiz (nestor.ortiz@nucleares.unam.mx).

 Última modificación: 25 de agosto de 2022.



## Instrucciones para correr el código en una terminal de Linux.

1. Seleccionar los parámetros deseados en el archivo 'parameters.c'. En dicho archivo hay una descripción de los parámetros disponibles. 
Principalmente hay que elegir si estamos en el caso con α = 1 y β = 0 (sys = 0) o no (sys = 1), debemos elegir el dominio espacial y temporal con el que trabajaremos, y debemos escoger el número de divisiones N de nuestro dominio espacial, el cual determinará la resolución ∆x y ∆t a través del factor de CFL. Los parámetros 'N' y 'res' serán particularmente importantes para correr este código (ver paso 3).

2. Ejecutar en la terminal el siguiente comando:

	../Fuente$ source compile_and_run.txt
	
	Se nos generarán archivos con formato txt en los cuáles estará la solución numérica del sistema para los parámetros 	escogidos. Estos archivos se guardarán automáticamente dentro del directorio 'Files'.


3. Para llevar a cabo el análisis de errores este código está diseñado para ser ejecutado manualmente tres veces (con tres resoluciones distintas). Primero, debemos correr el código (paso 2) con un cierto valor de N (en nuestro trabajo escrito tomamos N = 500), el cual estará asociado a la primera resolución etiquetada como res = 1. Luego, volveremos a correr el código (paso 2, nuevamente) pero aumentando al doble la N (en nuestro ejemplo cambiamos a N = 1000) y cambiando el valor de la variable res a res = 2. Por último, volvemos a doblar el valor de N (en nuestro ejemplo cambiamos a N = 2000), cambiamos a res = 4, y corremos el código (paso 2, nuevamente). Es importante realizar así este proceso pues se generarán archivos de texto etiquetados con las resoluciones, que posteriormente serán utilizados por el script animations.py. De esta manera, si ya se tienen los intervalos espacial y temporal fijos, y ya se ha decidido si trabajar con sys = 0 ó sys = 1, entonces lo único que resta hacer es cambiar manualmente el valor de N y de res, y ejecutar el código para tres elecciones de N y res.

4. Una vez obtenidos los datos para tres resoluciones distintas, ejecutar en la terminal el siguiente comando para obtener las animaciones:

	../Fuente$ python3 animations.py
	
	En este caso, no hay necesidad de modificar nada, pues ya este script de Python ya está automatizado para recibir los archivos de texto generados con el programa escrito en C.

5. ¡Listo! Si desea ver más configuraciones, se invita al lector a modificar los parámetros y/o el código.

**NOTA:** En caso de que se trabaje en otro sistema operativo distinto a Linux, se tendría que investigar la manera de compilar el archivo main con todos los scripts ocupados, y posteriormente ejecutarlo.


## Descripción general de los archivos contenidos en el directorio 'Fuente'.

* El directorio 'Files' sirve para almacenar los datos que se generan con el código. Este directorio debe existir, pues de otra manera el código no tendrá en dónde almacenar los datos y arrojará un error. Si no existe, será creado por el archivo 'compile_and_run.txt'.

* Los archivos con extensión '.c' (por ejemplo, 'analytic.c') son los scripts escritos en lenguaje C que componen al código completo, y cada uno está especializado para realizar determinadas tareas del código.

* Los archivos con extensión '.h' (por ejemplo, 'analytic.h') son los 'headers' y sirven para que los scripts se comuniquen entre sí. En estos 'headers' se coloca únicamente el nombre de las funciones (y sus variables dependientes) definidas en su script con extensión '.c' asociado. Por ejemplo, en el archivo 'analytic.h' vemos que están escritas todas las funciones definidas en 'analytic.c'; si agregáramos o quitáramos alguna función de 'analytic.c', entonces tendríamos que modificar acordemente el archivo 'analytic.h'.

* El archivo 'compile_and_run.txt' contiene los comandos necesarios para que la terminal de Linux integre los archivos con extensión '.c' y '.h' en un solo archivo ejecutable llamado 'exe', y también contiene el comando para ejecutar dicho archivo 'exe'. Todo esto se realiza al escribir el comando 'source compile_and_run.txt' en la terminal, como se indicó anteriormente en este readme.

## Descripción breve de cada archivo.

* El archivo 'animations.py' es el script escrito en lenguaje Python, cuya función es graficar los datos generados por el código en C, y hacer el análisis de autoconvergencia con dichos datos.

* El archivo 'main.c' es el script principal en el cual está contenido el método de resolución numérico empleado. Este archivo invoca a los distintos scripts conforme se va ejecutando y, de manera general, posee el siguiente flujo de acciones:
	1. Inicializa parámetros del problema.
	2. Provee datos iniciales 
	3. Evoluciona el sistema.

* Los archivos 'analytic.c' y 'analytic.h' contienen el código necesario para calcular las funciones analíticas que aparecen en el problema.

* Los archivos 'boundary.c' y 'boundary.h' contienen el código necesario para calcular las condiciones de frontera del problema.

* Los archivos 'evolution.c' y 'evolution.h' contienen el código necesario para evolucionar el sistema de ecuaciones.

* Los archivos 'finite_differences.c' y 'finite_differences.h' contienen el código necesario para calcular primeras derivadas de funciones de manera discretizada. Se incluyen fórmulas para calcular las derivadas ladeadas y centradas, con error de orden O(2).

* Los archivos 'initial.c' y 'initial.h' contienen el código necesario para dar las condiciones iniciales del sistema de ecuaciones.

* Los archivos 'mathematica.c' y 'mathematica.h' contienen el código necesario para implementar métodos matemáticos. En nuestro caso simple, solamente está incluido el método de interpolación/extrapolación de Lagrange.

* Los archivos 'parameters.c' y 'parameters.h' contienen el código necesario para establecer los parámetros del sistema.

* Los archivos 'time_integrators.c' y 'time_integrators.h' contienen el código necesario para implementar la evolución temporal con el método de RK3.

* Los archivos 'tx_arrays.c' y 'tx_arrays.h' contienen el código necesario para crear los arrays de espacio y tiempo de la malla.
