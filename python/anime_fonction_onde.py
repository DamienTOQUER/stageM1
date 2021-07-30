import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from matplotlib import animation, rc
import math

# création du graphique (cf. tutoriels sur les graphiques)

fig = plt.figure(figsize=(12,10))
plt.xlim(-50,50)
plt.ylim(0,1)
plt.grid()
plt.xlabel("Position")
plt.ylabel("Densité de probabilité")
plt.title("animation : fonction d'onde")


line = plt.plot([0.3],[0],'r+',[], [],'bo-')
line2 = plt.plot([0.3],[0],'r+',[], [],'r')#'ro--')
line3 = plt.plot([0.3],[0],'r+',[], [],'g--')

def init():
	line[1].set_data([], [])
	line2[1].set_data([], [])
	return (line+line2)#+line3)

def animate(j):
	file = open("../Documents/resultat_temp/densite"+str(j*100)+".txt", "r")
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
		if norme[i]==0:
			norme[i] = np.nan
	line[1].set_data(position, norme)
	file = open("../Documents/resultat_temp/densite"+str(j*100+1)+".txt", "r")
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
		if norme[i]==0:
			norme[i] = np.nan
	line2[1].set_data(position, norme)
	"""
	file = open("../Documents/resultat_temp/psi"+str(j*100)+".txt", "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	position = [0]*len(tab)
	norme = [0]*len(tab)
	distrib = [0]*len(tab)
	for i in range(0, len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		position[i] = float(tab[i][0])+30
		norme[i] = float(tab[i][1])/2
		if norme[i]==0:
			norme[i] = np.nan
	line3[1].set_data(position, norme)
	plt.title("animation : fonction d'onde t=" + str(j*100))
	"""
	return (line+line2)#+line3)
"""
file = open("../Documents/resultat_temp/densite"+str(0)+".txt", "r")
tab = file.readlines()
file.close()
tab = tab[1:]
position = [0]*len(tab)
for i in range(0, len(tab)):
	tab[i] = tab[i][0:-1].split(" ")
	position[i] = float(tab[i][0])
x1 = -60
x2 = -20
s1 = 10
s2 = 70
a1=1000
a2=1000
potential = [(a1*math.exp(-(x-x1)**2/2/s1**2)+a2*math.exp(-(x-x2)**2/2/s2**2)-950)/500 for x in position]
"""
#plt.plot(position, potential, color=(0., 0., 0.), linewidth = 3)
anim=animation.FuncAnimation(fig, animate, init_func=init, frames=500, interval=200, blit=False, repeat=True)
#anim.save('test.gif', writer='imagemagick', fps=30)
#f = "./test.gif"
#writergif = animation.PillowWriter(fps=30) 
#anim.save(f, writer=writergif)
plt.show()
plt.close()
