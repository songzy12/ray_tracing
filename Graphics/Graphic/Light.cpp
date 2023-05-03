#include "Light.h"

#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light(void):casts_shadows(true) {}

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls){}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {} 



// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
Light::L(ShadeRec& s) const {
	return (black);
}

double Light::G(ShadeRec &sr) const {
	return 1;
}
		
double Light::pdf(ShadeRec& sr) const {
	return 0;
}