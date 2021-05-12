import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation, rc

# création du graphique (cf. tutoriels sur les graphiques)

fig = plt.figure(figsize=(12,10))
plt.xlim(-10,10)
plt.ylim(0, 5)
plt.grid()
plt.xlabel("Position")
plt.ylabel("Densité de probabilité")
plt.title("animation : fonction d'onde")


line = plt.plot([0.3],[0],'r+',[], [],'bo-')

def init():
	line[1].set_data([], [])
	return (line)

def animate(i):
	file = open("Documents/resultat/psi"+str(i*100)+".txt", "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	position = [0]*len(tab)
	norme = [0]*len(tab)
	distrib = [0]*len(tab)
	for i in range(0, len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		position[i] = float(tab[i][0])
		norme[i] = float(tab[i][1])
		distrib[i] = norme[i]**2
	line[1].set_data(position, distrib)
	return (line)

file = open("Documents/resultat/psi"+str(0)+".txt", "r")
tab = file.readlines()
file.close()
tab = tab[1:]
position = [0]*len(tab)
for i in range(0, len(tab)):
	tab[i] = tab[i][0:-1].split(" ")
	position[i] = float(tab[i][0])
potential = [0]*len(position)
for i in range(len(position)):
	#if position[i]<-0.5 or position[i]>0.5:
	#	potential[i]=0;
	#else:
	#	potential[i]=1;
	potential[i] = position[i] ** 2/10
plt.plot(position, potential, c=(0, 0, 0))

anim=animation.FuncAnimation(fig, animate, init_func=init, frames=100, interval=30, blit=True, repeat=True)
#anim.save('Documents/OH.gif', writer='imagemagick', fps=30)
plt.show()
plt.close()
