#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;
	
#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"


//----------------------------------------------------------------------------------------------------- Class GeometricObject

class GeometricObject {	
	
	public:	

		GeometricObject(void);									// default constructor
		
		GeometricObject(const GeometricObject& object);			// copy constructor
	
		virtual GeometricObject*								// virtual copy constructor
		clone(void) const = 0;

		virtual 												// destructor
		~GeometricObject (void);	
			
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

		virtual bool shadow_hit(const Ray& ray, double& t) const = 0;
				
		Material*						
		get_material(void) const;

		virtual void 							// needs to virtual so that it can be overriden in Compound
		set_material(Material* mPtr); 			
		
		virtual Point3D 		
		sample(void) const;
		
		virtual double
		pdf(ShadeRec& sr) const; 
		
		virtual Normal
		get_normal(void) const; 
		
		virtual Normal
		get_normal(const Point3D& p); 
		//void set_color(double r, double g, double b);

		//RGBColor get_color() const;
	
	protected:
		
		//RGBColor color;

		mutable Material*   material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
	
		GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);
};


// ------------------------------------------------------------------------- get_material


/*inline RGBColor GeometricObject::get_color() const{
	return color;
}

inline void GeometricObject::set_color(double r, double g, double b){
	color.r = r;
	color.g = g;
	color.b = b;
}*/

#endif