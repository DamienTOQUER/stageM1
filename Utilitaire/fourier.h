#ifndef FOURIER_H
#define FOURIER_H

#include <list>
#include <vector>

using namespace std;

#include "complex.h"

void fourier(list<Complex> & fx, list<Complex> & fk);
void ifourier(list<Complex> & fk, list<Complex> & fx);

void rec_fft(vector<Complex> & fx, vector<Complex> & fk, double N, unsigned int i0=0, unsigned int pas=1);//Programme récursif qui calcule la fft.
void rec_ifft(vector<Complex> & fk, vector<Complex> & fx, double N, unsigned int i0=0, unsigned int pas=1);//Programme récursif qui calcule la fft.

void fft(vector<Complex> & fx, vector<Complex> & fk);//Préprogramme qui lance la récursion, normalise puis recentre.
void ifft(vector<Complex> & fk, vector<Complex> & fx);//Préprogramme qui lance la récursion, normalise puis recentre.

void fft(vector<double> & fx, vector<Complex> & fk);//Préprogramme qui lance la récursion, normalise puis recentre.
void ifft(vector<Complex> & fk, vector<double> & fx);//Préprogramme qui lance la récursion, normalise puis recentre.

void filtre(vector<Complex> & fk, double pt);//

#endif
