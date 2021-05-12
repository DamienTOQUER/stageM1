#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{
	private:
		double m_re;
		double m_im;
	public:
		Complex();
		Complex(double re, double im);
		Complex(const Complex & z);
		double get_re() const;
		double get_im() const;
		double get_norme() const;
		double get_phase() const;
		Complex get_conjugate() const;
		void set_re(const double re);
		void set_im(const double im);
		static Complex cexp(double n, double p);
		
		void affiche() const;
		
		friend Complex operator+(Complex const& z1, Complex const& z2);
		friend Complex operator+(Complex const& z, double a);
		friend Complex operator+(double a, Complex const& z);
		friend Complex operator-(Complex const& z);
		friend Complex operator-(Complex const& z1, Complex const& z2);
		friend Complex operator-(Complex const& z, double a);
		friend Complex operator-(double a, Complex const& z);
		friend Complex operator*(Complex const& z1, Complex const& z2);
		friend Complex operator*(Complex const& z, double a);
		friend Complex operator*(double a, Complex const& z);
		friend Complex operator/(Complex const& z1, Complex const& z2);
		friend Complex operator/(double a, Complex const& z);
		friend Complex operator/(Complex const& z1, Complex const& z2);
};

#endif
