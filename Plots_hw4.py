import numpy as np
import matplotlib.pylab as plt

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
