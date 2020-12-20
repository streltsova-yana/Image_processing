#ifndef WATERSHED_H
#define WATERSHED_H

#include <opencv2\highgui.hpp>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc.hpp>
#include<iostream>

void threshold_image(cv::Mat& src, int thresh);
cv::Mat LBP(const cv::Mat& src);
cv::Mat Watershed(const cv::Mat& src, int thresh);

#endif