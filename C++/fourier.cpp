#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "const.h"
#include "complex.h"
#include "fourier.h"

void fourier(list<Complex> & fx, list<Complex> & fk){
	int k = 0;
	int x;
	double v_x;
	double v_p;
	for(list<Complex>::iterator itk = fk.begin(); itk!=fk.end(); itk++){
		*itk = Complex(0,0);
		x=0;
		v_p = (k-Const::n_x/2.)*2*M_PI*Const::hbar/Const::n_x/Const::pas_x;
		for(list<Complex>::iterator itx = fx.begin(); itx!=fx.end(); itx++){
			v_x = Const::min_x + x*Const::pas_x;
			*itk = *itk + *itx * Complex::cexp(1./sqrt(fx.size()), -v_x*v_p/Const::hbar);
			x++;
		}
		k++;
	}
}

void ifourier(list<Complex> & fk, list<Complex> & fx){
	int x = 0;
	int k;
	double v_x;
	double v_p;
	for(list<Complex>::iterator itx = fx.begin(); itx!=fx.end(); itx++){
		*itx = Complex(0,0);
		k=0;
		v_x = Const::min_x + x*Const::pas_x;
		for(list<Complex>::iterator itk = fk.begin(); itk!=fk.end(); itk++){
			v_p = (k-Const::n_x/2.)*2*M_PI*Const::hbar/Const::n_x/Const::pas_x;
			*itx = *itx + *itk * Complex::cexp(1./sqrt(fx.size()), v_x*v_p/Const::hbar);
			k++;
		}
		x++;
	}
}

void rec_fft(vector<Complex> & fx, vector<Complex> & fk, double N, unsigned int i0, unsigned int pas){
	Complex fact = Complex(0, 0);
	if(N==1){
		fk[0] = fx[i0];
		/*
		cout<<endl;
		cout<<1<<endl;
		cout<<i0<<endl;
		cout<<0<<endl;
		fk[0].affiche();
		cout<<endl;
		*/
	}
	else{
		vector<Complex> fk1(N/2, Complex(0, 0));
		vector<Complex> fk2(N/2, Complex(0, 0));
		rec_fft(fx, fk1, N/2, i0, 2*pas);
		rec_fft(fx, fk2, N/2, i0+pas, 2*pas);
		for(unsigned int i=0; i<N/2; i++){
			fact = Complex::cexp(1., -(i*1.)*2.*M_PI/(N*1.));
			fk[i] = fk1[i]+fact*fk2[i];
			fk[i+N/2] = fk1[i]-fact*fk2[i];
			/*
			cout<<endl;
			cout<<N<<endl;
			cout<<i0<<endl;
			cout<<i<<endl;
			fk[i].affiche();
			cout<<endl;
			cout<<endl;
			cout<<N<<endl;
			cout<<i0<<endl;
			cout<<i+N/2<<endl;
			fk[i+N/2].affiche();
			cout<<endl;
			*/
		}
	}
}

void rec_ifft(vector<Complex> & fk, vector<Complex> & fx, double N, unsigned int i0, unsigned int pas){
	Complex fact = Complex(0, 0);
	if(N==1){
		fx[0] = fk[i0];
		/*
		cout<<endl;
		cout<<1<<endl;
		cout<<i0<<endl;
		cout<<0<<endl;
		fk[0].affiche();
		cout<<endl;
		*/
	}
	else{
		vector<Complex> fx1(N/2, Complex(0, 0));
		vector<Complex> fx2(N/2, Complex(0, 0));
		rec_ifft(fk, fx1, N/2, i0, 2*pas);
		rec_ifft(fk, fx2, N/2, i0+pas, 2*pas);
		for(unsigned int i=0; i<N/2; i++){
			fact = Complex::cexp(1., (i*1.)*2.*M_PI/(N*1.));
			fx[i] = fx1[i]+fact*fx2[i];
			fx[i+N/2] = fx1[i]-fact*fx2[i];
			/*
			cout<<endl;
			cout<<N<<endl;
			cout<<i0<<endl;
			cout<<i<<endl;
			fk[i].affiche();
			cout<<endl;
			cout<<endl;
			cout<<N<<endl;
			cout<<i0<<endl;
			cout<<i+N/2<<endl;
			fk[i+N/2].affiche();
			cout<<endl;
			*/
		}
	}
}


void fft(vector<Complex> & fx, vector<Complex> & fk){
	Complex z(0, 0);
	/*for(unsigned int i=0; i<Const::n_x/2; i++){//i=0 -> Centre de la gaussienne
		z = fx[i];
		fx[i] = fx[i+Const::n_x/2];
		fx[i+Const::n_x/2] = z;
	}*/
	rec_fft(fx, fk, fx.size());
	for(unsigned int i=0; i<Const::n_x; i++){
		//fk[i] = fk[i]*Complex::cexp(1/sqrt(Const::n_x*1.), -M_PI*i/Const::n_x);
		fk[i] = fk[i]*Complex::cexp(1./sqrt(Const::n_x*1.), -M_PI*(i*1.-Const::n_x/2.));
	}
	
	for(unsigned int i=0; i<Const::n_x/2; i++){
		z = fk[i];
		fk[i] = fk[i+Const::n_x/2];
		fk[i+Const::n_x/2] = z;
	}
	
	/*for(unsigned int i=0; i<Const::n_x; i++){
		fk[i] = fk[i]*Complex(1./sqrt(Const::n_x*1.), 0);
	}*/
}

void ifft(vector<Complex> & fk, vector<Complex> & fx){
	Complex z(0, 0);
	rec_ifft(fk, fx, fk.size());
	for(unsigned int i=0; i<Const::n_x; i++){
		fx[i] = fx[i]*Complex::cexp(1./sqrt(Const::n_x*1.), M_PI*(i*1.-Const::n_x/2.));
	}
	for(unsigned int i=0; i<Const::n_x/2; i++){
		z = fx[i];
		fx[i] = fx[i+Const::n_x/2];
		fx[i+Const::n_x/2] = z;
	}
}

bool cmp(const Complex &a, const Complex &b){
	return a.get_norme()<b.get_norme();
}

void fft(vector<double> & fx, vector<Complex> & fk){
	vector<Complex> fix(fx.size(), Complex(0, 0));
	for(unsigned int i=0; i<fx.size(); i++){
		fix[i] = Complex(fx[i], 0);
	}
	fft(fix, fk);
}

void ifft(vector<Complex> & fk, vector<double> & fx){
	vector<Complex> fix(fx.size(), Complex(0, 0));
	ifft(fk, fix);
	for(unsigned int i=0; i<Const::n_x; i++){
		fx[i] = (fix[i]).get_re();
	}
}

void filtre(vector<Complex> & fk, double pt){
	for(unsigned int i=0; i<fk.size(); i++){
		if((fk[i]).get_norme()<(*max_element(fk.begin(), fk.end(), cmp)).get_norme()*pt){
			fk[i]=Complex(0, 0);
		}	
	}
}
