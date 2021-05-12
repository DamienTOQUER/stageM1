#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<string>
#include<cmath>

using namespace std;

#include "const.h"

#include "complex.h"
#include "potential.h"
#include "initial.h"
#include "fourier.h"

void enregistre(list<Complex> & psi, unsigned int i){
	ofstream flux("../resultat/psi"+to_string(i)+".txt");
	list<Complex>::iterator it;
	flux<<"position"<<" "<<"norme"<<" "<<"phase"<<endl;
	double x = Const::min_x;
	for(it = psi.begin(); it!=psi.end(); it++){
		flux<<x<<" "<<(*it).get_norme()<<" "<<(*it).get_phase()<<endl;
		x+=Const::pas_x;
	}
}

double integrate(list<Complex> & psi){
	list<Complex>::iterator it;
	double S = 0;
	for(it = psi.begin(); it!=psi.end(); it++){
		S+=pow((*it).get_norme(),2);
	}
	return S*Const::pas_x;
}

void moment(list<Complex> & psi, unsigned int j){
	if(j==0){
		ofstream flux("../resultat/moment.txt");
		flux<<"Temps"<<" "<<"Norme"<<" "<<"Centre"<<" "<<"Ecart"<<endl;
	}
	else{
		ofstream flux("../resultat/moment.txt", ios::app);
	}
	list<Complex>::iterator it = psi.begin();
	double S0 = 0;
	double S1 = 0;
	double S2 = 0;
	for(unsigned int i=0; i<Const::n_x; i++){
		S0+=pow((*it).get_norme(),2);
		S1+=pow((*it).get_norme(),2)*(Const::min_x + i*Const::pas_x);
		S2+=pow((*it).get_norme(),2)*pow(Const::min_x + i*Const::pas_x,2);
		it++;
	}
	ofstream flux("../resultat/moment.txt", ios::app);
	flux<<j*Const::pas_t<<" "<<S0*Const::pas_x<<" "<<S1*Const::pas_x<<" "<<S2*Const::pas_x<<endl;
}

int main(){
	list<Complex> fx;
	list<Complex> fk;
	Gaussian psi0(0, 2, 0.1);
	PotConst pot(0);
	for(int i=0; i<Const::n_x; i++){
		fx.push_back(psi0(Const::min_x+i*Const::pas_x));
		fk.push_back(Complex(0,0));
	}
	for(int j=0; j<Const::n_t; j++){
		list<Complex>::iterator it = fx.begin();
		for(unsigned int i = 0; i<Const::n_x; i++){
			*it = *it * Complex::cexp(1, -pot(Const::min_x+i*Const::pas_x, 0)*Const::pas_t/2/Const::hbar);
			it++;
		}
		fourier(fx, fk);
		it = fk.begin();
		for(unsigned int i = 0; i<Const::n_x; i++){
			*it = *it * Complex::cexp(1, -pow((i*Const::hbar/2/Const::pas_x),2)*Const::pas_t/2/Const::m*Const::hbar);
			it++;
		}
		ifourier(fk, fx);
		it = fx.begin();
		for(unsigned int i = 0; i<Const::n_x; i++){
			*it = *it * Complex::cexp(1, -pot(Const::min_x+i*Const::pas_x, 0)*Const::pas_t/2/Const::hbar);
			it++;
		}
		cout<<j<<endl;
	}
	enregistre(fx, 2);
	return 0;
}