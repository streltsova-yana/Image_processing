#ifndef CANNY_H
#define CANNY_H

#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>

int Sobelx(const cv::Mat&, int, int);
int Sobely(const cv::Mat&, int, int);
int Direction(int);
bool Edge(cv::Mat, int, int, std::vector<int>);
bool Neighborhood(cv::Mat, int, int, int);
cv::Mat Canny(const cv::Mat&);

#endif