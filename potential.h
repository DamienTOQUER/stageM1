#ifndef POTENTIAL_H
#define POTENTIAL_H

class Potential{
	public:
		virtual ~Potential();
		virtual double operator()(double x, double t) = 0;
};

class PotConst:public Potential{
	public:
		PotConst(double val);
		~PotConst();
		double operator()(double x, double t);
	private:
		double m_val;
};

class PotOH:public Potential{
	public:
		PotOH(double pulsation);
		~PotOH();
		double operator()(double x, double t);
	private:
		double m_pulsation;
};

class PotRamp:public Potential{
	public:
		PotRamp(double center, double slope);
		~PotRamp();
		double operator()(double x, double t);
	private:
		double m_center;
		double m_slope;
};

class PotWall:public Potential{
	public:
		PotWall(double center, double height, double width);
		~PotWall();
		double operator()(double x, double t);
	private:
		double m_center;
		double m_height;
		double m_width;
};

#endif
