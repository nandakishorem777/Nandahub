// DFT_DCT_NandaKishore.cpp : Defines the entry point for the console application.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>

using namespace std;
using namespace cv;
int main()
{


	Mat img = imread("zebras.jpg", 0);
	//show the image
	imshow("Original Image", img);

	int rows_input = img.rows;
	int cols_input = img.cols;
	Mat dftInput, dftImage, dctImage, inverseDFT, inverseDCT, inverseDFT_Trunc, inverseDCT_Trunc;
	img.convertTo(dftInput, CV_32F);
	dft(dftInput, dftImage, DFT_REAL_OUTPUT);                // Applying DFT
	idft(dftImage, inverseDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT without Truncation
	inverseDFT.convertTo(inverseDFT, CV_8U);
	imshow("IDFT Reconstructed", inverseDFT);     //Display Reconstructed Image with no Truncation
	imwrite("IDFT without Trunc.jpg", inverseDFT);

	int Lmin_DFT = 47;
	int i = 0;
    int j = 0;
	for (i = Lmin_DFT; i <= (rows_input - Lmin_DFT + 1); i++)
	{
		for (j = Lmin_DFT; j <= (cols_input - Lmin_DFT + 1); j++)
		{
			 dftImage.at<float>(i,j) = 0;
		}

	}
													 
	idft(dftImage, inverseDFT_Trunc, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT with Truncation
	inverseDFT_Trunc.convertTo(inverseDFT_Trunc, CV_8U);
	
	imshow("DFT_Image", dftImage);
	

	char file[80];
	sprintf(file, "LminDFT=%d_Output", Lmin_DFT); 
	imshow(file, inverseDFT_Trunc); //Display Truncated IDFT Image
	sprintf(file, "LminDFT=%d_Output.jpg", Lmin_DFT); 
	imwrite(file, inverseDFT_Trunc);//Save Truncated IDFT Image


	
	dct(dftInput, dctImage);  //Applying DCT
	idct(dctImage, inverseDCT);              //IDCT Without Truncation
	inverseDCT.convertTo(inverseDCT, CV_8U);
	imshow("IDCT Reconstructed", inverseDCT);//Display Reconstructed with no Truncation
	imwrite("IDCT without Trunc.jpg", inverseDCT);

	int LminDCT = 65;
	for (i=LminDCT;i<=rows_input-1;i++)
	{ 
		for (j = LminDCT; j <= cols_input - 1; j++)
		{
			dctImage.at<float>(i, j) = 0;
		}
	}
	imshow("DCT_Image ", dctImage);
	idct(dctImage, inverseDCT_Trunc);
	inverseDCT_Trunc.convertTo(inverseDCT_Trunc, CV_8U);

	char file1[80];
	sprintf(file1, "LminDCT = %d_Output", LminDCT);
	imshow(file1, inverseDCT_Trunc);
	sprintf(file1, "LminDCT = %d_Output.jpg", LminDCT);
	imwrite(file1, inverseDCT_Trunc);
	
	
	// Wait until user press some key
	char c=(char)waitKey(0);
	if (c == 27)
		return -1; //Press ESC to stop debugging
		
	return 0;

}

