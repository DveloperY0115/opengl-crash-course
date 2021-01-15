class Complex {
public:
	// constructor
	Complex(float re_, float im_) {
		re = re_;
		im = im_;
	}

	// operator overloading for addition
	Complex operator+ (Complex& c) {
		float re = this->re + c.re;
		float im = this->im + c.im;

		return Complex(re, im);
	}

	// operator overloading for multiplication
	Complex operator* (Complex& c) {
		float re = this->re * c.re - this->im * c.im;
		float im = this->im * c.re + this->re * c.im;

		return Complex(re, im);
	}

public:
	float re;
	float im;
};