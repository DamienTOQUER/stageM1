#ifndef POLY_H
#define POLY_H

#include<vector>

using namespace std;

class Poly{
	private:
		vector<double> m_coeff;
	public:
		Poly();
		Poly(vector<double> coeff);
		Poly(const Poly & p);
		void deriv();
		
		double get_coeff(const unsigned int i) const;
		unsigned int get_size() const;
		
		double operator()(double x);
		void operator=(Poly const& p);
		
		friend Poly operator+(Poly const& p1, Poly const& p2);
		friend Poly operator+(Poly const& p1, Poly const& p2);
		friend Poly operator-(Poly const& p1, Poly const& p2);
		friend Poly operator*(Poly const& p1, Poly const& p2);
		friend Poly operator*(Poly const& p1, double a);
		friend Poly operator*(double a, Poly const& p1);
};

#endif
