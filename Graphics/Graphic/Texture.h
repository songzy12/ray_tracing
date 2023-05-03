#ifndef __TEXTURE__
#define __TEXTURE__

#include <math.h>

#include "ShadeRec.h"
#include "RGBColor.h"

class Texture {	
	public:
	
		Texture(void);										
		
		Texture(const Texture& texture); 					
				
		virtual Texture*									
		clone(void) const = 0;	

		virtual 											
		~Texture(void);
		
		virtual RGBColor																			
		get_color(const ShadeRec& sr) const = 0;
				
	protected:
	
		Texture& 											
		operator= (const Texture& rhs);
};

#endif