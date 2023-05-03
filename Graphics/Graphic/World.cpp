// this file contains the definition of the World class


#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"
#include "Rectangle.h"
// tracers

#include "AreaLighting.h"
#include "Whitted.h"
// cameras

#include "Pinhole.h"

// lights

#include "Directional.h"
#include "PointLight.h"
#include "AreaLight.h"
// materials

#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"
#include "Reflective.h"
#include "Transparent.h"
#include "SV_Matte.h"
// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

// samplers

#include "MultiJittered.h"

// textures

#include "Image.h"
#include "ImageTexture.h"
#include "Mapping.h"
#include "SphericalMap.h"
#include "Checker3D.h"
// build functions

// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new Ambient),
		camera_ptr(NULL)/*,
		eye(100),
		d(100)*/
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	
		
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
			
		
	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}
	
	delete_objects();	
	delete_lights();				
}

void World::build1(){
	int num_samples = 1;//16
	
	vp.set_hres(600);	  		
	vp.set_vres(600);        
	vp.set_samples(num_samples);
	vp.set_max_depth(4);//19
	
	tracer_ptr = new Whitted(this);
			
	Pinhole* pinhole_ptr = new Pinhole;
	
	pinhole_ptr->set_eye(1.7, 1.5, 1.7);
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(175);// TODO:
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.3);
	glass_ptr->set_exp(2000);	
	glass_ptr->set_kr(0.1);
	glass_ptr->set_ior(1.5);	
	glass_ptr->set_kt(0.8);	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-1.415, 0, 1.415), 1); 
	sphere_ptr2->set_material(glass_ptr);
	add_object(sphere_ptr2);
	
	// four point lights near the ceiling
	// these don't use distance attenuation

	double point_position = 2.5;
	double light_radiance = 2;
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(point_position, point_position, 0); 
	light_ptr1->scale_radiance(light_radiance); 
	light_ptr1->set_shadows(true); 
    add_light(light_ptr1);
    
    PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, point_position, point_position); 
	light_ptr2->scale_radiance(light_radiance); 
	light_ptr2->set_shadows(true); 
    add_light(light_ptr2);
    
    PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(-point_position, point_position, 0); 
	light_ptr3->scale_radiance(light_radiance); 
	light_ptr3->set_shadows(true); 
    add_light(light_ptr3);
    
    PointLight* light_ptr4 = new PointLight;
	light_ptr4->set_location(0, point_position, -point_position); 
	light_ptr4->scale_radiance(light_radiance); 
	light_ptr4->set_shadows(true); 
    add_light(light_ptr4);

	double room_size = 3.75;
	
	// floor  (-ve yw)
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.1);   
	matte_ptr1->set_kd(0.50);
	matte_ptr1->set_cd(0.25);     // medium grey
	
	Plane* floor_ptr = new Plane(Point3D(0, -room_size,  0), Normal(0, 1, 0));
	floor_ptr->set_material(matte_ptr1);        
	add_object(floor_ptr);
	
	
	// ceiling  (+ve yw)
	
	Matte* matte_ptr2 = new Matte;   
	matte_ptr2->set_ka(0.35);   
	matte_ptr2->set_kd(0.50);
	matte_ptr2->set_cd(white);
	
	Plane* ceiling_ptr = new Plane(Point3D(0, room_size,  0), Normal(0, -1, 0));
	ceiling_ptr->set_material(matte_ptr2);        
	add_object(ceiling_ptr);
	
	
	// back wall  (-ve zw)
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15); 
	matte_ptr3->set_kd(0.60);
	matte_ptr3->set_cd(0.5, 0.75, 0.75);     // cyan
	
	Plane* backWall_ptr = new Plane(Point3D(0, 0,  -room_size), Normal(0, 0, 1));
	backWall_ptr->set_material(matte_ptr3);        
	add_object(backWall_ptr);
	
	// front wall  (+ve zw)
	
	Plane* frontWall_ptr = new Plane(Point3D(0, 0,  room_size), Normal(0, 0, -1));
	frontWall_ptr->set_material(matte_ptr3);        
	add_object(frontWall_ptr);
	
	// left wall  (-ve xw)
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.15); 
	matte_ptr4->set_kd(0.60);
	matte_ptr4->set_cd(0.71, 0.40, 0.20);   // orange
	
	Plane* leftWall_ptr = new Plane(Point3D(-room_size, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->set_material(matte_ptr4);        
	add_object(leftWall_ptr);
	
	// right wall  (+ve xw)
	
	Plane* rightWall_ptr = new Plane(Point3D(room_size, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->set_material(matte_ptr4);        
	add_object(rightWall_ptr);

	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_ka(0); 
	reflective_ptr1->set_kd(0);
	reflective_ptr1->set_cd(white); 
	reflective_ptr1->set_ks(0);
	reflective_ptr1->set_exp(2000.0);
	reflective_ptr1->set_kr(0.9);
	reflective_ptr1->set_cr(0.9, 1.0, 0.9);  // light green
	
	// back wall mirror  (-ve zw)
	
	double mirror_size 	= 2.75;  	// the mirror size
	double offset 		= 0.25;  // the mirror offset from the walls

	Point3D p0;
	Vector3D a, b;
	
	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Normal n(0, 0, 1);
	Rectangle* rectangle_ptr1 = new Rectangle(p0, a, b, n);
	rectangle_ptr1->set_material(reflective_ptr1); 
	add_object(rectangle_ptr1);
	
	
	// front wall mirror  (+ve zw)
	
	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Normal(0, 0, -1);
	Rectangle* rectangle_ptr2 = new Rectangle(p0, a, b, n);
	rectangle_ptr2->set_material(reflective_ptr1); 
	add_object(rectangle_ptr2);
	
	
	// left wall mirror  (-ve xw)
	
	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Point3D(0, 0, -2.0 * mirror_size);
	n = Normal(1, 0, 0);
	Rectangle* rectangle_ptr3 = new Rectangle(p0, a, b, n);
	rectangle_ptr3->set_material(reflective_ptr1); 
	add_object(rectangle_ptr3);
	
	double yw = -1.0;   // the yw location of the mirror
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.5);
	checker_ptr->set_color1(0.35);
	checker_ptr->set_color2(0.5);
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.75);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(checker_ptr);
	p0 = Point3D(-mirror_size, yw, -mirror_size);
	a = Vector3D(0, 0, 2.0 * mirror_size);
	b = Vector3D(2.0 * mirror_size, 0, 0);
	n = Normal(0, 1, 0);
	Rectangle* rectangle_ptr4 = new Rectangle(p0, a, b, n);
	rectangle_ptr4->set_material(sv_matte_ptr2); 
	add_object(rectangle_ptr4);

	Image* image_ptr = new Image;				
	image_ptr->read_ppm_file("EarthLowRes.ppm");
	// mapping:
	SphericalMap* map_ptr = new SphericalMap; 
	// image based texture:
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	// textured material:
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.2);
	sv_matte_ptr->set_kd(0.8);
	sv_matte_ptr->set_cd(texture_ptr);
	// generic sphere:
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0, 0), 1); 
	sphere_ptr1->set_material(sv_matte_ptr);
	add_object(sphere_ptr1);
	
	double delta = 0; // TODO

	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3); 
	reflective_ptr->set_cd(white); 
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);
	Sphere* sphere_ptr3 = new Sphere(Point3D(1.415 + delta , 0, -1.415 + delta), 1);
	sphere_ptr3->set_material(reflective_ptr);
	add_object(sphere_ptr3);
}

