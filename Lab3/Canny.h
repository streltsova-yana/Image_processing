#ifndef CANNY_H
#define CANNY_H

#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>
using namespace cv;

int Sobelx(const Mat&, int, int);
int Sobely(const Mat&, int, int);
int Direction(int);
bool Edge(Mat, int, int, std::vector<int>);
bool Neighborhood(Mat, int, int, int);
Mat Canny(const Mat&);

#endif