#include <opencv2/imgproc.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include "Canny.h"
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat img = imread("kr.jpg", IMREAD_COLOR);

	Mat resimg = Mat::zeros(Size(img.cols, img.rows), CV_8UC1);
	resimg = Canny(img);
	imshow("Display Canny", resimg);

	waitKey(0);

	return 0;
}