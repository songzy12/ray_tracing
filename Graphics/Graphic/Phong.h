#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

//----------------------------------------------------------------------------- class Phong

class Phong: public Material {	
	public:
			
		Phong(void);											

		Phong(const Phong& m);
		
		virtual Material*										
		clone(void) const;									

		Phong& 
		operator= (const Phong& rhs);							

		~Phong(void);											
		
		void 													
		set_ka(const double k); // ambient
		
		void 													
		set_kd(const double k); // diffuse
		
		void set_ks(const double k); // specular

		void set_exp(const double e);

		void													
		set_cd(const RGBColor c); // color
		
		void													
		set_cd(const double r, const double g, const double b);
		
		void																						
		set_cd(const double c);
				
		virtual RGBColor										
		shade(ShadeRec& s);
		
	private:
		
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular* specular_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Phong::set_ka(const double ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Phong::set_kd (const double kd) {
	diffuse_brdf->set_kd(kd);
}

inline void								
Phong::set_ks (const double ks) {
	specular_brdf->set_ks(ks);
}

inline void Phong::set_exp (const double e){
	specular_brdf->set_exp(e);
}

// ---------------------------------------------------------------- set_cd

inline void												
Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
	specular_brdf->set_cs(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const double r, const double g, const double b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
	specular_brdf->set_cs(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const double c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
	specular_brdf->set_cs(c);
}

#endif