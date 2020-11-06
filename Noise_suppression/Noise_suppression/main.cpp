#include <iostream>
#include <time.h> 
#include "Noise.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3) {
		cout << "Not enough command line arguments" << endl;
		return -1;
	}

	Mat A = imread(argv[1]);
	Mat B = imread(argv[2]);
	if ((!A.data) || (!B.data)) {
		cout << "No image data" << endl;
		return -1;
	}

	/************Test Gaussian_noise************/
	imshow("Original_A", A);
	Mat C = Gaussian_noise(A);
	imshow("Gaussian_noise", C);


	imshow("Original_B", B);
	/************Test Averaging Filter************/
	clock_t start = clock();
	Mat D = Average(B);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Averaging Filter = " << seconds << " seconds" << endl;
	imshow("Averaging Filter", D);

	/************Test Median Filter************/
	start = clock();
	Mat E = MedianFilter(B);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Median Filter = " << seconds << " seconds" << endl;
	imshow("Median Filter", E);

	/************Test Median Filter OpenCV************/
	Mat F;
	start = clock();
	medianBlur(B, F, 3);
	cvtColor(F, F, COLOR_BGR2GRAY);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Median Filter OpenCV = " << seconds << " seconds" << endl;
	imshow("Median Filter OpenCV", F);

	waitKey(0);
}


