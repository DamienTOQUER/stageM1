#include <cmath>

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
	return Complex::cexp(pow(2*M_PI*m_s0*m_s0, -0.25)*exp(-pow(x-m_x0,2)/(4*m_s0*m_s0)), m_p0*(x-m_x0)/Const::hbar);
}
