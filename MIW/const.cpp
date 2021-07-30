#include <cmath>

#include "const.h"

namespace Const{
	//Constante physique
	const double hbar = 197.327050000;//MeV.fm/c
	const double mn = 938.91897;//MeV/c^2
	const double r0 = 10.;//fm
	const int A = 1;
	const double m = mn*A;//MeV/c^2
	//const double R = r0*pow(A, 1./3.);//fm
	const double tau = 0.1;//fm/c correspond à la constante du temps apparaissant dans les forces de frottements


	//Espace
	const int n_x = 151;
	const double min_x = -50;
	const double max_x = 50;
	const double pas_x = (max_x-min_x)/(n_x*1.);
	
	const double eta = 1.;
	const double epsilon = 0.01;
	
	const int n_pt = n_x;
	
	//Temps
	//const int n_t = pow(2, 18)-2;
	//const double pas_t = 50.*M_PI/(1.*(n_t+2))/(0.05);//fm/c
	const int n_t = 1000001;
	const double pas_t = 0.001;
	//const int n_t = int(40.*M_PI/0.005/pas_t);
	//const double pas_t = 0.02;
}
