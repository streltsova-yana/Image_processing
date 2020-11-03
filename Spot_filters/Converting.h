#ifndef CONVERTING_H
#define CONVERTING_H
#include <opencv2/opencv.hpp>

cv::Mat brightness_rgb(const cv::Mat&);
cv::Mat brightness_hsv(const cv::Mat&);

cv::Mat bgr2hsv(const cv::Mat& _bgr);
cv::Mat hsv2bgr(const cv::Mat& _hsv);

#endif
