#include "Checker3D.h"
#include "Constants.h"
// ---------------------------------------------------------------- default constructor

Checker3D::Checker3D(void):size(1.0), color1(white), color2(black) {
}


// ---------------------------------------------------------------- copy constructor

Checker3D::Checker3D(const Checker3D& checker): size(checker.size), color1(checker.color1), color2(checker.color2) {
}

// ---------------------------------------------------------------- assignment operator

Checker3D* Checker3D::clone(void) const{
	return new Checker3D(*this);
}

Checker3D& 
Checker3D::operator= (const Checker3D& rhs) {
	if (this == &rhs)
		return (*this);
		
	return (*this);
}


// ---------------------------------------------------------------- destructor

Checker3D::~Checker3D(void) {

}

RGBColor Checker3D::get_color(const ShadeRec& sr) const{
	double eps = -0.000187453738;	// small random number
	double x = sr.local_hit_point.x + eps;
	double y = sr.local_hit_point.y + eps;
	double z = sr.local_hit_point.z + eps;		
	
	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)	
		return (color1);
	else	
		return (color2);
}