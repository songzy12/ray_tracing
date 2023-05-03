#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "Lambertian.h"

//----------------------------------------------------------------------------- class Emissive

class Emissive: public Material {	
	public:
			
		Emissive(void);											

		Emissive(const Emissive& m);
		
		virtual Material*										
		clone(void) const;									

		Emissive& 
		operator= (const Emissive& rhs);							

		~Emissive(void);											
		
		void scale_radiance(const double ls);

		void set_ce(const double r, const double g, const double b);
		
		void set_ce(const RGBColor& color);

		virtual RGBColor get_Le(ShadeRec &sr);

		virtual RGBColor area_light_shade(ShadeRec& sr);
		
	private:
		
		double ls;
		RGBColor ce;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void	Emissive::scale_radiance(const double l){
	ls = l;
}

inline void Emissive::set_ce(const double r, const double g, const double b){
	ce.r = r; ce.g = g; ce.b = b;
}

inline void Emissive::set_ce(const RGBColor& color){
	ce = color;
}

inline RGBColor Emissive::get_Le(ShadeRec &sr){
	return ls * ce;
}

#endif