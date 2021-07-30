#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#include "const.h"
#include "save.h"
#include "potential.h"

void save2D_discret(vector<double> & y, unsigned int t){
	ofstream flux("../resultat_temp/densite"+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" "<<"x"<<" "<<"y"<<endl;
	for(unsigned int i=0; i<Const::n_x; i++){
		flux<<1.*Const::min_x+1.*i*Const::pas_x<<" "<<y[i]<<endl;
	}
}

void save2D_discret(vector<Complex> & y, unsigned int t){
	ofstream flux("../resultat_temp/densite"+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" "<<"x"<<" "<<"y"<<endl;
	for(unsigned int i=0; i<Const::n_x; i++){
		flux<<i<<" "<<(y[i]).get_re()<<endl;
	}
}

void save2D(vector<double> & x, vector<double> & y, unsigned int t){
	ofstream flux("../resultat_temp/densite"+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" "<<"x"<<" "<<"y"<<endl;
	for(unsigned int i=0; i<x.size(); i++){
		flux<<x[i]<<" "<<y[i]<<endl;
	}
}

void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int n_traj, unsigned int t){
	int pas = int(Const::n_pt/n_traj);
	ofstream flux("../resultat_temp/traj"+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" position vitesse potentiel"<<endl;
	for(unsigned int i=0; i<x.size(); i+=pas){
		flux<<x[i]<<" "<<v[i]<<" "<<Veff[i]<<endl;
	}
}

void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int t){
	ofstream flux("../resultat_temp/traj"+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" position vitesse potentiel"<<endl;
	for(unsigned int i=0; i<x.size(); i++){
		flux<<x[i]<<" "<<v[i]<<" "<<Veff[i]<<endl;
	}
}

void savetraj(vector<double> & x, vector<double> & v, vector<double> & Veff, unsigned int t, string name){
	ofstream flux("../resultat_temp/"+name+to_string(t)+".txt");
	flux<<"t="<<t*Const::pas_t<<" position vitesse potentiel"<<endl;
	for(unsigned int i=0; i<x.size(); i++){
		flux<<x[i]<<" "<<v[i]<<" "<<Veff[i]<<endl;
	}
}
/*
void moment(vector<double> & R, unsigned int j){
	if(j==0){
		ofstream flux("../resultat_temp/moment.txt");
		flux<<"Temps"<<" "<<"Norme"<<" "<<"Centre"<<" "<<"Ecart"<<endl;
	}
	else{
		ofstream flux("../resultat_temp/moment.txt", ios::app);
	}
	double S0 = 0;
	double S1 = 0;
	double S2 = 0;
	for(unsigned int i=0; i<Const::n_x; i++){
		S0+=R[i];
		S1+=R[i]*(Const::min_x + i*Const::pas_x);
		S2+=R[i]*pow(Const::min_x + i*Const::pas_x,2);
	}
	ofstream flux("../resultat_temp/moment.txt", ios::app);
	flux<<j*Const::pas_t<<" "<<S0<<" "<<S1<<" "<<pow(S2-pow(S1, 2), 0.5)<<endl;
}
*/
void moment(vector<double> & x, unsigned int j){
	if(j==0){
		ofstream flux("../resultat_temp/moment.txt");
		flux<<"Temps"<<" "<<"Norme"<<" "<<"Centre"<<" "<<"Ecart"<<endl;
	}
	else{
		ofstream flux("../resultat_temp/moment.txt", ios::app);
	}
	double S0 = 0;
	double S1 = 0;
	double S2 = 0;
	for(unsigned int i=0; i<Const::n_x; i++){
		S0+=1./Const::n_x;
		S1+=x[i]/Const::n_x;
		S2+=pow(x[i],2)/Const::n_x;
	}
	ofstream flux("../resultat_temp/moment.txt", ios::app);
	flux<<j*Const::pas_t<<" "<<S0<<" "<<S1<<" "<<pow(S2-pow(S1, 2), 0.5)<<endl;
	
}

void saveVeff(Potential* pot, vector<double> & param, unsigned int t){
	if(t==0){
		ofstream flux("../resultat_temp/pot.txt");
	}
	else{
		ofstream flux("../resultat_temp/pot.txt", ios::app);
	}
	ofstream flux("../resultat_temp/pot.txt", ios::app);
	for(unsigned int i=0; i<Const::n_x; i++){
		double b = param[1];
		double c = param[2];
		double d = param[3];
		double e = param[4];
		double x = Const::min_x+i*Const::pas_x;
		flux<<(*pot)(x, 0)-Const::hbar*Const::hbar/2./Const::m*(c-b*b/4.+x*(3.*d-c*b)+pow(x, 2)*(6.*e-c*c-3.*b*d/2.)-pow(x, 3)*(2.*e*b+3.*c*d)-pow(x, 4)*(9./4.*d*d+4.*e*c)-pow(x, 5)*6.*d*e-pow(x, 6)*4.*e*e)<<" ";
	}
	flux<<endl;
}

void savet(double ft, unsigned int j){
	if(j==0){
		ofstream flux("../resultat_temp/t.txt");
		flux<<"Temps"<<" "<<"P(t)"<<endl;
	}
	else{
		ofstream flux("../resultat_temp/t.txt", ios::app);
	}
	ofstream flux("../resultat_temp/t.txt", ios::app);
	flux<<j*Const::pas_t<<" "<<ft<<endl;
}
