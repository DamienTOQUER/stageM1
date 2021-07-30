#include<vector>
#include<cmath>

using namespace std;

#include "poly.h"


Poly::Poly(){
	m_coeff.push_back(0.);
}

Poly::Poly(vector<double> coeff){
	for(unsigned int i=0; i<coeff.size(); i++){
		m_coeff.push_back(coeff[i]);
	}
}

Poly::Poly(const Poly & p){
	for(unsigned int i=0; i<p.get_size(); i++){
		m_coeff.push_back(p.get_coeff(i));
	}
}

void Poly::deriv(){
	for(unsigned int i=0; i<m_coeff.size()-1; i++){
		m_coeff[i] = (i+1)*m_coeff[i+1];
	}
	m_coeff.pop_back();
}

double Poly::get_coeff(const unsigned int i) const{
	if(i<m_coeff.size()){
		return m_coeff[i];
	}
	else{
		return 0;
	}
}

unsigned int Poly::get_size() const{
	return m_coeff.size();
}

double Poly::operator()(double x){
	double s = 0;
	for(unsigned int i=0; i<m_coeff.size(); i++){
		s+=m_coeff[i]*pow(x, i);
	}
	return s;
}

void Poly::operator=(Poly const& p){
	m_coeff.clear();
	for(unsigned int i=0; i<p.get_size(); i++){
		m_coeff.push_back(p.get_coeff(i));
	}
}

Poly operator+(Poly const& p1, Poly const& p2){
	vector<double> p(max(p1.get_size(), p2.get_size()), 0);
	for(unsigned int i=0; i<p.size(); i++){
		p[i] = p1.get_coeff(i)+p2.get_coeff(i);
	}
	return Poly(p);
}

Poly operator-(Poly const& p1, Poly const& p2){
	vector<double> p(max(p1.get_size(), p2.get_size()), 0);
	for(unsigned int i=0; i<p.size(); i++){
		p[i] = p1.get_coeff(i)-p2.get_coeff(i);
	}
	return Poly(p);
}

Poly operator*(Poly const& p1, Poly const& p2){
	vector<double> p(p1.get_size()+p2.get_size()-1, 0);
	for(unsigned int i=0; i<p.size(); i++){
		p[i] = 0;
		for(unsigned int j=0; j<=i; j++){
			p[i] += p1.get_coeff(j)*p2.get_coeff(i-j);
		}
	}
	return Poly(p);
}

Poly operator*(Poly const& p1, double a){
	vector<double> p(p1.get_size(), 0);
	for(unsigned int i=0; i<p.size(); i++){
		p[i] = p1.get_coeff(i)*a;
	}
	return Poly(p);
}

Poly operator*(double a, Poly const& p1){
	vector<double> p(p1.get_size(), 0);
	for(unsigned int i=0; i<p.size(); i++){
		p[i] = p1.get_coeff(i)*a;
	}
	return Poly(p);
}
