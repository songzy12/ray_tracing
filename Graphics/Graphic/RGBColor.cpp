// This file contains the definition of the class RGBColor

#include <math.h>

#include "RGBColor.h"

// -------------------------------------------------------- default constructor

RGBColor::RGBColor(void)
	: r(0.0), g(0.0), b(0.0) 							
{}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(double c)
	: r(c), g(c), b(c) 							
{}
								

// -------------------------------------------------------- constructor

RGBColor::RGBColor(double _r, double _g, double _b)	
	: r(_r), g(_g), b(_b)
{}


// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{} 				 
		

// -------------------------------------------------------- destructor

RGBColor::~RGBColor(void)		
{}


// --------------------------------------------------------assignment operator

RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}
 

// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor
RGBColor::powc(double p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}