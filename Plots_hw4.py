import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits import mplot3d

def funcion(a,b,m):
    M=np.zeros((50,50))
    k=0
    for i in range(a,b):
        
        for j in range(50):
            
            M[k,j]=m[i,j]
        
        k=k+1
    return M







datos=np.loadtxt("45.txt")
dat=np.loadtxt("angulo.txt")
promedio=np.loadtxt("Temperatura_promedio.txt")
tiempo=np.linspace(0.0,0.8,23331)

temp_inicial = np.loadtxt("Temperatura_inicial.txt")
fijas=np.loadtxt("Fronteras_fijas.txt")
abiertas=np.loadtxt("Fronteras_abiertas.txt")
periodicas=np.loadtxt("Fronteras_periodicas.txt")

g=np.loadtxt("Graficas.txt")

lado_x= np.linspace(0, 50, 50)
lado_y = np.linspace(0, 50, 50)

X, Y = np.meshgrid(lado_x, lado_y)

x=datos[:,0]
y=datos[:,1]


i=0

plt.figure()
while(i<13):

    x_i = dat[i,dat[i,:]!=-1]
    y_i = dat[(i+1),dat[(i+1),:]!=-1] 
    i=i+2
    
    plt.plot(x_i,y_i)
    
    
plt.title("Trayectoria del proyectil con varios angulos")    
plt.ylabel("y [m]")    
plt.xlabel("x [m]")  
plt.savefig("Angulos.jpg")



plt.figure()
plt.plot(x,y)
plt.title("Trayectoria con angulo de 45 grados")    
plt.ylabel("y [m]")    
plt.xlabel("x [m]") 
plt.savefig("45.jpg")




#PARTE PARA GRAFICAR LA TEMPERATURA

m1=funcion(0,50,g)
m2=funcion(50,100,g)
m3=funcion(100,150,g)
m4=funcion(150,200,g)
m5=funcion(200,250,g)
m6=funcion(250,300,g)


plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m1 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)
ax.set_title('Primera evolucion fronteras fijas')
plt.savefig("1_fijas.jpg")




plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m2 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)

ax.set_title('Segunda evolucion fronteras fijas')
plt.savefig("2_fijas.jpg")



plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m3 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)
ax.set_title('Primera evolucion fronteras abiertas')
plt.savefig("1_abiertas.jpg")


plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m4 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)
ax.set_title('Segunda evolucion fronteras abiertas')
plt.savefig("2_abiertas.jpg")



plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m5 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)
ax.set_title('Primera evolucion fronteras periodicas')
plt.savefig("1_periodicas.jpg")


plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, m6 , rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('Temperatura [K]')
ax.set_zlim3d(283.15,373.15)
ax.set_title('Segunda evolucion fronteras periodicas')
plt.savefig("2_periodicas.jpg")






plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, temp_inicial, rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('Momento inicial')
plt.savefig("Momento_inicial.jpg")



plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, fijas, rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('FRONTERAS FIJAS')
plt.savefig("Fronteras_fijas.jpg")



plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, abiertas, rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('FRONTERAS ABIERTAS')
plt.savefig("Fronteras_abiertas.jpg")



plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, periodicas, rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('FRONTERAS PERIODICAS')
plt.savefig("Fronteras_periodicas.jpg")





for i in range(3):
    pro=promedio[i,:]
    
    plt.plot(tiempo,pro)
    
plt.xlabel("Tiempo")  
plt.ylabel("Temperatura")
plt.title("Temperatura promedio")
plt.savefig("Temperatura_promedio.jpg")



