#include <cmath>
#include <list>
#include <iostream>

using namespace std;

#include "complex.h"
#include "fourier.h"

void fourier(list<Complex> & fx, list<Complex> & fk){
	int k = 0;
	int x;
	for(list<Complex>::iterator itk = fk.begin(); itk!=fk.end(); itk++){
		*itk = Complex(0,0);
		x=0;
		for(list<Complex>::iterator itx = fx.begin(); itx!=fx.end(); itx++){
			*itk = *itk + *itx * Complex::cexp(1, -2*M_PI*x*k/fx.size());
			x++;
		}
		k++;
	}
}

void ifourier(list<Complex> & fk, list<Complex> & fx){
	int x = 0;
	int k;
	for(list<Complex>::iterator itx = fx.begin(); itx!=fx.end(); itx++){
		*itx = Complex(0,0);
		k=0;
		for(list<Complex>::iterator itk = fk.begin(); itk!=fk.end(); itk++){
			*itx = *itx + *itk * Complex::cexp(1, 2*M_PI*x*k/fk.size());
			k++;
		}
		x++;
	}
}
