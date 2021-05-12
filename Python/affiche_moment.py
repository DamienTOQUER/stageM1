from matplotlib.pyplot import *

matplotlib.rcParams.update({'font.size': 22})

file = open("Documents/resultat/moment.txt", "r")
tab0 = file.readlines()
tab0 = tab0[1:]
file.close()
t = [0]*len(tab0)
m0 = [0]*len(tab0)
m1 = [0]*len(tab0)
m2 = [0]*len(tab0)
for i in range(0, len(tab0)):
	tab0[i] = tab0[i][0:-1].split(" ")
	t[i] = float(tab0[i][0])
	m0[i] = float(tab0[i][1])
	m1[i] = float(tab0[i][2])
	m2[i] = float(tab0[i][3])
plot(t, m0, label="Norme")
plot(t, m1, label="Position du centre")
plot(t, m2, label="Extension spatiale")
xlabel("temps")
legend()
show()
