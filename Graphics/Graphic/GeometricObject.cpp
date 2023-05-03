// this file contains the definition of the class GeometricObject 

#include "Constants.h"
#include "Material.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor


GeometricObject::GeometricObject(void)
	: material_ptr(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object) {
	if(object.material_ptr)
		material_ptr = object.material_ptr->clone(); 
	else  material_ptr = NULL;
}	


// ---------------------------------------------------------------------- assignment operator

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);
			
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {	
	/*if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}*/
}


// ---------------------------------------------------------------- set_material

void 
GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}


Material* 
GeometricObject::get_material(void) const {
	return (material_ptr);
}

Normal
GeometricObject::get_normal(void) const{
	return (Normal());
} 

Normal
GeometricObject::get_normal(const Point3D& p) {
	return (Normal());
} 
Point3D 
GeometricObject::sample(void) const {
	return (Point3D(0.0));
}


// ----------------------------------------------------------------------- pdf
// returns the probability density function for area light shading
		
double
GeometricObject::pdf(ShadeRec& sr) const{
	return (0.0);
}  