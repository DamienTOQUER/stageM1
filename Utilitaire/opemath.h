#ifndef OPEMATH_H
#define OPEMATH_H
//Quelques funconctions mathématique sur des vecteurs discrets

#include<vector>
#include<cmath>

using namespace std;


#include "const.h"

double gradient1D(vector<double> & func, unsigned int i);
double laplacien1D(vector<double> & func, unsigned int i);

double interpolationl1D(double x1, double x2, double f1, double f2, double x);
bool interpolation_hermite(vector<double> & x, vector<double> & Q, unsigned int imin, unsigned int imax, vector<double> & param, unsigned int loc);
bool interpolation_hermite(vector<double> & x, vector<double> & Q, unsigned int imax, vector<double> & param, unsigned int loc1, unsigned int loc2);
bool interpolation_hermite(vector<double> & x, vector<double> & Q, vector<int> & is, vector<double> & param);

double approx_poly(vector<double> & x, vector<double> & f, vector<double> & param);
double approx_poly(vector<double> & xb, vector<double> & g, vector<double> & param, vector<double> & weight);

void approx_monome(double x1, double x2, double x3, double Q1, double Q2, double Q3, int N, vector<double> & param, vector<vector<int>> & bin);//Interpole x1, x2, x3 ou x2 est un extrema de Q et x1, x3 des points d'inflexion de Q, par un polynome de degrès N.
void approx_monome2(double x1, double x2, double Q1, double Qp1, double Qp2, int N, vector<double> & param, vector<vector<int>> & bin);
void approx_monome3(double x1, double x2, double Q1, double Q2, int N, vector<double> & param, vector<vector<int>> & bin, bool ispos = false);

double calc_chi2(vector<double> & xb, vector<double> & g, vector<double> & param);
double calc_gradchi2(vector<double> & xb, vector<double> & g, vector<double> & param, unsigned int j);

int factorial(int k);
void binom(int Nmax, vector<vector<int>> & bin);

void lagrange(vector<double> x, unsigned int i, vector<double> & param);

#endif
