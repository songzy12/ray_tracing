#include "ConstantColor.h"

ConstantColor::ConstantColor(void):color(0.0){
}
		
ConstantColor::ConstantColor(const ConstantColor& constant_color):
	color(constant_color.color){
	
}
				
ConstantColor*	ConstantColor::clone(void) const{
	return new ConstantColor(*this);
}

ConstantColor::~ConstantColor(void){
}
		
ConstantColor& ConstantColor::operator= (const ConstantColor& rhs){
	if (this == &rhs)
		return (*this);
	
	color = rhs.color;
	return *this;
}

void ConstantColor::set_color(const RGBColor &c){
	color = c;
}

RGBColor ConstantColor::get_color(const ShadeRec& sr) const {
	return (color);
}