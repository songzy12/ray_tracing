#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "World.h"			// you will need this later on for shadows
#include "ShadeRec.h"

class PointLight: public Light {
	public:
	
		PointLight(void);   							

		PointLight(const PointLight& a); 					 
	
		virtual Light* 									
		clone(void) const;	
		
		PointLight& 									
		operator= (const PointLight& rhs);									
		
		virtual 									
		~PointLight(void);
				
		void
		scale_radiance(const double b);
		
		void
		set_color(const double c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const double r, const double g, const double b); 
		
		void
		set_location(const double x, const double y, const double z); 

		virtual Vector3D								
		get_direction(ShadeRec& s); 
		
		virtual RGBColor
		L(ShadeRec& s) const; // remember this.

		virtual bool in_shadow(const Ray &ray, const ShadeRec &sr) const;
	
	private:
	
		double		ls;
		RGBColor	color;
		Vector3D	location;
};




// ------------------------------------------------------------------------------- scale_radiance

inline void
PointLight::scale_radiance(const double b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const double c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const double r, const double g, const double b) {
	color.r = r; color.g = g; color.b = b;
}

inline void PointLight::set_location(const double x, const double y, const double z){
	location.x  = x; location.y = y; location.z = z;
}

#endif