#include "Transparent.h"

Transparent::Transparent (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular),
		specular_btdf(new PerfectTransmitter)
{}


// ---------------------------------------------------------------- copy constructor

Transparent::Transparent(const Transparent& rm)
	: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;

	if(rm.specular_btdf)
		specular_btdf = rm.specular_btdf;
	else
		specular_btdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Transparent& 
Transparent::operator= (const Transparent& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();
	
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}

	if (rhs.specular_btdf)
		specular_btdf = rhs.specular_btdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- clone

Transparent*										
Transparent::clone(void) const {
	return (new Transparent(*this));
}	


// ---------------------------------------------------------------- destructor

Transparent::~Transparent(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}
}

RGBColor Transparent::shade(ShadeRec &sr){
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflective_ray(sr.hit_point, wi);

	if(specular_btdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflective_ray, sr.depth + 1);
	else{
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr * sr.w.tracer_ptr->trace_ray(reflective_ray, sr.depth + 1) * fabs(sr.normal * wi);
		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
	}
	return L;
}