#include "potential.h"
#include "const.h"

Potential::~Potential(){

}

PotConst::~PotConst(){

}
PotConst::PotConst(double val):m_val(val){

}
double PotConst::operator()(double x, double t){
	return m_val;
}
double PotConst::deriv(double x, double t){
	return 0;
}

PotOH::~PotOH(){

}
PotOH::PotOH(double pulsation):m_pulsation(pulsation){

}
double PotOH::operator()(double x, double t){
	return 0.5*Const::m*m_pulsation*m_pulsation*x*x;
}
double PotOH::deriv(double x, double t){
	return Const::m*m_pulsation*m_pulsation*x;
}

PotRamp::~PotRamp(){

}
PotRamp::PotRamp(double center, double slope):m_center(center),m_slope(slope){

}
double PotRamp::operator()(double x, double t){
	if(x<m_center){
		return 0;
	}
	else{
		return m_slope*x;
	}
}

PotWall::~PotWall(){

}
PotWall::PotWall(double center, double height, double width):m_center(center),m_height(height),m_width(width){

}
double PotWall::operator()(double x, double t){
	if(x<m_center-m_width/2 || x>m_center+m_width/2){
		return 0;
	}
	else{
		return m_height;
	}
}

PotQuart::~PotQuart(){

}
PotQuart::PotQuart(double a2, double a4):m_a2(a2),m_a4(a4){

}
double PotQuart::operator()(double x, double t){
	return -m_a2*pow(x, 2)+m_a4*pow(x, 4);
}
double PotQuart::deriv(double x, double t){
	return -2*m_a2*x+4*m_a4*pow(x, 3);
}

PotFis::~PotFis(){

}
PotFis::PotFis(double x1, double x2, double s1, double s2, double a1, double a2):m_x1(x1), m_x2(x2), m_s1(s1), m_s2(s2), m_a1(a1), m_a2(a2){
	
}
double PotFis::operator()(double x, double t){
	return m_a1*exp(-pow(x-m_x1,2)/2./m_s1/m_s1)+m_a2*exp(-pow(x-m_x2,2)/2./m_s2/m_s2);
}
double PotFis::deriv(double x, double t){
	return -m_a1/pow(m_s1, 2)*(x-m_x1)*exp(-pow(x-m_x1,2)/2./m_s1/m_s1)-m_a2/pow(m_s2, 2)*(x-m_x2)*exp(-pow(x-m_x2,2)/2./m_s2/m_s2);
}

PotAbs::~PotAbs(){

}
PotAbs::PotAbs(double x, double a):m_x(x), m_a(a){
	
}
double PotAbs::operator()(double x, double t){
	if(x<m_x){
		return 0;
	}
	else{
		return m_a*pow(x-m_x,4.);
	}
}

PotDAbs::~PotDAbs(){

}
PotDAbs::PotDAbs(double x, double a):m_x(x), m_a(a){
	
}
double PotDAbs::operator()(double x, double t){
	if(abs(x)<m_x){
		return 0;
	}
	else{
		return m_a*pow(abs(x)-m_x,2.);
	}
}

PotWS::~PotWS(){

}
PotWS::PotWS(double V0, double a):m_V0(V0), m_a(a){
	
}
double PotWS::operator()(double x, double t){
	double R = Const::r0*pow(Const::A, 1./3.);
	return -m_V0/(1+exp((x-R)/m_a))-m_V0/(1+exp((-x-R)/m_a));
}
double PotWS::deriv(double x, double t){
	double R = Const::r0*pow(Const::A, 1./3.);
	return -m_V0/m_a*(1./((1.+exp((x-R)/m_a))*(1.+exp((R-x)/m_a)))-1./((1.+exp((x+R)/m_a))*(1.+exp((-R-x)/m_a))));
}
