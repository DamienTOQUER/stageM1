#include<vector>
#include<cmath>
#include<iostream>
//GSL
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_multifit.h>

using namespace std;


#include "const.h"
#include "opemath.h"
#include "poly.h"

double gradient1D(vector<double> & func, unsigned int i){
	if(i==0){
		return gradient1D(func, 1);
	}
	else if(i>=Const::n_x-1){
		return gradient1D(func, Const::n_x-2);
	}
	else{
		return (func[i+1]-func[i-1])/2./Const::pas_x;
	}
}

double laplacien1D(vector<double> & func, unsigned int i){
	if(i==0){
		return laplacien1D(func, 1);
	}
	else if(i>=Const::n_x-1){
		return laplacien1D(func, Const::n_x-2);
	}
	else{
		return (func[i+1]+func[i-1]-2.*func[i])/Const::pas_x/Const::pas_x;
	}
}

double interpolationl1D(double x1, double x2, double f1, double f2, double x){
	return f1 + (f2-f1)/(x2-x1)*(x-x1);
}
bool interpolation_hermite(vector<double> & x, vector<double> & Q, unsigned int imin, unsigned int imax, vector<double> & param, unsigned int loc){
	if(loc==0 || imin==imax || (imin<imax && (imin+loc>imax || imin<0 || imax>=x.size()-1 || imin+loc==imax-loc)) || (imin>imax && (imin-loc<imax || imin>=x.size() || imax<1 || imin-loc==imax+loc))){
		return false;
	}
	Poly Pf;
	vector<double> xp;
	vector<double> Qp;
	vector<double> dQp;
	if(imin<imax){
		xp.push_back(x[imin+loc]);
		xp.push_back(x[imax-loc]);
		xp.push_back(x[imax]);
		Qp.push_back(Q[imin+loc]);
		Qp.push_back(Q[imax-loc]);
		Qp.push_back(Q[imax]);
		dQp.push_back((Q[imin+loc+1]-Q[imin+loc-1])/(x[imin+loc+1]-x[imin+loc-1]));
		dQp.push_back((Q[imax-loc+1]-Q[imax-loc-1])/(x[imax-loc+1]-x[imax-loc-1]));
		dQp.push_back((Q[imax+1]-Q[imax-1])/(x[imax+1]-x[imax-1]));
	}
	else{
		xp.push_back(x[imax]);
		xp.push_back(x[imax+loc]);
		xp.push_back(x[imin-loc]);
		Qp.push_back(Q[imax]);
		Qp.push_back(Q[imax+loc]);
		Qp.push_back(Q[imin-loc]);
		dQp.push_back((Q[imax+1]-Q[imax-1])/(x[imax+1]-x[imax-1]));
		dQp.push_back((Q[imax+loc+1]-Q[imax+loc-1])/(x[imax+loc+1]-x[imax+loc-1]));
		dQp.push_back((Q[imin-loc+1]-Q[imin-loc-1])/(x[imin-loc+1]-x[imin-loc-1]));
	}
	for(unsigned int i=0; i<3; i++){
		vector<double> p;
		lagrange(xp, i, p);
		Poly P(p);
		P = P*P;
		Poly dP(p);
		dP = dP*dP;
		dP.deriv();
		vector<double> q(2, 0);
		double a = dQp[i]-dP(xp[i])*Qp[i];
		q[0] = Qp[i]-a*xp[i];
		q[1] = a;
		Poly Q(q);
		Pf = Pf+P*Q;
	}
	param.clear();
	for(unsigned int i=0; i<Pf.get_size(); i++){
		param.push_back(Pf.get_coeff(i));
	}
	return true;
	
}

bool interpolation_hermite(vector<double> & x, vector<double> & Q, unsigned int imax, vector<double> & param, unsigned int loc1, unsigned int loc2){
	if(loc1==0 || loc2==0 || (loc1>0 && (imax+loc2>x.size()-1 || imax+loc1>x.size()-1 || loc2<0)) || (loc1<0 && (imax+loc2<1 || imax+loc1<1 || loc2>0))){
		return false;
	}
	Poly Pf;
	vector<double> xp;
	vector<double> Qp;
	vector<double> dQp;
	xp.push_back(x[imax+loc1]);
	xp.push_back(x[imax+loc2]);
	xp.push_back(x[imax]);
	Qp.push_back(Q[imax+loc1]);
	Qp.push_back(Q[imax+loc2]);
	Qp.push_back(Q[imax]);
	dQp.push_back((Q[imax+loc1+1]-Q[imax+loc1-1])/(x[imax+loc1+1]-x[imax+loc1-1]));
	dQp.push_back((Q[imax+loc2+1]-Q[imax+loc2-1])/(x[imax+loc2+1]-x[imax+loc2-1]));
	dQp.push_back((Q[imax+1]-Q[imax-1])/(x[imax+1]-x[imax-1]));

	for(unsigned int i=0; i<3; i++){
		vector<double> p;
		lagrange(xp, i, p);
		Poly P(p);
		P = P*P;
		Poly dP(p);
		dP = dP*dP;
		dP.deriv();
		vector<double> q(2, 0);
		double a = dQp[i]-dP(xp[i])*Qp[i];
		q[0] = Qp[i]-a*xp[i];
		q[1] = a;
		Poly Q(q);
		Pf = Pf+P*Q;
	}
	param.clear();
	for(unsigned int i=0; i<Pf.get_size(); i++){
		param.push_back(Pf.get_coeff(i));
	}
	return true;
}

