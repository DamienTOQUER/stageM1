#ifndef CONST_H
#define CONST_H

#include <cmath>

namespace Const{
	//Constante physique
	extern const double hbar;//MeV.fm/c
	extern const double mn;//MeV/c^2
	extern const double r0;//fm
	extern const int A;
	extern const double m;//MeV/c^2
	//const double R = r0*pow(A, 1./3.);//fm
	extern const double tau;//fm/c correspond à la constante du temps apparaissant dans les forces de frottements


	//Espace
	extern const int n_x;
	extern const double min_x;
	extern const double max_x;
	extern const double pas_x;
	
	extern const double eta;
	extern const double epsilon;//Pour les dérivations
	
	extern const int n_pt;
	
	//Temps
	extern const double pas_t;//fm/c
	extern const int n_t;	
}

#endif
