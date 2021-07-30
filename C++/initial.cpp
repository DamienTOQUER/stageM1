#include <cmath>
#include <iostream>
#include<cstdlib>

using namespace std;

#include "const.h"
#include "complex.h"
#include "initial.h"

Initial::~Initial(){

}
Gaussian::~Gaussian(){

}

Gaussian::Gaussian(const double x0, const double p0, const double s0):m_x0(x0),m_p0(p0),m_s0(s0){
	
}
Complex Gaussian::operator()(const double x){
	return Complex::cexp(pow(2.*M_PI*m_s0*m_s0, -0.25)*exp(-pow(x-m_x0,2)/(4.*m_s0*m_s0)), m_p0*(x-m_x0)/Const::hbar);
}
double Gaussian::tirage(){
	double rhomax = pow(2*M_PI*m_s0, -0.5);
	double x=0;
	double y=0;
	do{
		x = Const::min_x+100*drand48();
		y = drand48()*rhomax;
	}while(y>rhomax*exp(-pow(x-m_x0, 2)/2./m_s0/m_s0));
	return x;
}

DGaussian::~DGaussian(){

}

DGaussian::DGaussian(const double x0, const double s0):m_x0(x0),m_s0(s0){
	
}
Complex DGaussian::operator()(const double x){
	return Complex(pow(2.*M_PI*m_s0*m_s0, -0.25)*(exp(-pow(x-m_x0,2)/(4.*m_s0*m_s0))+exp(-pow(x+m_x0,2)/(4.*m_s0*m_s0))), 0);
}
double DGaussian::tirage(){
	double rhomax = pow(2*M_PI*m_s0, -0.5);
	double x=0;
	double y=0;
	do{
		x = Const::min_x+100*drand48();
		y = drand48()*rhomax;
	}while(y>pow(pow(2.*M_PI*m_s0*m_s0, -0.25)*(exp(-pow(x-m_x0,2)/(4.*m_s0*m_s0))+exp(-pow(x+m_x0,2)/(4.*m_s0*m_s0))), 2));
	return x;
}
