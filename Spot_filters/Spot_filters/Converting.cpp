#include "Converting.h"

using namespace cv;
using namespace std;

template <typename T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;

	return v;
}

Mat brightness_rgb(const Mat& image)
{
  int k = 50;
	Mat resimg = image.clone();
	for (int x = 0; x < resimg.rows; x++)
		for (int y = 0; y < resimg.cols; y++)
			for (int c = 0; c < resimg.channels(); c++)
			{
				resimg.at<Vec3b>(x, y)[c] = clamp<int>(resimg.at<Vec3b>(x, y)[c] + k, 255, 0);
			}
  return resimg;
}

Mat brightness_hsv(const Mat& image)
{
  int k = 50;
	Mat resimg2 = image.clone();
	cvtColor(resimg2, resimg2, COLOR_BGR2HSV);

	for (int x = 0; x < resimg2.rows; x++)
		for (int y = 0; y < resimg2.cols; y++)
		{
			resimg2.at<Vec3b>(x, y)[2] = clamp<int>(resimg2.at<Vec3b>(x, y)[2] + k, 255, 0);
		}
	cvtColor(resimg2, resimg2, COLOR_HSV2BGR);
  return resimg2;
}
