from matplotlib.pyplot import *

matplotlib.rcParams.update({'font.size': 30})
matplotlib.rcParams.update({'legend.loc' : 'upper right'})
matplotlib.rcParams.update({'text.usetex' : True})

norme = [0]*10
phase = [0]*10
distrib = [0]*10

for j in range(0, 10):
	file = open("Documents/resultat/psi"+str(j*1000)+".txt", "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	if j==0:
		position = [0]*len(tab)
	norme[j] = [0]*len(tab)
	phase[j] = [0]*len(tab)
	distrib[j] = [0]*len(tab)
	for i in range(0, len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		if j==0:
			position[i] = float(tab[i][0])
		norme[j][i] = float(tab[i][1])
		phase[j][i] = float(tab[i][2])
		distrib[j][i] = norme[j][i]**2
	plot(position, distrib[j], label="état à t="+str((j/10)), c = (0.3, j/10, 1-j/10))
potential = [0]*len(position)
for i in range(len(position)):
	#if position[i]<0:
	#	potential[i] = 0;
	#else:
	#	potential[i] = position[i]*0.1
	if position[i]<-0.5 or position[i]>0.5:
		potential[i]=0;
	else:
		potential[i]=1;
plot(position, potential, c=(0, 0, 0))
xlabel("position")
ylabel("densité de probabilité")
legend()
show()
