#include "Texture.h"
#include "SV_Lambertian.h"
#include "Material.h"

class SV_Matte: public Material {		
	public:
	
		SV_Matte(void);											

		SV_Matte(const SV_Matte& m);
		
		virtual Material*										
		clone(void) const;									

		SV_Matte& 
		operator= (const SV_Matte& rhs);							

		~SV_Matte(void);											
		
		void 													
		set_ka(const double k); // ambient
		
		void 													
		set_kd(const double k); // diffuse
	
		void
		set_cd(Texture* t_ptr);
		
		void set_sampler(Sampler* sPtr);

		virtual RGBColor shade(ShadeRec& s);	
	
	private:
	
		SV_Lambertian*	ambient_brdf;
		SV_Lambertian*	diffuse_brdf;
};

inline void SV_Matte::set_sampler(Sampler* sPtr){
	ambient_brdf->set_sampler(sPtr);
	diffuse_brdf->set_sampler(sPtr);
}

inline void								
SV_Matte::set_ka(const double ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
SV_Matte::set_kd (const double kd) {
	diffuse_brdf->set_kd(kd);
}

inline void
SV_Matte::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}