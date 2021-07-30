#ifndef CONST_H
#define CONST_H

#include <cmath>

namespace Const{
	const double hbar = 197.327050000;//MeV.fm/c
	const double mn = 938.91897;//MeV/c^2
	const double r0 = 1.25;//fm
	const int A = 1;
	const double m = mn*A;//MeV/c^2
	const double R = r0*pow(A, 1./3.);//fm

	const int n_x = 1024; //Puissance de 2 pour fft
	const double min_x = -50.;//fm
	const double max_x = 50.;//fm
	const double pas_x = (max_x-min_x)/(n_x*1.);//fm
	
	const double pas_t = 0.05;//m/M_PI/hbar*pow(pas_x, 2);//fm/c
	const int n_t = 50001;
	
	const int n_pt = 33.;
	const double min_pt = -45.;//fm
	const double max_pt = -25.;//fm
	const double pas_pt = (max_pt-min_pt)/(n_pt*1.-1.);//fm
}

#endif
