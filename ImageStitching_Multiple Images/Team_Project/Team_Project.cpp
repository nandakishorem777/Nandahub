
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
void readme();


	int main(int argc, char** argv) {
		int i = 1,j=0,k=2;
		char name[20], name1[20], name2[20], name3[30];
	while (i<4)
		{
			//for gray scale images:
			sprintf_s(name, "mymainpic%d.jpg", i);
			Mat img1 = imread(name);
			cvtColor(img1, img1, cv::COLOR_RGB2GRAY);
			sprintf_s(name1, "Input_%d.jpg", i);
			imshow(name1, img1);
			sprintf_s(name1, "mymainpic%d.jpg", i+1);
			Mat img2 = imread(name1);
			cvtColor(img2, img2, cv::COLOR_RGB2GRAY);
			sprintf_s(name2, "Input_%d.jpg", i+1);
			imshow(name2, img2);
			//for color images:
			//Mat img = imread("lena.bmp");
			Mat gray_1,gray_2;
			// converting from color to grayscale:
			// cvtColor(img,gray,COLOR_BGR2GRAY);
			int minHessian = 400;
			//Creating a feature vector that calculates SURF Features using xfeatures2d 
		Ptr<Feature2D> f2d = xfeatures2d::SURF::create(minHessian);
			gray_1 = img1;
			gray_2 = img2;
			std::vector<KeyPoint> keypoints_1;
			f2d->detect(gray_1, keypoints_1);
			std::vector<KeyPoint> keypoints_2;
			f2d->detect(gray_2, keypoints_2);
			Mat descriptors_1,descriptors_2;
			f2d->compute(gray_1, keypoints_1, descriptors_1);
			f2d->compute(gray_2, keypoints_2, descriptors_2);
			Mat img_keypoints_1,img_keypoints_2;
			//Drawing the SURF keypoints on both the images
			drawKeypoints(gray_1, keypoints_1, img_keypoints_1, Scalar::all(-1),
				cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
			imshow("surf_1", img_keypoints_1);
			imwrite("SURF1.jpg", img_keypoints_1);
			drawKeypoints(gray_2, keypoints_2, img_keypoints_2, Scalar::all(-1),
				cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
			imshow("surf_2", img_keypoints_2);
			imwrite("SURF2.jpg", img_keypoints_2);
			//Initializing object to perform flann based matching between obtained keypoints
			FlannBasedMatcher matcher;
			std::vector< DMatch > matches;
			matcher.match(descriptors_2, descriptors_1, matches);

			double max_dist = 0; double min_dist = 100;

			//-- Quick calculation of max and min distances between keypoints
			for (int i = 0; i < descriptors_2.rows; i++)
			{
				double dist = matches[i].distance;
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
			}

			printf("-- Max dist : %f \n", max_dist);
			printf("-- Min dist : %f \n", min_dist);

			//Intention is to Use only "good" matches (i.e. whose distance is less than 3*min_dist )
			std::vector< DMatch > good_matches;

			for (int i = 0; i < descriptors_2.rows; i++)
			{
				if (matches[i].distance < 3 * min_dist)
				{
					good_matches.push_back(matches[i]);
				}
			}
			std::vector< Point2f > obj;
			std::vector< Point2f > scene;

			for (int i = 0; i < good_matches.size(); i++)
			{
				//-- Get the keypoints from the good matches
				obj.push_back(keypoints_2[good_matches[i].queryIdx].pt);
				scene.push_back(keypoints_1[good_matches[i].trainIdx].pt);
			}


		std::vector<cv::KeyPoint> keypointsA, keypointsB;
			cv::Mat descriptorsA, descriptorsB, img_keypoints_A,img_keypoints_B;
			Mat gray_A = img1;
			Mat gray_B = img2;

			//declaring a variable BRISKD of the type cv::BRISK
			cv::Ptr<cv::BRISK> BRISKD = cv::BRISK::create();


			BRISKD->detect(gray_A, keypointsA);
			BRISKD->compute(gray_A, keypointsA, descriptorsA);

			BRISKD->detect(gray_B, keypointsB);
			BRISKD->compute(gray_B, keypointsB, descriptorsB);
			//Drawing the Brisk features on the images
			drawKeypoints(gray_A, keypointsA, img_keypoints_A, Scalar::all(-1),
				cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
			imshow("Brisk_1", img_keypoints_A);
			imwrite("Brisk1.jpg", img_keypoints_A);
			drawKeypoints(gray_B, keypointsB, img_keypoints_B, Scalar::all(-1),
				cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
				imshow("Brisk_2",img_keypoints_B);
				imwrite("Brisk2.jpg", img_keypoints_B);
				//Initializng the flann based matcher for brisk
			FlannBasedMatcher matcher(new cv::flann::LshIndexParams(20, 10, 2));
			std::vector< DMatch > matches;
			matcher.match(descriptorsB, descriptorsA, matches);

			double max_dist = 0; double min_dist = 100;

			//-- Quick calculation of max and min distances between keypoints
			for (int i = 0; i < descriptorsB.rows; i++)
			{
				double dist = matches[i].distance;
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
			}

			printf("-- Max dist : %f \n", max_dist);
			printf("-- Min dist : %f \n", min_dist);

			//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
			std::vector< DMatch > good_matches;

			for (int i = 0; i < descriptorsB.rows; i++)
			{
				if (matches[i].distance < 3 * min_dist)
				{
					good_matches.push_back(matches[i]);
				}
			}
			std::vector< Point2f > obj;
			std::vector< Point2f > scene;

			for (int i = 0; i < good_matches.size(); i++)
			{
				//-- Get the keypoints from the good matches
				obj.push_back(keypointsB[good_matches[i].queryIdx].pt);
				scene.push_back(keypointsA[good_matches[i].trainIdx].pt);
			}



			// Find the Homography Matrix
			Mat H = findHomography(obj, scene, CV_RANSAC);
			// Use the Homography Matrix to warp the images
			cv::Mat result,result1;
			//Warping of one image on to the other
			warpPerspective(img2, result, H, cv::Size(img1.cols + img2.cols, img2.rows));
			cv::Mat half(result, cv::Rect(0, 0, img1.cols, img1.rows));
			img1.copyTo(half);
			cvNamedWindow("Result", WINDOW_AUTOSIZE);
			imshow("Result", result);
			sprintf_s(name3, "panorama_of_%d_images.jpg",k);
			imwrite(name3, result);

			
			Mat croppedImage;
			i = i + 2; 
			float sum_c;
			
			//Cropping the images to remove the black strip of pixels that is obtained 
			//due to overlapping during stitching process
				for (j = 0; j <= result.cols; j++)
				{
					sum_c = countNonZero(result.col(j));
					if (sum_c <= 0)
					{
						break;
					}
				}
				//Dsiplaying and saving the results
				cv::Mat ROI(result, cv::Rect(0, 0, j-5, 600));
				ROI.copyTo(croppedImage);
				imshow("Result1", croppedImage);
				if (i == 3)
				{
					sprintf_s(name2, "mymainpic.jpg", i);
					imwrite(name2, croppedImage);
					waitKey(0);
					cvDestroyWindow("Result");
				}
				if (i == 5)
				{
					sprintf_s(name2, "mymainpic%d.jpg", i);
					imwrite(name2, croppedImage);
				}
			k = k + 1;
		}	
		waitKey(0);
		return 0;
}

/*@function readme */
void readme()
{
	std::cout << " Usage: Panorama < img1 > < img2 >" << std::endl;
}

/*
void main()
{
	Mat img1 = imread("panorama_image1.jpg", IMREAD_GRAYSCALE);
	imshow("Input_1", img1);
	Mat img2 = imread("panorama_image2.jpg", IMREAD_GRAYSCALE);
	imshow("Input_2", img2);
	std::vector<cv::KeyPoint> keypointsA, keypointsB;
	cv::Mat descriptorsA, descriptorsB;
	Mat gray_A = img1;
	Mat gray_B = img2;

/*	int Threshl = 60;
	int Thresh = 40;
	int Octaves = 4; 
    float PatternScales = 1.0f;
					 //static Ptr<BRISK> create(int thresh = 30, int octaves = 3, float patternScale = 1.0f);

					// BRISK BRISKD(int Thresh=60,int Octaves=4,float PatternScales=1.0f); //initialize algoritm
					
	cv::Ptr<cv::BRISK> BRISKD = cv::BRISK::create();
	

					 BRISKD->detect(gray_A, keypointsA);
					 BRISKD->compute(gray_A, keypointsA, descriptorsA);

					 BRISKD->detect(gray_B, keypointsB);
					 BRISKD->compute(gray_B, keypointsB, descriptorsB);
}*/

