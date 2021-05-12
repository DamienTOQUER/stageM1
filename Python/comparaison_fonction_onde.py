from matplotlib.pyplot import *
from math import *


matplotlib.rcParams.update({'font.size': 22})
for nb in [0, 5, 9]:
	t=nb/10
	file = open("Documents/resultat/psi"+str(nb*1000)+".txt", "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	position = [0]*len(tab)
	norme = [0]*len(tab)
	phase = [0]*len(tab)
	distrib = [0]*len(tab)
	theorie = [0]*len(tab)

	x0 = 0
	p0 = 4
	s0 = 0.2
	m=1
	hbar=1
	pi=3.14159

	st2 = s0**2*(1+hbar**2*t**2/4/m**2/s0**4)
	xt = x0+t*p0/m

	for i in range(0, len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		position[i] = float(tab[i][0])
		norme[i] = float(tab[i][1])
		phase[i] = float(tab[i][2])
		distrib[i] = norme[i]**2
		x = position[i]
		theorie[i] = (1/2/pi/st2)**(0.5)*exp(-(x-xt)**2/(2*st2))
	plot(position, distrib, '-', label="état à t="+str(t), c=(1, 0, 0))
	plot(position, theorie, '--', label="theorie à t="+str(t), c=(0, 0, 1))
xlabel("position")
ylabel("densité de probabilité")
legend()
show()
