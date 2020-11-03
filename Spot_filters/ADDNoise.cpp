#include "AddNoise.h"

using namespace cv;

Mat addNoise(const Mat& image)
{
	Mat resimg = image.clone();
	for (int x = 0; x < resimg.rows; x++)
		for (int y = 0; y < resimg.cols; y++)
			for (int c = 0; c < resimg.channels(); c++)
			{
				resimg.at<Vec3b>(x, y)[c] = 0.07 * resimg.at<Vec3b>(x, y)[0] + 0.72 * resimg.at<Vec3b>(x, y)[1] + 0.21 * resimg.at<Vec3b>(x, y)[2];
			}
	return resimg;
}