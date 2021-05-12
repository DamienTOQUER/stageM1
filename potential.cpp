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

PotOH::~PotOH(){

}
PotOH::PotOH(double pulsation):m_pulsation(pulsation){

}
double PotOH::operator()(double x, double t){
	return 0.5*Const::m*m_pulsation*m_pulsation*x*x;
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
