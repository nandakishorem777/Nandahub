// CamCapture_DownSample.cpp : Defines the entry point for the console application.
//

/*
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

IplImage* doPyrDown(IplImage*, int);
int main()
{

	int count = 0;
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Size S = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	//int ex = (cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type


	VideoWriter outputVideo("test_folder/Input.avi", CV_FOURCC('D', 'I', 'V', '3'), 10.0, S, true);
	VideoWriter outputVideo1("test_folder/Down_Sampled.avi", CV_FOURCC('D', 'I', 'V', '3'), 10.0, S/2, true);

	if (!outputVideo.isOpened())
	{
		cout << "Could not open the output video for write: " << endl;
		return -1;
	}

	cvNamedWindow("Downsampled");
	while (1) {
		Mat frame;
		cap >> frame;
		IplImage* Image1 = cvCloneImage(&(IplImage)frame);
		IplImage* down_samp = doPyrDown(Image1, 7);
		cvShowImage("Downsampled", down_samp);
		outputVideo.write(frame);
		//	putText(frame, "Press ESC to stop", Point(0, 100), 1, 1, Scalar(255, 0, 255), 2);
		imshow("Record", frame);
		char filename[80];
		sprintf(filename, "test_folder/down_samp_%d.jpg", count);
		cv::Mat Down_samp = cv::cvarrToMat(down_samp);
		cvSaveImage(filename, down_samp);
		outputVideo1.write(Down_samp);


		count++;
		char S = (char)waitKey(33);
		if (S == 27) break;
	}

	return 0;

}
IplImage* doPyrDown(IplImage* Image1, int filter = CV_GAUSSIAN_5x5)
{
	assert(Image1->width % 2 == 0 && Image1->height % 2 == 0);

	IplImage* out1 = cvCreateImage(cvSize(Image1->width / 2, Image1->height / 2), Image1->depth, Image1->nChannels);

	cvPyrDown(Image1, out1);
	return(out1);
}
*/

// CamCapture_DownSample.cpp : Defines the entry point for the console application.
//


#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

IplImage* doPyrDown(IplImage*, int);
int main()
{

	int count = 0;
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Size S = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	//int ex = (cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type


	VideoWriter outputVideo("test_folder/Input.avi", CV_FOURCC('D', 'I', 'V', '3'), 10.0, S, true);
	VideoWriter outputVideo1("test_folder/Down_Sampled.avi", CV_FOURCC('D', 'I', 'V', '3'), 10.0, S / 2, true);

	if (!outputVideo.isOpened())
	{
		cout << "Could not open the output video for write: " << endl;
		return -1;
	}

	cvNamedWindow("Downsampled");
	while (1) {
		Mat frame;
		cap >> frame;
		IplImage* Image1 = cvCloneImage(&(IplImage)frame);
		IplImage* down_samp = doPyrDown(Image1, 7);
		cvShowImage("Downsampled", down_samp);
		outputVideo.write(frame);
		//	putText(frame, "Press ESC to stop", Point(0, 100), 1, 1, Scalar(255, 0, 255), 2);
		imshow("Record", frame);
		char filename[80];
		sprintf(filename, "test_folder/down_samp_%d.jpg", count);
		cv::Mat Down_samp = cv::cvarrToMat(down_samp);
		cvSaveImage(filename, down_samp);
		outputVideo1.write(Down_samp);


		count++;
		char S = (char)waitKey(33);
		if (S == 27) break;
	}

	return 0;

}
IplImage* doPyrDown(IplImage* Image1, int filter = CV_GAUSSIAN_5x5)
{
	assert(Image1->width % 2 == 0 && Image1->height % 2 == 0);

	IplImage* out1 = cvCreateImage(cvSize(Image1->width / 2, Image1->height / 2), Image1->depth, Image1->nChannels);

	cvPyrDown(Image1, out1);
	return(out1);
}