void World::build2(){
	int num_samples = 1; //16
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);		
	vp.set_max_depth(4);//5
	
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.3);
	glass_ptr->set_exp(2000);	
	glass_ptr->set_kr(0.1);
	glass_ptr->set_ior(2);	
	glass_ptr->set_kt(0.8);	
	Sphere* sphere_ptr2 = new Sphere(Point3D(2, 0, 2), 1); 
	sphere_ptr2->set_material(glass_ptr);
	add_object(sphere_ptr2);
	
	background_color = RGBColor(0.0, 0, 0);
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(8, 5, 40);   
	pinhole_ptr->set_lookat(0, 0, -3);    
	pinhole_ptr->set_view_distance(3600.0);  
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 10); 
	light_ptr1->scale_radiance(4.5);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-10, 20, 10); 
	light_ptr2->scale_radiance(4.5);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(-1, 0, 0); 
	light_ptr3->scale_radiance(4.5);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	Image* image_ptr = new Image;				
//	image_ptr->read_ppm_file("EarthHighRes.ppm");
	image_ptr->read_ppm_file("EarthLowRes.ppm");
	// mapping:
	SphericalMap* map_ptr = new SphericalMap; 
	// image based texture:
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	// textured material:
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.2);
	sv_matte_ptr->set_kd(0.8);
	sv_matte_ptr->set_cd(texture_ptr);
	// generic sphere:
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0, 0), 1); 
	sphere_ptr1->set_material(sv_matte_ptr);
	add_object(sphere_ptr1);
	
	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3); 
	reflective_ptr->set_cd(white); 
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);
	Sphere* sphere_ptr3 = new Sphere(Point3D(2 , 0, -2), 1);
	sphere_ptr3->set_material(reflective_ptr);
	add_object(sphere_ptr3);
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.5);
	checker_ptr->set_color1(0.35);
	checker_ptr->set_color2(0.5);
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.75);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(checker_ptr);

	/*Matte* matte_ptr = new Matte;			
	matte_ptr->set_ka(0.15); 
	matte_ptr->set_kd(0.95);	
	matte_ptr->set_cd(1, 1, 1);     
	matte_ptr->set_sampler(new MultiJittered(num_samples));*/
	Point3D p0(-20, -1, -60);
	Vector3D a(0, 0, 120);
	Vector3D b(40, 0, 0);
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
	rectangle_ptr->set_material(sv_matte_ptr2);
	add_object(rectangle_ptr);	
}

