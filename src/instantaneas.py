""" Script para graficar las tomas instantáneas de las soluciones registradas en los
archivos txt generados por el código en C. """

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import rcParams
rcParams["savefig.dpi"] = 200
rcParams["figure.dpi"] = 100
rcParams["font.size"] = 15

plt.rc('text', usetex=True)
plt.rc('text.latex', preamble=r' \usepackage{amssymb} \usepackage{amsmath}')

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



#Si el sistema tiene solución analítica correspondiente a 
#alpha=1 y beta=0, entonces se corre lo siguiente:
if(sys == 0):

	phi_4 = np.loadtxt("./Files/sol_0_res4.txt", usecols=np.arange(Nx_4))
	a_phi_4 = np.loadtxt("./Files/a_sol_0_res4.txt", usecols=np.arange(Nx_4))
	
	#Cargamos las normas del error
	L2_error_res1 = np.loadtxt("./Files/L2_error_res1.txt")
	L2_error_res2 = np.loadtxt("./Files/L2_error_res2.txt")
	L2_error_res4 = np.loadtxt("./Files/L2_error_res4.txt")
	
	#Graficamos la condición inicial:
	plt.plot(x_4, phi_4[0], label=r'$\phi_0(x)$')
	
	#Graficamos una toma instantánea de la solución:
	i = 600
	ti = 2*i * dx_4 * 0.5

	plt.plot(x_4, phi_4[i], label=r'$\phi_\textrm{{num}}(t={t:.1f}, x)$'.format(t=ti))
	plt.plot(x_4, a_phi_4[i], label=r'$\phi_\textrm{{ana}}(t={0:.1f}, x)$'.format(ti), linestyle='dashed', color='red')
	
	plt.xlabel(r'$x$')
	##plt.title(r'$\phi$ con $\Delta x={0:.3f}$'.format(dx_4))
	plt.title(r'$\phi$')
	plt.legend(loc='upper right')
	plt.xlabel(r'$x$')
	plt.grid(alpha = 0.5)
	plt.savefig('fig1.png', bbox_inches='tight')
	plt.show()
	
	
	#Gráfica de la norma L2

	plt.plot(t, L2_error_res1 , label=r'$L_2$ $\textrm{{con}}$ $\Delta x={0:.3f}$'.format(dx))
	plt.plot(t_2[0:Nt_2:2], 4*L2_error_res2[0:Nt_2:2], label=r'$4 L_2$ $\textrm{{con}}$ $\Delta x={0:.3f}$'.format(dx_2), linestyle='dashed')
	plt.plot(t_4[0:Nt_4:4], 16*L2_error_res4[0:Nt_4:4], label=r'$16 L_2$ $\textrm{{con}}$  $\Delta x={0:.3f}$'.format(dx_4), linestyle='dotted', color='red')
	plt.xlabel(r'$t$')
	plt.legend()
	plt.title(r'$L_2$')
	plt.savefig('fig2.png', bbox_inches='tight')
	plt.show()
	
#En cambio, si no tenemos solución analítica, corremos este bloque de código:
elif(sys == 1):

	phi = np.loadtxt("./Files/sol_0_res1.txt", usecols=np.arange(Nx))
	phi_2 = np.loadtxt("./Files/sol_0_res2.txt", usecols=np.arange(Nx_2))
	phi_4 = np.loadtxt("./Files/sol_0_res4.txt", usecols=np.arange(Nx_4))
 
	#Graficamos la condición inicial:
	plt.plot(x_4, phi_4[0], label=r'$\phi_0(x)$')
	
	#Para graficar instantáneas a dos niveles de tiempo distintos (en este
	#caso tomamos i=500 e i=1200):
	i = 500
	ti = 2*i * dx_4 * 0.5

	plt.plot(x_4, phi_4[i], label=r'$\phi(t={0:.1f}, x)$'.format(ti))
	
	i = 1200
	ti = 2*i * dx_4 * 0.5
	plt.plot(x_4, phi_4[i], label=r'$\phi(t={0:.1f}, x)$'.format(ti), 		color='r')
	
	plt.xlabel(r'$x$')
	plt.title(r'$\phi$')
	plt.legend(loc='upper right')
	plt.xlabel(r'$x$')
	plt.grid(alpha = 0.5)
	plt.savefig('fig3.png', bbox_inches='tight')
	plt.show()
	
	
	#Para graficar instantáneas de la gráfica de autoconvergencia:
	numerator_auto = np.zeros([Nt,Nx])
	denominator_auto = np.zeros([Nt,Nx])

	for i in range(Nt):
		for j in range(Nx):
			numerator_auto[i, j] = np.abs(phi[i, j] - phi_2[2*i, 2*j])
			denominator_auto[i, j] = np.abs(phi_2[2*i, 2*j] - phi_4[4*i, 4*j])
			
	max_err = np.max(np.abs(numerator_auto))*1.1 
	plt.ylim(-0.1*max_err, max_err)
	
	i = 375
	ti = 2*i * dx * 0.5
	
	plt.plot(x, numerator_auto[i], label=r'$|\phi_{\Delta x } - \phi_{\Delta x /2}|$')
	plt.plot(x, 4*denominator_auto[i], label=r'$4|\phi_{\Delta x /2} - \phi_{\Delta x /4}|$', linestyle='dashed')
	plt.legend(loc='upper right')
	plt.xlabel(r'$x$')
	plt.title(r'$\textrm{Test de autoconvergencia de } \phi$')
	plt.grid(alpha = 0.5)
	#Descomentar lo siguiente si se quiere guardar la animación:
	plt.savefig('fig4.png', bbox_inches='tight')
	plt.show()  
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

