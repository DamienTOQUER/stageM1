#ifndef FOURIER_H
#define FOURIER_H

#include <list>

using namespace std;

#include "complex.h"

void fourier(list<Complex> & fx, list<Complex> & fk);
void ifourier(list<Complex> & fk, list<Complex> & fx);

#endif