bool interpolation_hermite(vector<double> & x, vector<double> & Q, vector<int> & is, vector<double> & param){
	vector<int> isb;
	for(unsigned int i=0; i<is.size(); i++){
		if(is[i]>1 && is[i]<x.size()-1){
			isb.push_back(is[i]);
		}
	}
	Poly Pf;
	vector<double> xs;
	vector<double> Qs;
	vector<double> dQs;
	for(unsigned int i=0; i<isb.size(); i++){
		xs.push_back(x[isb[i]]);
		Qs.push_back(Q[isb[i]]);
		dQs.push_back((Q[isb[i]+1]-Q[isb[i]-1])/(x[isb[i]+1]-x[isb[i]-1]));
	}
	for(unsigned int i=0; i<isb.size(); i++){
		vector<double> p;
		lagrange(xs, i, p);
		Poly P(p);
		P = P*P;
		Poly dP(p);
		dP = dP*dP;
		dP.deriv();
		vector<double> q(2, 0);
		double a = dQs[i]-dP(xs[i])*Qs[i];
		q[0] = Qs[i]-a*xs[i];
		q[1] = a;
		Poly Q(q);
		Pf = Pf+P*Q;
	}
	param.clear();
	for(unsigned int i=0; i<Pf.get_size(); i++){
		param.push_back(Pf.get_coeff(i));
	}
	return true;
}

double approx_poly(vector<double> & xb, vector<double> & g, vector<double> & param){
	//cout<<xb.size()<<endl;
	gsl_vector* vec_g = gsl_vector_alloc(g.size());
	gsl_matrix* mat_X = gsl_matrix_alloc(g.size(), param.size());
	gsl_vector* vec_p = gsl_vector_calloc(param.size());
	gsl_matrix* mat_C = gsl_matrix_calloc(param.size(), param.size());
	
	double chi2 = 0;
	
	for(unsigned int i=0; i<g.size(); i++){
		gsl_vector_set(vec_g, i, g[i]);
		for(unsigned int j=0; j<param.size(); j++){
			gsl_matrix_set(mat_X, i, j, pow(xb[i], j));
		}
	}
	
	gsl_multifit_linear_workspace *w = gsl_multifit_linear_alloc(g.size(), param.size());
	gsl_multifit_linear(mat_X, vec_g, vec_p, mat_C, &chi2, w);
	
	for(unsigned int j=0; j<param.size(); j++){
		param[j] = gsl_vector_get(vec_p, j);
	}
	
	gsl_multifit_linear_free(w);
	
	gsl_vector_free(vec_g);
	gsl_matrix_free(mat_X);
	gsl_vector_free(vec_p);
	gsl_matrix_free(mat_C);
	return chi2;
}
/*
double approx_poly(vector<double> & xb, vector<double> & g, vector<double> & param, vector<double> & weight){
	//cout<<xb.size()<<endl;
	gsl_vector* vec_g = gsl_vector_alloc(g.size());
	gsl_matrix* mat_X = gsl_matrix_alloc(g.size(), param.size());
	gsl_vector* vec_p = gsl_vector_calloc(param.size());
	gsl_matrix* mat_C = gsl_matrix_calloc(param.size(), param.size());
	gsl_vector* vec_w = gsl_vector_calloc(weight.size());
	
	double chi2 = 0;
	
	for(unsigned int i=0; i<g.size(); i++){
		gsl_vector_set(vec_g, i, g[i]);
		gsl_vector_set(vec_w, i, weight[i]);
		for(unsigned int j=0; j<param.size(); j++){
			gsl_matrix_set(mat_X, i, j, pow(xb[i], j));
		}
	}
	
	gsl_multifit_linear_workspace *w = gsl_multifit_linear_alloc(g.size(), param.size());
	gsl_multifit_wlinear(mat_X, vec_w, vec_g, vec_p, mat_C, &chi2, w);
	
	for(unsigned int j=0; j<param.size(); j++){
		param[j] = gsl_vector_get(vec_p, j);
	}
	
	gsl_multifit_linear_free(w);
	
	gsl_vector_free(vec_g);
	gsl_matrix_free(mat_X);
	gsl_vector_free(vec_p);
	gsl_matrix_free(mat_C);
	gsl_vector_free(vec_w);
	return chi2;
}
*/
void approx_monome(double x1, double x2, double x3, double Q1, double Q2, double Q3, int N, vector<double> & param, vector<vector<int>> & bin){
	vector<double> p(N+1, 0);
	for(unsigned int i=0; i<=N; i++){
		p[i] = bin[N][i]*pow(-x2, N-i);
	}
	Poly P(p);
	P = P*((Q1-Q2)/pow(x1-x2, N));
	param = vector<double>(N+1, 0);
	for(unsigned int i=0; i<=N; i++){
		param[i] = P.get_coeff(i);
	}
	param[0]+=Q2;
}

