#ifndef __GLOSSYSPECULAR__
#define __GLOSSYSPECULAR__

#include "BRDF.h"

class GlossySpecular: public BRDF {
	public:
	
		GlossySpecular(void);
		
		GlossySpecular(const GlossySpecular& gloss);
		
		virtual GlossySpecular*
		clone(void) const;
		
		~GlossySpecular(void);
		
		GlossySpecular& 
		operator= (const GlossySpecular& rhs);
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, double& pdf) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
				
		void
		set_ks(const double ks);
		
		void
		set_cs(const RGBColor& c);
		
		void													
		set_cs(const double r, const double g, const double b);
		
		void													
		set_cs(const double c);

		void													
		set_exp(const double e);
		
		void
		set_sampler(Sampler* sp, const double exp);   			// any type of sampling
		
		void
		set_samples(const int num_samples, const double exp); 	// multi jittered sampling
		
		void
		set_normal(const Normal& n);
					
	private:
	
		double		ks;// diffuse coefficient
		RGBColor 	cs;// diffuse color
		double		exp;
		Sampler*	sampler;    // for use in sample_f
};




// -------------------------------------------------------------- set_ks

inline void
GlossySpecular::set_ks(const double k) {
	ks = k;
}


// -------------------------------------------------------------- set_cs

inline void
GlossySpecular::set_cs(const RGBColor& c) {
	cs = c;
}


// ---------------------------------------------------------------- set_cs

inline void													
GlossySpecular::set_cs(const double r, const double g, const double b) {
	cs.r = r; cs.g = g; cs.b = b;
}


// ---------------------------------------------------------------- set_cs

inline void													
GlossySpecular::set_cs(const double c) {
	cs.r = c; cs.g = c; cs.b = c;
}

inline void													
GlossySpecular::set_exp(const double e) {
	exp = e;
}

#endif