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
		double deriv(double x, double t);
	private:
		double m_val;
};

class PotOH:public Potential{
	public:
		PotOH(double pulsation);
		~PotOH();
		double operator()(double x, double t);
		double deriv(double x, double t);
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

class PotQuart:public Potential{
	public:
		PotQuart(double a2, double a4);
		~PotQuart();
		double operator()(double x, double t);
		double deriv(double x, double t);
	private:
		double m_a2;
		double m_a4;
};

class PotFis:public Potential{
	public:
		PotFis(double x1, double x2, double s1, double s2, double a1, double a2);
		~PotFis();
		double operator()(double x, double t);
		double deriv(double x, double t);
	private:
		double m_x1;
		double m_x2;
		double m_s1;
		double m_s2;
		double m_a1;
		double m_a2;
};

class PotAbs:public Potential{
	public:
		PotAbs(double x, double a);
		~PotAbs();
		double operator()(double x, double t);
	private:
		double m_x;
		double m_a;
};

class PotDAbs:public Potential{
	public:
		PotDAbs(double x, double a);
		~PotDAbs();
		double operator()(double x, double t);
	private:
		double m_x;
		double m_a;
};

class PotWS:public Potential{
	public:
		PotWS(double V0, double a);
		~PotWS();
		double operator()(double x, double t);
		double deriv(double x, double t);
	private:
		double m_V0;
		double m_a;
};

#endif