void approx_monome2(double x1, double x2, double Q1, double Qp1, double Qp2, int N, vector<double> & param, vector<vector<int>> & bin){
	double rQp1 = (Qp1>=0)?pow(Qp1, 1./(1.*N-1.)):-pow(-Qp1, 1./(1.*N-1.));
	double rQp2 = (Qp2>=0)?pow(Qp2, 1./(1.*N-1.)):-pow(-Qp2, 1./(1.*N-1.));
	double b = pow(rQp1-rQp2, N-1)/(1.*N)/pow(x1-x2, N-1);
	double c = (rQp1*x2-rQp2*x1)/(rQp1-rQp2);
	vector<double> p(N+1, 0);
	for(unsigned int i=0; i<=N; i++){
		p[i] = bin[N][i]*pow(-c, N-i);
	}
	Poly P(p);
	P = P*b;
	double v = P(x1);
	for(unsigned int i=0; i<=N; i++){
		param[i] = P.get_coeff(i);
	}
	param[0]=param[0]-v+Q1;
}

void approx_monome3(double x1, double x2, double Q1, double Q2, int N, vector<double> & param, vector<vector<int>> & bin, bool ispos){
	double b = ((ispos)?1.:-1.)*abs(Q2-Q1)/pow(x1-x2, N);
	double a = x1;
	vector<double> p(N+1, 0);
	for(unsigned int i=0; i<=N; i++){
		p[i] = bin[N][i]*pow(-a, N-i);
	}
	Poly P(p);
	P = P*b;
	for(unsigned int i=0; i<=N; i++){
		param[i] = P.get_coeff(i);
	}
	param[0]=param[0]+Q1;
}

double calc_chi2(vector<double> & xb, vector<double> & g, vector<double> & param){
	Poly p(param);
	double chi2 = 0;
	for(unsigned int i=0; i<xb.size(); i++){
		chi2+=pow(g[i]-p(xb[i]), 2);
	}
	return chi2;
}

double calc_gradchi2(vector<double> & xb, vector<double> & g, vector<double> & param, unsigned int j){
	Poly p(param);
	double gchi2 = 0;
	for(unsigned int i=0; i<xb.size(); i++){
		gchi2+=2*(g[i]-p(xb[i]))*pow(xb[i], j);
	}
	return gchi2;
}

int factorial(int k){
	if(k==0 or k==1){
		return 1;
	}
	else if(k==2){
		return 2;
	}
	else if(k==3){
		return 6;
	}
	else if(k==4){
		return 24;
	}
	else{
		return k*factorial(k-1);
	}
}

void binom(int Nmax, vector<vector<int>> & bin){
	bin = vector<vector<int>>(Nmax+1);
	for(unsigned int n=0; n<=Nmax; n++){
		bin[n] = vector<int>(n+1, 0);
		bin[n][0]=1;
		bin[n][n]=1;
		for(unsigned int k=1; k<n; k++){
			bin[n][k] = bin[n-1][k-1] + bin[n-1][k];
		}
	}
	
}

void lagrange(vector<double> x, unsigned int i, vector<double> & param){
	vector<double> p(1, 1);
	Poly P(p);
	for(unsigned int j=0; j<x.size(); j++){
		if(i!=j){
			vector<double> p2(2, 1);
			p2[0] = -x[j];
			Poly P2(p2);
			P2 = P2*(1./(x[i]-x[j]));
			P = P * P2;
		}
	}
	param.clear();
	for(unsigned int i=0; i<P.get_size(); i++){
		param.push_back(P.get_coeff(i));
	}
}

