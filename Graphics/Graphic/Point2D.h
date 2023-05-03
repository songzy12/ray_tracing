#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {	
	public:
	
		double	x, y;
				
	public:
	
		Point2D (void);										// default constructor
		Point2D (const double arg);							// constructor
		Point2D (const double x1, const double y1);			// constructor
		Point2D (const Point2D& p); 						// copy constructor
		~Point2D (void) {}									// destructor

		Point2D& 											// assignment operator
		operator= (const Point2D& rhs);
		
		Point2D												// multiplication on right by scalar
		operator* (const double a);
};


// scales the point by the double a

inline Point2D
Point2D::operator* (const double a) {
	return (Point2D(a * x, a * y));
}


#endif