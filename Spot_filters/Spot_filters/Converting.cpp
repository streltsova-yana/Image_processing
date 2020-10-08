#include "Converting.h"

using namespace cv;

Mat brightness_rgb(const Mat& image)
{
    int k = 50;
    Mat resimg = image.clone();
    for (int x = 0; x < resimg.rows; x++)
        for (int y = 0; y < resimg.cols; y++)
            for (int c = 0; c < resimg.channels(); c++)
            {
                resimg.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(resimg.at<Vec3b>(x, y)[c] + k);
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
            resimg2.at<Vec3b>(x, y)[2] = saturate_cast<uchar>(resimg2.at<Vec3b>(x, y)[2] + k);
        }
    cvtColor(resimg2, resimg2, COLOR_HSV2BGR);
    return resimg2;
}

Mat bgr2hsv(const Mat& _bgr)
{
    if (_bgr.type() != 16)
        throw "Image type must be CV_8UC3";
    Mat hsv(_bgr.size(), CV_32FC3);
    for (int y = 0; y < _bgr.rows; y++)
        for (int x = 0; x < _bgr.cols; x++) {
            float B = _bgr.at<Vec3b>(y, x)[0] / 255.0;
            float G = _bgr.at<Vec3b>(y, x)[1] / 255.0;
            float R = _bgr.at<Vec3b>(y, x)[2] / 255.0;

            float Cmin = fmin(R, G);
            Cmin = fmin(Cmin, B);
            float Cmax = fmax(R, G);
            Cmax = fmax(Cmax, B);
            float delta = Cmax - Cmin;

            if (delta == 0) {
                hsv.at<Vec3f>(y, x)[0] = 0;
                hsv.at<Vec3f>(y, x)[1] = 0;
                continue;
            }
            hsv.at<Vec3f>(y, x)[2] = Cmax;
            hsv.at<Vec3f>(y, x)[1] = delta / Cmax;
            if (R == Cmax) 
                hsv.at<Vec3f>(y, x)[0] = int(60 * ((G - B) / delta));
            else if (G == Cmax)
                hsv.at<Vec3f>(y, x)[0] = int(60 * ((B - R) / delta + 2.0));
            else
                hsv.at<Vec3f>(y, x)[0] = int(60 * ((R - G) / delta + 4.0));
            if (hsv.at<Vec3f>(y, x)[0] < 0)
                hsv.at<Vec3f>(y, x)[0] += 360;
        }
    return hsv;
};

Mat hsv2bgr(const Mat& _hsv)
{
    if (_hsv.type() != 21)
        throw "Image type must be CV_32FC3";
    Mat bgr(_hsv.size(), CV_8UC3);
    for (int y = 0; y < _hsv.rows; y++)
        for (int x = 0; x < _hsv.cols; x++) {
            float B = 0, G = 0, R = 0;
            float H = _hsv.at<Vec3f>(y, x)[0];
            float S = _hsv.at<Vec3f>(y, x)[1];
            float V = _hsv.at<Vec3f>(y, x)[2];
            float C = V * S;
            float X = C * (1.0 - fabs(fmod((H / 60.0), 2.0) - 1.0));
            float m = V - C;
            if ((H >= 0) && (H < 60)) {
                R = C; 
                G = X; 
                B = 0;
            }
            else if ((H >= 60) && (H < 120)) {
                R = X;
                G = C;
                B = 0;
            }
            else if ((H >= 120) && (H < 180)) {
                R = 0;
                G = C;
                B = X;
            }
            else if ((H >= 180) && (H < 240)) {
                R = 0;
                G = X;
                B = C;
            }
            else if ((H >= 240) && (H < 300)) {
                R = X;
                G = 0;
                B = C;
            }
            else if ((H >= 300) && (H < 360)) {
                R = C;
                G = 0;
                B = X;
            }
            else {
                R = 0;
                G = 0;
                B = 0;
            }
            bgr.at<Vec3b>(y, x)[0] = int((B + m) * 255);
            bgr.at<Vec3b>(y, x)[1] = int((G + m) * 255);
            bgr.at<Vec3b>(y, x)[2] = int((R + m) * 255);
        }
    return bgr;
};