import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits import mplot3d


datos=np.loadtxt("45.txt")
dat=np.loadtxt("angulo.txt")


x=datos[:,0]
y=datos[:,1]


i=0


while(i<13):

    x_i = dat[i,dat[i,:]!=-1]
    y_i = dat[(i+1),dat[(i+1),:]!=-1] 
    i=i+2
    
    plt.plot(x_i,y_i)
    
    
plt.title("Con varios angulos")    
plt.ylabel("y [m]")    
plt.xlabel("x [m]")    
plt.show()




plt.plot(x,y)
plt.title("Con angulo de 45 grados")    
plt.ylabel("y [m]")    
plt.xlabel("x [m]") 
plt.show()



x_2 = np.linspace(0, 50, 50)
y_2 = np.linspace(0, 50, 50)

X, Y = np.meshgrid(x_2, y_2)
Z = np.loadtxt("final.txt")

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.plot_surface(X, Y, Z, rstride=1, cstride=1,cmap='viridis', edgecolor='none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('TEMPERATURA t=10s')
ax.view_init(60, 35)
fig



