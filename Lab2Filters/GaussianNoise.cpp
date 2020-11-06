#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>
#include <algorithm>
#include "GaussianNoise.h"

using namespace cv;
using namespace std;

Mat Gaussian_noise(const Mat& image)
{
	std::mt19937 gen(time(0)); 
	std::uniform_int_distribution<> uid(0, 78400);
	Mat resimg = image.clone();
	int count = int(image.rows * image.cols * 0.2);
	for (int i = 0; i < count; i++)
	{
		int ran = uid(gen);
		int x = ran / image.cols;
		int y = ran - x * image.cols;

		resimg.at<uchar>(x, y) = saturate_cast<uchar>(resimg.at<uchar>(x, y) + genGaussian_noise(0, 255));
	}
	return resimg;
}

int genGaussian_noise( int a, int b)
{
	float mu = 0;
	double x = (rand() % 1000) / 999.0;
	float sigma = 1;
	int pi = 3;
	double sdvig = 1 / sqrt(2*pi*sigma*sigma) * exp(((-1)*(x - mu) * (x - mu)) / (2*sigma*sigma));
	sdvig = sdvig * (b - a) + a;
	return int(sdvig);
}
