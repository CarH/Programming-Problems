#include <iostream>		// fixed
#include <iomanip>		// setprecision
#include <cmath>		// exp, sin, cos, tan
#define EPS 1e-7
using namespace std;

// Set true to enable the comparison between the Bisection and Secant methods
bool COMPARE = true;

int p, q, r, s, t, u;

double f(double x) {
	return (p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * (x*x) + u);
}

// Bisection Method
double bisection(double lo, double hi) {
	int iterations=0;
	while ( hi-lo > EPS ) {
		iterations++;
		double mid = (hi+lo)/2.0;
		if ( f(lo)*f(mid) <= 0 ) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	if (COMPARE) cout << " # iterations (Bisection): " << iterations << "\n";
	return (hi+lo)/2.0;
}

// A faster approach - Secant method
double secant(double x0, double x1) {
	int iterations=0;
	if (f(x0) == 0) return 0;
	while ( 1 ) {
		double f1 = f(x1);
		double delta = ( f1 * (x1 - x0) ) / ( f1 - f(x0) );
		iterations++;
		if ( fabs(delta) < EPS ) {
			if (COMPARE) cout << " # iterations (Secant): " << iterations << "\n";
			return x1;
		}
		x0 = x1;
		x1 = x1 - delta;
	}
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	while ( cin >> p >> q >> r >> s >> t >> u ) {

		if ( f(0)*f(1) > 0.0 ) {
			cout << "No solution\n";
		}
		else {
			if (COMPARE) {
				cout << fixed;
				cout << setprecision(4) << bisection(0, 1) << "\n";
			}
			cout << fixed;
			cout << setprecision(4) << secant(0, 1) << "\n";
		}
	}
	return 0;
}