#ifndef CONST_H
#define CONST_H

#include <cmath>

namespace Const{
	//Constante physique
	const double hbar = 197.327050000;//MeV.fm/c
	const double mn = 938.91897;//MeV/c^2
	const double r0 = 1.25;//fm
	const int A = 1;
	const double m = mn*A;//MeV/c^2
	//const double R = r0*pow(A, 1./3.);//fm


	//Espace
	const int n_x = 1024; //Puissance de 2 pour fft
	const double min_x = -50.;//fm
	const double max_x = 50.;//fm
	const double pas_x = (max_x-min_x)/(n_x*1.);//fm
	
	//Temps
	const double pas_t = 0.005;//fm/c
	const int n_t = 50001;
	
	//Trajectoire
	const int n_pt = 10000.;
	
	//Pour le fit
	const int degH = 5;
	const int deg = 3;
	const int degfit = 3;
	const int n_loc = 10;//Nombre de points à prendre en compte de chaque coté pour le fit local (ou la convolution) (sans prendre en compte le point local). On doit avoir 2*n_loc+1>deg. 
	const int n_locfit = 3;
	
	const double sigherH = 15.*pas_x;//Sigma de la convolution
	const double sigher = 3.;
	//const double mu = 1.;
	//const double alpha = 0.1;//Paramètre pour le calcul du fit local
	//const double epsilon = 0.001;//Paramètre pour le calcul du fit local
	
	//Pour les particules tests
	const int n_test = 100.;
	
}

#endif
