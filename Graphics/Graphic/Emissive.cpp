#include "Emissive.h"

// ---------------------------------------------------------------- default constructor

Emissive::Emissive (void)
	:	Material(),
		ls(0.0),
		ce(white)
{}



// ---------------------------------------------------------------- copy constructor

Emissive::Emissive(const Emissive& m)
	: 	Material(m), ls(m.ls), ce(m.ce){
	
}


// ---------------------------------------------------------------- clone

Material*										
Emissive::clone(void) const {
	return (new Emissive(*this));
}	


// ---------------------------------------------------------------- assignment operator

Emissive& 
Emissive::operator= (const Emissive& rhs) {
	if (this == &rhs)
		return (*this);
	
	Material::operator=(rhs);
	ls = rhs.ls;
	ce = rhs.ce;
	return (*this);
}


// ---------------------------------------------------------------- destructor

Emissive::~Emissive(void) {
}


// ---------------------------------------------------------------- shade

RGBColor
Emissive::area_light_shade(ShadeRec& sr) {
	if(-sr.normal * sr.ray.d > 0.0)
		return ls * ce;
	else
		return black;
}