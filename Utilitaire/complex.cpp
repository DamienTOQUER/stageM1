#include <iostream>
#include <cmath>

using namespace std;

#include "complex.h"

Complex::Complex():m_re(0),m_im(0){

}
Complex::Complex(double re, double im):m_re(re),m_im(im){
	
}
Complex::Complex(const Complex & z):m_re(z.get_re()),m_im(z.get_im()){
	
}
double Complex::get_re() const{
	return m_re;
}
double Complex::get_im() const{
	return m_im;
}
double Complex::get_norme() const{
	return sqrt(m_re*m_re+m_im*m_im);
}
double Complex::get_phase() const{
	return atan2(m_im, m_re);
}
Complex Complex::get_conjugate() const{
	return Complex(m_re, -m_im);
}
void Complex::set_re(const double re){
	m_re = re;
}
void Complex::set_im(const double im){
	m_im = im;
}
void Complex::affiche() const{
	cout<<m_re<<"+i*"<<m_im<<endl;
}
Complex Complex::cexp(double n, double p){
	return Complex(n*cos(p),n*sin(p));
}
Complex operator+(Complex const& z1, Complex const& z2){
	return Complex(z1.get_re()+z2.get_re(), z1.get_im()+z2.get_im());
}
Complex operator+(Complex const& z, double a){
	return Complex(z.get_re()+a, z.get_im());
}
Complex operator+(double a, Complex const& z){
	return Complex(z.get_re()+a, z.get_im());
}
Complex operator-(Complex const& z){
	return Complex(-z.get_re(), -z.get_im());
}
Complex operator-(Complex const& z1, Complex const& z2){
	return Complex(z1.get_re()-z2.get_re(), z1.get_im()-z2.get_im());
}
Complex operator-(Complex const& z, double a){
	return Complex(z.get_re()-a, z.get_im());
}
Complex operator-(double a, Complex const& z){
	return Complex(a-z.get_re(), -z.get_im());
}
Complex operator*(Complex const& z1, Complex const& z2){
	double a = z1.get_re();
	double b = z1.get_im();
	double c = z2.get_re();
	double d = z2.get_im();
	return Complex(a*c-b*d,a*d+b*c);
}
Complex operator*(Complex const& z, double a){
	return Complex(z.get_re()*a, z.get_im()*a);
}
Complex operator*(double a, Complex const& z){
	return Complex(a*z.get_re(), a*z.get_im());
}
Complex operator/(Complex const& z1, Complex const& z2){
	return z1*z2.get_conjugate()*(1/z2.get_norme()/z2.get_norme());
}
Complex operator/(Complex const& z, double a){
	return Complex(z.get_re()/a, z.get_im()/a);
}
Complex operator/(double a, Complex const& z){
	return a*z.get_conjugate()*(1/z.get_norme()/z.get_norme());
}
