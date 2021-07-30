#ifndef SAVE_H
#define SAVE_H

#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#include "const.h"
#include "complex.h"
#include "potential.h"

void save2D_discret(vector<double> & y, unsigned int t);
void save2D_discret(vector<Complex> & y, unsigned int t);
void save2D(vector<double> & x, vector<double> & y, unsigned int t);
void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int n_traj, unsigned int t);
void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int t);
void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int t, string name);
void moment(vector<double> & x, unsigned int j);
void saveVeff(Potential* pot, vector<double> & param, unsigned int j);
void savet(double ft, unsigned int t);


#endif
