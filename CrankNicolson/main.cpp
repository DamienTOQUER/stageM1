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

void maffiche(list<Complex> & subdiag, list<Complex> & diag, list<Complex> & supdiag){
	list<Complex>::iterator it;
	cout<<"Subdiag:"<<subdiag.size()<<endl;
	for(it = subdiag.begin(); it!=subdiag.end(); it++){
		it->affiche();
	}
	cout<<"Diag:"<<diag.size()<<endl;
	for(it = diag.begin(); it!=diag.end(); it++){
		it->affiche();
	}
	cout<<"Supdiag:"<<supdiag.size()<<endl;
	for(it = supdiag.begin(); it!=supdiag.end(); it++){
		it->affiche();
	}
}

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
	cout<<"Facteur d'échantillonage dt/dx²="<<Const::pas_t/Const::pas_x/Const::pas_x<<endl;
	//PotConst pot(0);
	//PotOH pot(10);
	//PotRamp pot(0, 100);
	PotWall pot(0, 60, 1);
	Gaussian psi0(0, 8, 0.5);
	Complex alpha = Complex(0,Const::hbar*Const::pas_t/2/Const::m/Const::pas_x/Const::pas_x);
	list<Complex> diag;
	list<Complex> supdiag;
	list<Complex> subdiag;
	diag.push_back(Complex(1,0));
	supdiag.push_back(Complex(0, 0));
	for(unsigned int i=1; i<Const::n_x-1; i++){
		subdiag.push_back(-alpha*0.5);
		diag.push_back(Complex(1, 0.5*pot(Const::min_x+i*Const::pas_x,0)/Const::hbar*Const::pas_t)+alpha);
		//cout<<pot(Const::min_x+i*Const::pas_x,0)<<endl;
		supdiag.push_back(-alpha*0.5);
	}
	diag.push_back(Complex(1, 0));
	subdiag.push_back(Complex(0, 0));
	//maffiche(subdiag, diag, supdiag);
	//for(unsigned int i=0; i<Const::n_x; i++){
	//	psi0(Const::min_x+i*Const::pas_x).affiche();
	//}
	list<Complex> psi;
	for(unsigned int i=0; i<Const::n_x; i++){
		psi.push_back(psi0(Const::min_x+i*Const::pas_x));
	}
	for(unsigned int j=0; j<Const::n_t; j++){
		if(j%100==0){
			enregistre(psi, j);
			cout<<j<<endl;
		}
		if(j%100==0){
			moment(psi, j);
		}
		vector<Complex> cp(Const::n_x-1);
		vector<Complex> dp(Const::n_x);
		list<Complex>::iterator d = psi.begin();
		vector<Complex> psip(Const::n_x); 
		for(unsigned int i=0; i<Const::n_x; i++){
			psip[i] = *d;
			d++;
		}
		d = psi.begin();
		list<Complex>::iterator b = diag.begin();
		list<Complex>::iterator a = subdiag.begin();
		list<Complex>::iterator c = supdiag.begin();
		for(unsigned int i=1; i<Const::n_x-1; i++){
			d++;
			b++;
			c++;
			*d = (*a).get_conjugate()*psip[i-1]+(*c).get_conjugate()*psip[i+1]+(*b).get_conjugate()*psip[i];
			a++;
		}
		b = diag.begin();
		a = subdiag.begin();
		c = supdiag.begin();
		d = psi.begin();
		cp[0] = *c/(*b*1);
		dp[0] = *d/(*b*1);
		for(unsigned int i=1; i<Const::n_x-1; i++){
			if(i!=1){
				a++;
			}
			b++;
			c++;
			d++;
			cp[i] = *c/(*b-*a*cp[i-1]);
			dp[i] = (*d-*a*dp[i-1])/(*b-*a*cp[i-1]);
		}
		a++;
		b++;
		d++;
		dp[Const::n_x-1] = (*d-*a*dp[Const::n_x-2])/(*b-*a*cp[Const::n_x-2]);
		*d = dp[Const::n_x-1];
		for(int i=Const::n_x-2; i>=0 ; i--){
			Complex dpre = *d;
			d--;
			*d = dp[i]-cp[i]*dpre;
		}
	}
	//for(list<Complex>::iterator d = psi.begin(); d!=psi.end(); d++){
	//	(*d).affiche();
	//}
	return 0;
}
