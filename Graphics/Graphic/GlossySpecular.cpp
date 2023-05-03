#include "GlossySpecular.h"
#include "MultiJittered.h"

// ---------------------------------------------------------------------- default constructor

GlossySpecular::GlossySpecular(void) 
	:   BRDF(),
		ks(0.0), 
		cs(1.0),
		sampler(NULL)// just for fun
{}


// ---------------------------------------------------------------------- copy constructor

GlossySpecular::GlossySpecular(const GlossySpecular& gloss) 
	:   BRDF(gloss),
		ks(gloss.ks), 
		cs(gloss.cs),
		exp(gloss.exp),
		sampler(gloss.sampler)
{}


// ---------------------------------------------------------------------- clone

GlossySpecular* 
GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}	


// ---------------------------------------------------------------------- destructor

GlossySpecular::~GlossySpecular(void) {}


// ---------------------------------------------------------------------- assignment operator

GlossySpecular& 
GlossySpecular::operator= (const GlossySpecular& rhs) {
	if (this == &rhs)
		return (*this);
		
	BRDF::operator= (rhs);
	
	ks = rhs.ks; 
	cs = rhs.cs;
	exp = rhs.exp;
	
	return (*this);
}

// ---------------------------------------------------------------------- set_sampler
// this allows any type of sampling to be specified in the build functions

void
GlossySpecular::set_sampler(Sampler* sp, const double exp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}


// ---------------------------------------------------------------------- set_samples
// this sets up multi-jittered sampling using the number of samples

void
GlossySpecular::set_samples(const int num_samples, const double exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}

// ---------------------------------------------------------------------- f

RGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor L;
	double ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	double rdotwo = r * wo;
	if(rdotwo > 0.0)
		L = ks * cs * pow(rdotwo, exp); // cs
	return  L;
}


// ---------------------------------------------------------------------- rho

RGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, double& pdf) const {
	
	double ndotwo = sr.normal * wo;
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection
	
	Vector3D w = r;								
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w; 
	u.normalize();
	Vector3D v = u ^ w;
		
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction
	
	if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	double phong_lobe = pow(r * wi, exp);
	pdf = phong_lobe * (sr.normal * wi);

	return (ks * cs * phong_lobe);
}


// ----------------------------------------------------------------------------------- rho

RGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}