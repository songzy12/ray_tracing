#ifndef __PINHOLE__
#define __PINHOLE__

// This file contains the declaration of the class Pinhole

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here

//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
	public:
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const double vpd);
		
		void
		set_zoom(const double zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		virtual void 												
		render_scene(const World& w, cv::Mat &img);
		
	private:
			
		double	d;		// view plane distance
		double	zoom;	// zoom factor
		
};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(double _d) {
	d = _d;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(double zoom_factor) {
	zoom = zoom_factor;
}	

#endif