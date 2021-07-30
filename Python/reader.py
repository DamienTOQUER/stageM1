"""
Ensemble de fonction permettant de lire des fichiers de données.
	-> readpsi : Renvoit l'abscisse, l'observable et le temps
	-> multreadpsi : Identique à readpsi mais pour plusieurs fichiers différent
	-> readmoment : Renvoit le temps, la position du centre de masse et l'écart type de la gaussienne.
	-> read2D : Lecture simple d'un document à 2 collones

"""

import math as math

folder = "./resultat_temp/"

def readpsi(filename, observable="distribution"):
	file = open(folder+filename, "r")
	tab = file.readlines()
	file.close()
	t = float(tab[0].split(" ")[0][2:])
	tab = tab[1:]
	x=[0]*len(tab)
	y=[0]*len(tab)
	for i in range(len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		x[i] = float(tab[i][0])
		if(observable=="distribution"):
			y[i] = float(tab[i][1])**2
		elif(observable=="norme"):
			y[i] = float(tab[i][1])
		elif(observable=="phase"):
			y[i] = float(tab[i][2])
		elif(observable=="re"):
			y[i] = float(tab[i][1])*math.cos(float(tab[i][2]))
		elif(observable=="im"):
			y[i] = float(tab[i][1])*sin.cos(float(tab[i][2]))
	return x,y,t
	
def multreadpsi(nameb, namee, i0, ni, di, observable="distribution"):
	x = []
	y = [[]]*ni
	t = [0]*ni
	
	for i in range(ni):
		x,y[i],t[i] = readpsi(nameb+str(i0+i*di)+namee, observable)
	return x,y,t
			
def readmoment(filename):
	file = open(folder+filename, "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	t=[0]*len(tab)
	x=[0]*len(tab)
	s=[0]*len(tab)
	for i in range(len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		t[i] = float(tab[i][0])
		x[i] = float(tab[i][2])
		s[i] = float(tab[i][3])
	return t,x,s
	
def read2D(filename, col = 1):
	file = open(folder+filename, "r")
	tab = file.readlines()
	file.close()
	tab = tab[1:]
	x=[0]*len(tab)
	y=[0]*len(tab)
	for i in range(len(tab)):
		tab[i] = tab[i][0:-1].split(" ")
		x[i] = float(tab[i][0])
		y[i] = float(tab[i][col])
	return x,y
	
def multreadact(nameb, namee, i0, ni, di):
	x = []
	y = [[]]*ni
	
	for i in range(ni):
		x,y[i] = read2D(nameb+str(i0+i*di)+namee)
	return x,y
	
def readtraj(nameb, namee, i0, ni, di, ntraj, observable="position"):
	t=[0]*ni
	x=[[0 for i in range(ni)] for j in range(ntraj)]
	for i in range(ni): 
		file = open(folder+nameb+str(i0+i*di)+namee, "r")
		#print(folder+nameb+str(i0+i*di)+namee)
		tab = file.readlines()
		file.close()
		#print(tab[0].split(" "))
		t[i] = float(tab[0].split(" ")[0][2:])
		tab=tab[1:]
		for j in range(ntraj):
			tab[j] = tab[j].split(" ");
			if observable=="position":
				x[j][i] = float(tab[j][0])
			elif observable=="vitesse":
				if float(tab[j][0])<35:
					x[j][i] = float(tab[j][1])
				else:
					x[j][i] = math.nan
				#x[j][i] = float(tab[j][1])
			elif observable=="potentiel":
				if float(tab[j][0])<35:
					x[j][i] = float(tab[j][2])
				else:
					x[j][i] = math.nan
				#x[j][i] = float(tab[j][2])
			elif observable=="energie":
				if float(tab[j][0])<35:
					x[j][i] = float(tab[j][2])+1/2.*938.91897*float(tab[j][1])**2
				else:
					x[j][i] = math.nan
				#x[j][i] = float(tab[j][2])+1./2.*938.91897*float(tab[j][1])**2
	return t,x

def readsometraj(nameb, namee, i0, ni, di, i0t, ntraj, dt, observable="position"):
	nt = int((ntraj-i0t-1)/dt)
	t=[0]*ni
	x=[[0 for i in range(ni)] for j in range(nt+1)]
	for i in range(ni): 
		file = open(folder+nameb+str(i0+i*di)+namee, "r")
		#print(folder+nameb+str(i0+i*di)+namee)
		tab = file.readlines()
		file.close()
		#print(tab[0].split(" "))
		t[i] = float(tab[0].split(" ")[0][2:])
		tab=tab[1:]
		if(len(tab)>=ntraj):
			for j in range(ntraj):
				tab[j] = tab[j].split(" ");
				if j-i0t>=0 and (j-i0t)%dt == 0:
					if observable=="position":
						x[(j-i0t)//dt][i] = float(tab[j][0])
					elif observable=="vitesse":
						if float(tab[j][0])<35:
							x[(j-i0t)//dt][i] = float(tab[j][1])
						else:
							x[(j-i0t)//dt][i] = math.nan
						#x[j][i] = float(tab[j][1])
					elif observable=="potentiel":
						if float(tab[j][0])<35:
							x[(j-i0t)//dt][i] = float(tab[j][2])
						else:
							x[(j-i0t)//dt][i] = math.nan
						#x[j][i] = float(tab[j][2])
					elif observable=="energie":
						if float(tab[j][0])<35:
							x[(j-i0t)//dt][i] = float(tab[j][2])+1/2.*938.91897*float(tab[j][1])**2
						else:
							x[(j-i0t)//dt][i] = math.nan
						#x[j][i] = float(tab[j][2])+1./2.*938.91897*float(tab[j][1])**2
		else:
			print(len(tab))
			print(ntraj)
	return t,x

def read3D(filename):
	file = open(folder+filename, "r")
	tab = file.readlines()
	file.close()
	tab = [tab[i].split() for i in range(len(tab))]
	return [[float(tab[j][i]) for j in range(len(tab))] for i in range(len(tab[0]))]
		
def read3Dlog(filename):
	file = open(folder+filename, "r")
	tab = file.readlines()
	file.close()
	tab = [tab[i].split() for i in range(len(tab))]
	return [[math.log(abs(float(tab[j][i]))) for j in range(len(tab))] for i in range(len(tab[0]))]

