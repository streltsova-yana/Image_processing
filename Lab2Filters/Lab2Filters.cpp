#include "Header.h"
using namespace cv;
Mat MedianFilter(const Mat& image)
{
	Mat copy(image);
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
}
Mat Average(const cv::Mat& image)
{
	Mat copy(image);
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
}
