
#include <algorithm>   // for random_shuffle in Sampler::setup_shuffled_indices
#include <ctime>
#include "Constants.h"
#include "Sampler.h"

// ------------------------------------------------------------------ default constructor
	
Sampler::Sampler(void)						
	: 	num_samples(1),
		num_sets(83),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}


// ------------------------------------------------------------------ constructor

Sampler::Sampler(const int ns)
	: 	num_samples(ns),
		num_sets(83),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}


// ------------------------------------------------------------------ constructor

Sampler::Sampler(const int ns, const int n_sets)
	: 	num_samples(ns),
		num_sets(n_sets),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}


// ------------------------------------------------------------------ copy constructor

Sampler::Sampler(const Sampler& s)				
	: 	num_samples(s.num_samples),
		num_sets(s.num_sets),
		samples(s.samples),
		shuffled_indices(s.shuffled_indices),
		disk_samples(s.disk_samples),
		hemisphere_samples(s.hemisphere_samples),
		sphere_samples(s.sphere_samples),
		count(s.count),
		jump(s.jump)
{}


// ------------------------------------------------------------------ assignment operator

Sampler& 
Sampler::operator= (const Sampler& rhs)	{
	if (this == &rhs)
		return (*this);
	
	num_samples 		= rhs.num_samples;
	num_sets			= rhs.num_sets;
	samples				= rhs.samples;
	shuffled_indices	= rhs.shuffled_indices;
	disk_samples		= rhs.disk_samples;
	hemisphere_samples	= rhs.hemisphere_samples;
	sphere_samples		= rhs.sphere_samples;
	count				= rhs.count;
	jump				= rhs.jump;
	
	return (*this);
}

Sampler::~Sampler(void) {}


// ------------------------------------------------------------------- set_num_sets

void
Sampler::set_num_sets(const int np) {
	num_sets = np;
}


// ------------------------------------------------------------------- get_num_samples

int
Sampler::get_num_samples(void) {
	return (num_samples);
}


// ------------------------------------------------------------------- shuffle_x_coordinates
// shuffle the x coordinates of the points within each set

void
Sampler::shuffle_x_coordinates(void) {
	srand((unsigned)time(0));
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i <  num_samples - 1; i++) {
			int target = rand() % num_samples + p * num_samples;
			double temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}


// ------------------------------------------------------------------- shuffle_y_coordinates
// shuffle the y coordinates of the points within set

void
Sampler::shuffle_y_coordinates(void) {
	srand((unsigned)time(0));
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i <  num_samples - 1; i++) {
			int target = rand() % num_samples + p * num_samples;
			double temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}	
}


// ------------------------------------------------------------------- setup_shuffled_indices
// sets up randomly shuffled indices for the samples array

void											
Sampler::setup_shuffled_indices(void) {
	shuffled_indices.reserve(num_samples * num_sets);
	vector<int> indices;
	
	for (int j = 0; j < num_samples; j++)
		indices.push_back(j);
	
	for (int p = 0; p < num_sets; p++) { 
		random_shuffle(indices.begin(), indices.end());	
		
		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);
	}	
}


// ------------------------------------------------------------------- map_samples_to_unit_disk

// Maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk, using Peter Shirley's
// concentric map function

void
Sampler::map_samples_to_unit_disk(void) {
	int size = samples.size();
	double r, phi;		// polar coordinates
	Point2D sp; 		// sample point on unit disk
	
	disk_samples.reserve(size);
		
	for (int j = 0; j < size; j++) {
		 // map sample point to [-1, 1] X [-1,1]
		 	
		sp.x = 2.0 * samples[j].x - 1.0;	
		sp.y = 2.0 * samples[j].y - 1.0;
			
		if (sp.x > -sp.y) {			// sectors 1 and 2
			if (sp.x > sp.y) {		// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {					// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {						// sectors 3 and 4
			if (sp.x < sp.y) {		// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {					// sector 4
				r = -sp.y;
				if (sp.y != 0.0)	// avoid division by zero at origin
					phi = 6 - sp.x / sp.y;
				else
					phi  = 0.0;
			}
		}
		
		phi *= PI / 4.0;
				
		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}
	
	samples.erase(samples.begin(), samples.end());
}


// ------------------------------------------------------------------- map_samples_to_hemisphere

// Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power
// density distribution in the polar angle

void
Sampler::map_samples_to_hemisphere(const double exp) {
	int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);
		
	for (int j = 0; j < size; j++) {
		double cos_phi = cos(2.0 * PI * samples[j].x);
		double sin_phi = sin(2.0 * PI * samples[j].x);	
		double cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
		double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		double pu = sin_theta * cos_phi;
		double pv = sin_theta * sin_phi;
		double pw = cos_theta;
		hemisphere_samples.push_back(Point3D(pu, pv, pw)); 
	}
}


// ------------------------------------------------------------------- map_samples_to_sphere

// Maps the 2D sample points to 3D points on a unit sphere with a uniform density 
// distribution over the surface
// this is used for modelling a spherical light

void
Sampler::map_samples_to_sphere(void) {
	double r1, r2;
	double x, y, z;
	double r, phi;
		
	sphere_samples.reserve(num_samples * num_sets);   
		
	for (int j = 0; j < num_samples * num_sets; j++) {
		r1 	= samples[j].x;
    	r2 	= samples[j].y;
    	z 	= 1.0 - 2.0 * r1;
    	r 	= sqrt(1.0 - z * z);
    	phi = TWO_PI * r2;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
		sphere_samples.push_back(Point3D(x, y, z)); 
	}
}


// ------------------------------------------------------------------- sample_unit_square
// the final version in Listing 5.13

Point2D
Sampler::sample_unit_square(void) {
	srand((unsigned)time(0));
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;				// random index jump initialised to zero in constructor

	return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);  
}




/*

// ------------------------------------------------------------------- sample_unit_square
// the first revised version in Listing in Listing 5.8

Point2D
Sampler::sample_unit_square(void) {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;				// random index jump initialised to zero in constructor
	
	return (samples[jump + count++ % num_samples]);	
}

*/



/*

// ------------------------------------------------------------------- sample_unit_square
// the original version in Listing 5.7

Point2D
Sampler::sample_unit_square(void) {
	return (samples[count++ % (num_samples * num_sets)]);
}

*/



// ------------------------------------------------------------------- sample_unit_disk

Point2D
Sampler::sample_unit_disk(void) {
	srand((unsigned)time(0));
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;
	
	return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}



// ------------------------------------------------------------------- sample_hemisphere

Point3D
Sampler::sample_hemisphere(void) {
	srand((unsigned)time(0));
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;
		
	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);		
}



// ------------------------------------------------------------------- sample_sphere

Point3D
Sampler::sample_sphere(void) {
	srand((unsigned)time(0));
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;
		
	return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);		
}



// ------------------------------------------------------------------- sample_one_set
// This is a specialised function called in LatticeNoise::init_vector_table
// It doesn't shuffle the indices

Point2D
Sampler::sample_one_set(void) {
	return(samples[count++ % num_samples]);  
}