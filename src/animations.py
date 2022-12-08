""" Script para graficar las soluciones registradas en los
archivos txt generados por el código en C. """

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

#Cargamos los parámetros del sistema que resolvimos:
params = np.loadtxt("./Files/params.txt")
sys = int(params)


#Cargamos los archivos txt.
#Estos fueron creados guardando un renglon sí y uno no,
#('n = 2' en el archivo 'parameters.c'), por lo que 
#estos txt tendrán la mitad de puntos espaciales y temporales. 
#Primero cargamos los arrays de espacio y tiempo:
x = np.loadtxt("./Files/x_res1.txt")
t = np.loadtxt("./Files/t_res1.txt")
x_2 = np.loadtxt("./Files/x_res2.txt")
t_2 = np.loadtxt("./Files/t_res2.txt")
x_4 = np.loadtxt("./Files/x_res4.txt")
t_4 = np.loadtxt("./Files/t_res4.txt")

#Calculamos las resoluciones, tomando en cuenta que los archivos
# de texto usados tienen sólo la mitad de los puntos originales:
dx =  (x[1] - x[0]) * 0.5
dx_2 = dx * 0.5
dx_4 = dx * 0.25

#Introducimos los valores de Nx y Nt que usaremos en este script
# (no coinciden con los Nx y Nt del código pues los txt tienen la
# mitad de los puntos):
Nx = len(x) 
Nt = len(t) 
Nx_2 = len(x_2) 
Nt_2 = len(t_2)
Nx_4 = len(x_4) 
Nt_4 = len(t_4)

#Definimos las siguientes funciones que usaremos para animar
#las gráficas.
def update(n, x, data, line):
	line.set_xdata(x)
	line.set_ydata(data[n,:])
	
def update_both(n, x1, data1, line1, x2, data2, line2):
	update(n, x1, data1, line1)
	update(n, x2, data2, line2)


#Si el sistema tiene solución analítica correspondiente a 
#alpha=1 y beta=0, entonces se corre lo siguiente:
if(sys == 0):

	#Cargamos las soluciones numéricas y analíticas, respectivamente
	phi = np.loadtxt("./Files/sol_0_res1.txt", usecols=np.arange(Nx))
	phi_2 = np.loadtxt("./Files/sol_0_res2.txt", usecols=np.arange(Nx_2))
	phi_4 = np.loadtxt("./Files/sol_0_res4.txt", usecols=np.arange(Nx_4))

	a_phi = np.loadtxt("./Files/a_sol_0_res1.txt", usecols=np.arange(Nx))
	a_phi_2 = np.loadtxt("./Files/a_sol_0_res2.txt", usecols=np.arange(Nx_2))
	a_phi_4 = np.loadtxt("./Files/a_sol_0_res4.txt", usecols=np.arange(Nx_4))
	
	#Cargamos las normas del error
	L2_error_res1 = np.loadtxt("./Files/L2_error_res1.txt")
	L2_error_res2 = np.loadtxt("./Files/L2_error_res2.txt")
	L2_error_res4 = np.loadtxt("./Files/L2_error_res4.txt")

	# Gráfica de Phi	
	fig, ax = plt.subplots()
	ax.set_xlim(-1, 1)
	ax.set_ylim(-0.1, 1.1)
	line, = ax.plot([0, 0], label=r'Solución numérica con $\Delta x = {0:.3f}$'.format(dx_4))
	#line2, = ax.plot([0, 0], label=r'Solución analítica con $\Delta x = {0:.3f}$'.format(dx_4))
	line2, = ax.plot([0, 0], label=r'Solución analítica')
	ax.legend(loc='best')
	plt.xlabel(r'$x$')
	plt.title(r'$\phi$')

	animation = FuncAnimation(fig, update_both, frames=np.arange(0,Nt_4,5), 
			fargs=(x_4, phi_4, line, x_4, a_phi_4, line2), interval=1)

	plt.grid(alpha = 0.5)
	#Descomentar lo siguiente si se quiere guardar la animación:
	#animation.save('sys0_phi.mp4',  fps=60)
	plt.show()
	
	###NOTA:
	#Para guardar la animación en formato mp4 hay que instalar ffmpeg
	#Esto lo podemos hacer con los siguientes comandos en la terminal de linux:
	#   $ sudo apt update
	#   $ sudo apt install ffmpeg

	#Gráfica de la norma L2

	plt.plot(t, L2_error_res1 , label=r'$L_2$ con $\Delta x={0:.3f}$'.format(dx))
	plt.plot(t_2[0:Nt_2:2], 4*L2_error_res2[0:Nt_2:2], label=r'$4 L_2$ con $\Delta x={0:.3f}$'.format(dx_2))
	plt.plot(t_4[0:Nt_4:4], 16*L2_error_res4[0:Nt_4:4], label=r'$16 L_2$ con $\Delta x={0:.3f}$'.format(dx_4))
	plt.xlabel(r'$t$')
	plt.legend()
	plt.title(r'Norma $L_2$')
	plt.savefig('L2.png', bbox_inches='tight')
	plt.show()



