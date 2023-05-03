#include "Texture.h"

class ConstantColor: public Texture {		
	public:
		
		ConstantColor(void);										
		
		ConstantColor(const ConstantColor& constant_color); 					
				
		virtual ConstantColor*									
		clone(void) const;	

		virtual 											
		~ConstantColor(void);
		
		ConstantColor& 											
		operator= (const ConstantColor& rhs);
		
		void
		set_color(const RGBColor& c); 
		
		virtual RGBColor get_color(const ShadeRec& sr) const;
		
	private:
		
		RGBColor color;	 // the color		
};