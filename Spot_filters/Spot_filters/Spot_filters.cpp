#include <iostream>
#include <time.h> 
#include "Metric.h"
#include "Grayscale.h"
#include "Converting.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3) {
		cout << "Not enough command line arguments" << endl;
		return -1;
	}
	
	Mat A, B, C; //Loading images
	A = imread(argv[1]);
	B = imread(argv[2]);
	imshow("A", A);
	imshow("B", B);
	if ((!A.data) || (!B.data)) {
		cout << "No image data" << endl;
		return -1;
	}

	/************Test Metric************/
	resize(B, C, A.size()); //Resize picture B to size A
	try {
		float metric1 = ssim(A, C); //SSIM calculation
		float metric2 = ssim(A, A);
		cout << "SSIM between A and B = " << metric1 << endl;
		cout << "SSIM between A and A = " << metric2 << endl;
	}
	catch (const char* message) {
		cout << message;
	}

	/************Test Grayscale************/
	Mat resimg_gray1 = A.clone();
	resimg_gray1 = gray_scale(A);
	imshow("Grayscale_A", resimg_gray1);

	Mat resimg_gray2 = A.clone();
	cvtColor(resimg_gray2, resimg_gray2, COLOR_RGB2GRAY);
	imshow("Grayscale_A_using OpenCV", resimg_gray2);

	/************Test Brightness************/
	Mat resimg_br1 = A.clone();
	clock_t start = clock();
	resimg_br1 = brightness_rgb(A);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Brightness_RGB = " << seconds << " seconds" << endl;
	imshow("Brightness_RGB", resimg_br1);

	Mat resimg_br2 = A.clone();
	start = clock();
	resimg_br2 = brightness_hsv(A);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Brightness_HSV = " << seconds << " seconds" << endl;
	imshow("Brightness_HSV", resimg_br2);

	try {
		float metric = ssim(resimg_br1, resimg_br2); //SSIM calculation
		cout << "SSIM between Brightness_RGB and Brightness_HSV = " << metric << endl;
	}
	catch (const char* message) {
		cout << message;
	}
	
	/************Test Converting************/
	Mat hsv1;
	try {
		hsv1 = bgr2hsv(A);
	}
	catch (const char* message) {
		cout << message;
	}
	imshow("BGR2HSV_ A", hsv1);

	Mat hsv2;
	cvtColor(A, hsv2, COLOR_BGR2HSV);
	imshow("BGR2HSV_A_using OpenCV", hsv2);

	Mat bgr1;
	try {
		bgr1 = hsv2bgr(hsv1);
	}
	catch (const char* message) {
		cout << message;
	}
	imshow("HSV2BGR_A", bgr1);

	Mat bgr2;
	cvtColor(hsv2, bgr2, COLOR_HSV2BGR);
	imshow("HSV2BGR_A_using OpenCV", bgr2);
	
	waitKey(0);
	return 0;
}