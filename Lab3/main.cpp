#include <math.h>
#include "Canny.h"
#include "Watersheds.h"
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;


int main()
{
	//Canny
	Mat img = imread("1.jpg", IMREAD_COLOR);
	Mat resimg = Mat::zeros(Size(img.cols, img.rows), CV_8UC1);
	Mat resimg2;

	clock_t start = clock();
	resimg = Canny(img);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << " Our Canny= " << seconds << " seconds" << endl;

	clock_t start2 = clock();
	Canny(img, resimg2, 80, 0);
	clock_t end2 = clock();
	double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	cout << " OpenCV Canny= " << seconds2 << " seconds" << endl;

	imshow("Display Image", img);
	imshow("Display Canny", resimg);

	//Watershed
	img = imread("2.jpeg", 1);
	resize(img, img, Size(300, 300), 0, 0, INTER_LINEAR);
	imshow("Original", img);
	Mat dst = Watershed(img, 110);
	resize(dst, dst, Size(300, 300), 0, 0, INTER_LINEAR);
	imshow("Watershed", dst);

	waitKey(0);

	return 0;
}