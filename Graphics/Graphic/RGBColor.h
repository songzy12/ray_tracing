#ifndef __RGB_COLOR__
#define __RGB_COLOR__

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {
	
	public:
	
		double	r, g, b;									
				
	public:
	
		RGBColor(void);										// default constructor
		RGBColor(double c);									// constructor
		RGBColor(double _r, double _g, double _b);				// constructor
		RGBColor(const RGBColor& c); 						// copy constructor
		
		~RGBColor(void);									// destructor
		
		RGBColor& 											// assignment operator
		operator= (const RGBColor& rhs); 

		RGBColor 											// addition
		operator+ (const RGBColor& c) const;	

		RGBColor& 											// compound addition
		operator+= (const RGBColor& c);
		
		RGBColor 											// multiplication by a double on the right
		operator* (const double a) const;
		
		RGBColor& 											// compound multiplication by a double on the right
		operator*= (const double a);					
				
		RGBColor 											// division by a double
		operator/ (const double a) const;
		
		RGBColor& 											// compound division by a double
		operator/= (const double a); 
				
		RGBColor 											// component-wise multiplication
		operator* (const RGBColor& c) const;
		
		bool												// are two RGBColours the same?
		operator== (const RGBColor& c) const;				

		RGBColor											// raise components to a power
		powc(double p) const;
		
		double												// the average of the components
		average(void) const;
};



// inlined member functions

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) {
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline RGBColor 
RGBColor::operator* (const double a) const {
	return (RGBColor (r * a, g * a, b * a));	
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a double on the right

inline RGBColor& 
RGBColor::operator*= (const double a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by double

inline RGBColor 
RGBColor::operator/ (const double a) const {
	return (RGBColor (r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by double

inline RGBColor& 
RGBColor::operator/= (const double a) {	
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline RGBColor 
RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor (r * c.r, g * c.g, b * c.b));
} 


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

inline bool
RGBColor::operator== (const RGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}


// ----------------------------------------------------------------------- average
// the average of the three components

inline double											
RGBColor::average(void) const {
	return (0.333333333333 * (r + g + b));
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

RGBColor 
operator* (const double a, const RGBColor& c);

inline RGBColor 
operator* (const double a, const RGBColor& c) {
	return (RGBColor (a * c.r, a * c.g, a * c.b));	
}


#endif