void World::build3(){
	int num_samples = 1;   	//100
	
	Sampler* sampler_ptr = new MultiJittered(num_samples);

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_sampler(sampler_ptr);	

	background_color = RGBColor(0.5);

	tracer_ptr = new AreaLighting(this);

	Pinhole* camera = new Pinhole;
	camera->set_eye(-20, 10, 20);
	camera->set_lookat(0, 2, 0); 	
	camera->set_view_distance(1080);          
	camera->compute_uvw();     
	set_camera(camera); 

	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);
	emissive_ptr->set_ce(white);
	float width = 4.0;				// for Figure 18.4(a) & (b)
	float height = 4.0;
//	float width = 2.0;				// for Figure 18.4(c)
//	float height = 2.0;
	Point3D center(0.0, 7.0, -7.0);	// center of each area light (rectangular, disk, and spherical)
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(sampler_ptr);
	//rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);
	
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.1); 
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(white);
		
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);	
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.45); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.75, 0.25, 0);   // orange
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(0, 1, 0), 1);
	sphere_ptr2->set_material(matte_ptr1);      
	add_object(sphere_ptr2);
}

ShadeRec									
World::hit_objects(const Ray& ray) {

	ShadeRec	sr(*this); 
	double		t;
	Normal		normal;
	Point3D		local_hit_point;
	double		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material_ptr     = objects[j]->get_material();
			
			sr.hit_point 		= ray.o + t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}
  
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return(sr);   
}

// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	double max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB doubleing point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still doubleing point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color, cv::Mat &img) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;
   
   circle(img, cv::Point(x, y), 1, cv::Scalar(int(mapped_color.b * 255), int(mapped_color.g * 255), int(mapped_color.r * 255)));
}



//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}


//------------------------------------------------------------------ delete_lights

void
World::delete_lights(void) {
	int num_lights = lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}
	
	lights.erase (lights.begin(), lights.end());
}