#En cambio, si no tenemos solución analítica, corremos este bloque de código:
elif(sys == 1):

	#Cargamos las soluciones numéricas y analíticas. 
	#Haremos un análisis de autoconvergencia para phi, por lo que cargamos 
	#las soluciones con 3 distintas resoluciones.
	#En el caso de pi y psi, simplemente cargaremos la solución con mayor
	#resolución pues no les haremos análisis de autoconvergencia.
	phi = np.loadtxt("./Files/sol_0_res1.txt", usecols=np.arange(Nx))
	phi_2 = np.loadtxt("./Files/sol_0_res2.txt", usecols=np.arange(Nx_2))
	phi_4 = np.loadtxt("./Files/sol_0_res4.txt", usecols=np.arange(Nx_4)) 

	pi = np.loadtxt("./Files/sol_1_res4.txt", usecols=np.arange(Nx_4))
	psi = np.loadtxt("./Files/sol_2_res4.txt", usecols=np.arange(Nx_4))


	# Gráfica de la solución numérica de Phi(t,x)
	fig, ax = plt.subplots()
	ax.set_xlim(-1, 1)
	ax.set_ylim(-0.1, 1.1)
	line, = ax.plot([0, 0], label=r'Solución numérica con $\Delta x={0:.3f}$'.format(dx_4))
	ax.legend(loc='best')
	plt.xlabel(r'$x$')
	plt.title(r'$\phi$')

	animation = FuncAnimation(fig, update, frames=np.arange(0,Nt_4,5), 
			fargs=(x_4, phi_4, line), interval=1)

	plt.grid(alpha = 0.5)
	#Descomentar lo siguiente si se quiere guardar la animación:
	#animation.save('sys1_phi.mp4',  fps=60)
	plt.show()


	#Para graficar instantáneas:
	i = 500
	ti = i * dx_4 * 0.5
	plt.plot(x_4, phi_4[0], label=r'$\phi_0(x)$')
	plt.plot(x_4, phi_4[i], label=r'$\phi($t={0:.2f}$, x)$'.format(ti))
	
	i = 1200
	ti = i * dx_4 * 0.5
	plt.plot(x_4, phi_4[i], label=r'$\phi($t={0:.2f}$, x)$'.format(ti))
	
	plt.xlabel(r'$x$')
	plt.title(r'$\phi$ con $\Delta x={0:.3f}$'.format(dx_4))
	plt.legend(loc='upper right')
	plt.xlabel(r'$x$')
	plt.grid(alpha = 0.5)
	plt.show()







	# Gráfica de la solución numérica de Pi(t,x)
	fig, ax = plt.subplots()
	ax.set_xlim(-1, 1)
	ax.set_ylim(-10, 7)
	line, = ax.plot([0, 0], label=r'Solución numérica con $\Delta x={0:.3f}$'.format(dx_4))
	ax.legend(loc='best')
	plt.xlabel(r'$x$')
	plt.title(r'$\pi$')

	animation = FuncAnimation(fig, update, frames=np.arange(0,Nt_4,5), 
			fargs=(x_4, pi, line), interval=1)

	plt.grid(alpha = 0.5)
	plt.show()


	# Gráfica de la solución numérica de Psi(t,x)
	fig, ax = plt.subplots()
	ax.set_xlim(-1, 1)
	ax.set_ylim(-10, 10)
	line, = ax.plot([0, 0], label=r'Solución numérica con $\Delta x={0:.3f}$'.format(dx_4))
	ax.legend(loc='best')
	plt.xlabel(r'$x$')
	plt.title(r'$\psi$')

	animation = FuncAnimation(fig, update, frames=np.arange(0,Nt_4,5), 
			fargs=(x_4, psi, line), interval=1)

	plt.grid(alpha = 0.5)
	plt.show()


# Análisis de autoconvergencia de phi. 
# Se utiliza que:
#	numerator = phi - phi_2
#	denominator = phi_2 - phi_4
# Y se evalúan las funciones en el mismo punto espacial y temporal.
# Ver ec. (50) del texto principal.

	numerator_auto = np.zeros([Nt,Nx])
	denominator_auto = np.zeros([Nt,Nx])

	for i in range(Nt):
		for j in range(Nx):
			numerator_auto[i, j] = np.abs(phi[i, j] - phi_2[2*i, 2*j])
			denominator_auto[i, j] = np.abs(phi_2[2*i, 2*j] - phi_4[4*i, 4*j])


	fig, ax = plt.subplots()
	ax.set_xlim(-1, 1)

	#Reescalamos el eje 'y' con el 110% de los valores máximos:
	max_err = np.max(np.abs(numerator_auto))*1.1 
	ax.set_ylim(-0.1*max_err, max_err)
	line, = ax.plot([0, 0], label=r'$|\phi_{\Delta x } - \phi_{\Delta x /2}|$')#, marker='x')
	line2, = ax.plot([0, 0], label=r'$4|\phi_{\Delta x /2} - \phi_{\Delta x /4}|$')
	ax.legend(loc='upper center')
	plt.xlabel(r'$x$')
	plt.title(r'Test de autoconvergencia de $\phi$ con $\Delta x={0:.3f}$'.format(dx))
		
	animation = FuncAnimation(fig, update_both, frames=np.arange(0,Nt,5), 
			fargs=(x, numerator_auto, line, x, 4*denominator_auto, line2), interval=1)

	plt.grid(alpha = 0.5)
	#Descomentar lo siguiente si se quiere guardar la animación:
	#animation.save('sys1_auto.mp4',  fps=60)
	plt.show()  
