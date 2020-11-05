#ifndef HEADER_H
#define HEADER_H
#include <opencv2/opencv.hpp>
cv::Mat GaussianFilter(const cv::Mat&);
cv::Mat MedianFilter(const cv::Mat&);
cv::Mat Average(const cv::Mat&);
template<typename T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}
#endif
