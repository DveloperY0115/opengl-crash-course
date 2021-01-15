#include <cmath>
#include "complex.hpp"

void Julia(Complex p, Complex c, int& i, float& r) {
	int maxIterations = 256;
	float rSqr;

	for (i = 0; i < maxIterations; i++) {
		Complex p = p * p + c;
		rSqr = p.re * p.re + p.im * p.im;

		if (rSqr > 4)
			break;
	}
	 
	r = sqrt(rSqr);
}