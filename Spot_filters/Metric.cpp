#include "Metric.h"

using namespace cv;

float ssim(const Mat& _a, const Mat& _b)
{
	if ((_a.rows != _b.rows) || (_a.cols != _b.cols)) //Check size
		throw "Images must be the same size";

	Mat a, b;
	cvtColor(_a, a, COLOR_BGR2GRAY); //Convert to grayscale
	cvtColor(_b, b, COLOR_BGR2GRAY);
	int N = a.rows * a.cols;

	float avX = 0, avY = 0; //Average calculation
	for (int y = 0; y < a.rows; y++)
		for (int x = 0; x < a.cols; x++) {
			avX += a.at<uchar>(y, x);
			avY += b.at<uchar>(y, x);
		}
	avX = avX / N;
	avY = avY / N;
	
	float disX = 0, disY = 0, cov = 0; //Calculating variance and covariance
	for (int y = 0; y < a.rows; y++)
		for (int x = 0; x < a.cols; x++) {
			disX += (a.at<uchar>(y, x) - avX) * (a.at<uchar>(y, x) - avX);
			disY += (b.at<uchar>(y, x) - avY) * (b.at<uchar>(y, x) - avY);
			cov += (a.at<uchar>(y, x) - avX) * (b.at<uchar>(y, x) - avY);
		}
	disX = disX / (N - 1);
	disY = disY / (N - 1);
	cov = cov / (N - 1);

	float C1 = 0.01 * 255 * 0.01 * 255; //Calculation of constants and SSIM
	float C2 = 0.03 * 255 * 0.03 * 255;
	float SSIM = ((2 * avX * avY + C1) * (2 * cov + C2)) /
		         ((avX * avX + avY * avY + C1) * (disX + disY + C2));
	return SSIM;
};