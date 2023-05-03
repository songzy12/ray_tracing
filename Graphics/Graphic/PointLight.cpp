
#include "PointLight.h"
// ---------------------------------------------------------------------- default constructor

PointLight::PointLight (void)
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}


// ---------------------------------------------------------------------- copy constructor

PointLight::PointLight (const PointLight& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}


// ---------------------------------------------------------------------- clone

Light* 
PointLight::clone(void) const {
	return (new PointLight(*this));
}	


// ---------------------------------------------------------------------- assignment operator

PointLight& 
PointLight::operator= (const PointLight& rhs) {
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

PointLight::~PointLight (void) {}


// ---------------------------------------------------------------------- get_direction	

Vector3D								
PointLight::get_direction(ShadeRec& s) {
	return (location - s.hit_point).hat();
}


// ---------------------------------------------------------------------- L

RGBColor
PointLight::L(ShadeRec& sr) const{	
	return (ls * color);
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const{
	double t;
	int num_objects = sr.w.objects.size();
	double d = (location - ray.o).length();

	for(int j=0; j < num_objects; j++)
		if(sr.w.objects[j]->shadow_hit(ray, t) && t<d)
			return true;
	return false;
}