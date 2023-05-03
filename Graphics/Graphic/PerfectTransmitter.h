
#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

class PerfectTransmitter: public BTDF {
	public:
	
		PerfectTransmitter(void);
		
		PerfectTransmitter(const PerfectTransmitter& pt);
		
		virtual PerfectTransmitter*
		clone(void);
		
		~PerfectTransmitter(void);
		
		PerfectTransmitter&							
		operator= (const PerfectTransmitter& rhs);
		
		void
		set_kt(const double k);
		
		void
		set_ior(const double eta);

		bool													
		tir(const ShadeRec& sr) const;
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
				
	private:
	
		double	kt;			// transmission coefficient
		double	ior;		// index of refraction
};


// -------------------------------------------------------------- set_kt

inline void
PerfectTransmitter::set_kt(const double k) {
	kt = k;
}

// -------------------------------------------------------------- set_ior

inline void
PerfectTransmitter::set_ior(const double eta) {
	ior = eta;
}

#endif
