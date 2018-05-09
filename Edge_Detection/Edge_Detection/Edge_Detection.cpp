// Edge_Detection.cpp : Defines the entry point for the console application.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"



using namespace cv;
using namespace std;

int main()
{
	IplImage* Image1 = cvLoadImage("bird.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cvNamedWindow("Input1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Input1", Image1);

	//Canny Operator
	IplImage* output_canny = cvCreateImage(cvGetSize(Image1), IPL_DEPTH_8U, 1);
	cvCanny(Image1, output_canny, 30, 70, 3);
	cvNamedWindow("Output_Canny", CV_WINDOW_AUTOSIZE);
	cvShowImage("Output_Canny", output_canny);
	cvSaveImage("Edgeimg/canny.jpg", output_canny);

	//Laplacian Operator
	IplImage* output_Laplace = cvCreateImage(cvGetSize(Image1), IPL_DEPTH_8U, 1);
	cvLaplace(Image1, output_Laplace, 3);
	cvNamedWindow("Output_Laplace", CV_WINDOW_AUTOSIZE);
	cvShowImage("Output_Laplace", output_Laplace);
	cvSaveImage("Edgeimg/Laplace.jpg", output_Laplace);

	//Sobel Operator
	IplImage* output_Sobel = cvCreateImage(cvGetSize(Image1), IPL_DEPTH_8U, 1);
	cvSobel(Image1, output_Sobel, 1, 0, 3);
	cvNamedWindow("Output_Sobel", CV_WINDOW_AUTOSIZE);
	cvShowImage("Output_Sobel", output_Sobel);
	cvSaveImage("Edgeimg/Sobel.jpg", output_Sobel);


	cvWaitKey(0);

	cvReleaseImage(&Image1);
	cvReleaseImage(&output_canny);
	cvDestroyWindow("Output_Canny");
	cvReleaseImage(&output_Laplace);
	cvDestroyWindow("Output_Laplace");
	cvReleaseImage(&output_Sobel);
	cvDestroyWindow("Output_Sobel");

	return 0;

}