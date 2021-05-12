#ifndef CONST_H
#define CONST_H

namespace Const{
	const double hbar = 1;
	const double m = 1;

	const int n_x = 500;
	const double min_x = -10;
	const double max_x = 10;
	const double pas_x = (max_x-min_x)/(n_x-1);
	
	const double pas_t = 0.0001;
	const int n_t = 1000;
}

#endif
