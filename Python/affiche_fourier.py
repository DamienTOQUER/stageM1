from matplotlib.pyplot import *
from math import *

matplotlib.rcParams.update({'font.size': 30})
matplotlib.rcParams.update({'legend.loc' : 'upper right'})
matplotlib.rcParams.update({'text.usetex' : True})

file = open("Documents/resultat/psi"+str(2)+".txt", "r")
tab = file.readlines()
file.close()
tab = tab[1:]
position = [0]*len(tab)
norme = [0]*len(tab)
phase = [0]*len(tab)
distrib = [0]*len(tab)
re = [0]*len(tab)
for i in range(0, len(tab)):
	tab[i] = tab[i][0:-1].split(" ")
	position[i] = float(tab[i][0])
	norme[i] = float(tab[i][1])
	phase[i] = float(tab[i][2])
	distrib[i] = norme[i]**2
	re[i] = norme[i]*cos(phase[i])
plot(position, norme)
xlabel("$position$")
ylabel("densité de probabilité")
legend()
show()
