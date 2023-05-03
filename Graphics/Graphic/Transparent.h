#ifndef __TRANSPARENT__
#define __TRANSPARENT__

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"
class Transparent: public Phong {	
	public:

		Transparent(void);										

		Transparent(const Transparent& rm);						

		Transparent& 
		operator= (const Transparent& rhs);						

		virtual Transparent*										
		clone(void) const;				

		~Transparent(void);

		void
		set_kr(const double k);
				
		void													
		set_cr(const RGBColor& c);
		
		void
		set_cr(const double r, const double g, const double b);
		
		void
		set_cr(const double c);
		
		void
		set_kt(const double k);
		
		void
		set_ior(const double eta);

		virtual RGBColor										
		shade(ShadeRec& sr);

	private:

		PerfectSpecular* 	reflective_brdf;
		PerfectTransmitter* specular_btdf;	
};

inline void
Transparent::set_kr(const double k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const RGBColor& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const double r, const double g, const double b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const double c) {
	reflective_brdf->set_cr(c);
}

inline void Transparent::set_kt(const double k) {
	specular_btdf->set_kt(k);
}

// -------------------------------------------------------------- set_ior

inline void	Transparent::set_ior(const double eta) {
	specular_btdf->set_ior(eta);
}

#endif