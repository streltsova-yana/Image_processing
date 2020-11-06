#ifndef NOISE_H
#define NOISE_H
#include <opencv2/opencv.hpp>

template<typename T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
};
cv::Mat Gaussian_noise(const cv::Mat&);
int genGaussian_noise(int a, int b);
cv::Mat Average(const cv::Mat&);
cv::Mat MedianFilter(const cv::Mat&);

#endif
