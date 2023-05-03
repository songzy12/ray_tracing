#ifndef __SVLAMBERTIAN__
#define __SVLAMBERTIAN__

#include "BRDF.h"
#include "Texture.h"
class SV_Lambertian: public BRDF {
	public:
		SV_Lambertian(void);
		
		SV_Lambertian(const SV_Lambertian& lamb);
		
		virtual SV_Lambertian*
		clone(void) const;
		
		~SV_Lambertian(void);
		
		SV_Lambertian& 
		operator= (const SV_Lambertian& rhs);
	
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
	
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, double& pdf) const;
		
		void
		set_ka(const double ka);
				
		void
		set_kd(const double kd);
		
		void
		set_cd(Texture* c);
	private:
	
		double		kd;
		Texture* 	cd;
};

inline void
SV_Lambertian::set_ka(const double k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
SV_Lambertian::set_kd(const double k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
SV_Lambertian::set_cd(Texture *c) {
	cd = c;
}
#endif