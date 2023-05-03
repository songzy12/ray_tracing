

#include "BTDF.h"

// ------------------------------------------------------------------------ default constructor

BTDF::BTDF(void) {}


// ------------------------------------------------------------------------ copy constructor

BTDF::BTDF(const BTDF& btdf) {}


// ------------------------------------------------------------------------ destructor

BTDF::~BTDF(void) {}


// ------------------------------------------------------------------------ assignment operator

BTDF&														
BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ------------------------------------------------------------------------ f

RGBColor
BTDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

RGBColor
BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ rho	
	
RGBColor
BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}