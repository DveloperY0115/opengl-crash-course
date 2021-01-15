#include <cmath>
#include "complex.hpp"

void Julia(Complex p, Complex c, int& i, float& r) {
	int maxIterations = 256;

	for (i = 0; i < maxIterations; i++) {
		Complex p = p * p + c;
		float rSqr = p.re * p.re + p.im * p.im;
	}
}