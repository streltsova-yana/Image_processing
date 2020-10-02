#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

#include "Grayscale.h"

using namespace cv;
using namespace std;

Mat gray_scale(const Mat& image)
{
	cout << "done";
	Mat resimg = image.clone();
	for (int x = 0; x < resimg.rows; x++)
		for (int y = 0; y < resimg.cols; y++)
			for (int c = 0; c < resimg.channels(); c++)
			{
				resimg.at<Vec3b>(x, y)[c] = 0.21 * resimg.at<Vec3b>(x, y)[0] + 0.72 * resimg.at<Vec3b>(x, y)[1] + 0.07 * resimg.at<Vec3b>(x, y)[2];
			}
	return resimg;
}