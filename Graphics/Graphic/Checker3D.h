#ifndef __CHECKER3D__
#define __CHECKER3D__

#include <math.h>

#include "Texture.h"

class Checker3D: public Texture {	
public:
	
	Checker3D(void);										
		
	Checker3D(const Checker3D& checker);

	virtual 											
	~Checker3D(void);

	virtual Checker3D* clone(void) const;	
		
	virtual RGBColor																			
	get_color(const ShadeRec& sr) const;
	
	void set_color1(const RGBColor& c);
	
	void set_color2(const RGBColor& c);
	
	void set_size(const double s);
protected:

	Checker3D& 											
	operator= (const Checker3D& rhs);
private:
	double size;
	RGBColor color1;
	RGBColor color2;
};

inline void Checker3D::set_color1(const RGBColor& c){
	color1 = c;
}
inline void Checker3D::set_color2(const RGBColor& c){
	color2 = c;
}

inline void Checker3D::set_size(const double s){
	size = s;
}
#endif