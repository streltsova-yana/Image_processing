#include <math.h>
#include "Canny.h"
#include "Watersheds.h"

using namespace cv;
using namespace std;


int main()
{
	//Canny
	Mat img = imread("1.jpg", IMREAD_COLOR);
	Mat resimg = Mat::zeros(Size(img.cols, img.rows), CV_8UC1);
	resimg = Canny(img);
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