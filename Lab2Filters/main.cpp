#include <iostream>
#include <opencv2/opencv.hpp>
#include "Header.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat A, B;
	A = imread(argv[1]);
	cvtColor(A, A, COLOR_RGB2GRAY);
	imshow("A", A);
	//B = MedianFilter(A);
	B = Average(A);
	imshow("B", B);
	waitKey(0);
}