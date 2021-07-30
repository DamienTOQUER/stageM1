#ifndef INITIAL_H
#define INITIAL_H

#include "complex.h"

class Initial{
	public:
		virtual ~Initial();
		virtual Complex operator()(const double x) = 0;
};

class Gaussian:public Initial{
	private:
		double m_x0;
		double m_p0;
		double m_s0;
	public:
		Gaussian(const double x0, const double p0, const double s0);
		~Gaussian();
		Complex operator()(const double x);
		double tirage();
};

class DGaussian:public Initial{
	private:
		double m_x0;
		double m_s0;
	public:
		DGaussian(const double x0, const double s0);
		~DGaussian();
		Complex operator()(const double x);
		double tirage();
};

#endif
