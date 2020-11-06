#include <ctime>
#include <cmath>
#include <random>
#include "Noise.h"

using namespace cv;

Mat Gaussian_noise(const Mat& image)
{
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<> uid(0, image.rows * image.cols);
	Mat resimg = image.clone();
	cvtColor(resimg, resimg, COLOR_BGR2GRAY);
	int count = int(image.rows * image.cols * 0.2);
	for (int i = 0; i < count; i++)
	{
		int ran = uid(gen);
		int x = ran / image.cols;
		int y = ran - x * image.cols;

		resimg.at<uchar>(x, y) = saturate_cast<uchar>(resimg.at<uchar>(x, y) + genGaussian_noise(0, 255));
	}
	return resimg;
};

int genGaussian_noise(int a, int b)
{
	float mu = 0;
	double x = (rand() % 1000) / 999.0;
	float sigma = 1;
	int pi = 3;
	double sdvig = 1 / sqrt(2 * pi * sigma * sigma) * exp(((-1) * (x - mu) * (x - mu)) / (2 * sigma * sigma));
	sdvig = sdvig * (b - a) + a;
	return int(sdvig);
};

Mat Average(const cv::Mat& image)
{
	Mat copy = image.clone();
	cvtColor(copy, copy, COLOR_BGR2GRAY);
	int mRadius = 1;
	int size = 2 * mRadius + 1;
	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			int sum = 0;
			for (int i = -mRadius; i <= mRadius; i++)
				for (int j = -mRadius; j <= mRadius; j++)
				{
					int idx = (i + mRadius) * size + j + mRadius;
					int z = clamp<int>(x + j, copy.cols - 1, 0);
					int q = clamp<int>(y + i, copy.rows - 1, 0);
					sum += copy.at<uchar>(q, z);
				}
			copy.at<uchar>(y, x) = sum / (size * size);
		}
	return copy;
};

Mat MedianFilter(const Mat& image)
{
	Mat copy = image.clone();
	cvtColor(copy, copy, COLOR_BGR2GRAY);
	int mRadius = 1;
	int size = 2 * mRadius + 1;
	std::vector<int> vector(size * size);
	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			for (int i = -mRadius; i <= mRadius; i++)
				for (int j = -mRadius; j <= mRadius; j++)
				{
					int idx = (i + mRadius) * size + j + mRadius;
					int z = clamp<int>(x + j, copy.cols - 1, 0);
					int q = clamp<int>(y + i, copy.rows - 1, 0);
					vector[idx] = copy.at<uchar>(q, z);
				}
			sort(vector.begin(), vector.end());
			copy.at<uchar>(y, x) = vector[4];
		}
	return copy;
};