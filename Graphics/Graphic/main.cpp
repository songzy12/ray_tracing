#include "World.h"
using namespace cv;

int main(){
	World w;
	w.build1();// for mirror
	//w.build2();// for grid
	//w.build3();// for area_shade
	std::cout<<"Build finished."<<std::endl;
	/// Windows names  
	char RT_window[] = "Ray Trace";  
	/// Create black empty images   
	Mat RT_image = Mat::zeros( w.vp.vres, w.vp.hres, CV_8UC3 );
	
	clock_t start=clock();
	circle(RT_image, Point(30, 30), 1, Scalar(255,255,0));
	
	w.camera_ptr->render_scene(w, RT_image);
	
	std::cout<<"Render finished."<<std::endl;
	clock_t finish=clock();
	double totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	std::cout<<totaltime<<" seconds elapsed."<<std::endl;

	imshow( RT_window, RT_image );  
	imwrite("../ray_trace.bmp", RT_image);
	std::cout<<"Write finished."<<std::endl;
	waitKey(0);
	return 0;
}