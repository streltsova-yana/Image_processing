#include "Watersheds.h"

using namespace cv;
using namespace std;

void threshold_image(Mat& image, int thresh)
{
    for (int y = 0; y < (image.rows); y++)
        for (int x = 0; x < image.cols; x++) {
            if (image.at<uchar>(y, x) < thresh)
                image.at<uchar>(y, x) = 255;
            else
                image.at<uchar>(y, x) = 0;
        }
};

Mat LBP(const Mat& src)
{
    Mat lbp(src.size(), CV_8UC1);
    unsigned int cen = 0, lbp_cen = 0;
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            cen = src.at<uchar>(y, x);
            lbp_cen = 0;
            if (cen <= src.at<uchar>(y - 1, x - 1))
                lbp_cen += 1;
            if (cen <= src.at<uchar>(y - 1, x))
                lbp_cen += 2;
            if (cen <= src.at<uchar>(y - 1, x + 1))
                lbp_cen += 4;
            if (cen <= src.at<uchar>(y, x + 1))
                lbp_cen += 8;
            if (cen <= src.at<uchar>(y + 1, x + 1))
                lbp_cen += 16;
            if (cen <= src.at<uchar>(y + 1, x))
                lbp_cen += 32;
            if (cen <= src.at<uchar>(y + 1, x - 1))
                lbp_cen += 64;
            if (cen <= src.at<uchar>(y, x - 1))
                lbp_cen += 128;
            lbp.at<uchar>(y, x) = lbp_cen;
        }
    }
    return lbp;
}

cv::Mat Watershed(const Mat& src, int thresh)
{
    Mat gray_image = src.clone(), blur_image, binary;
    if (gray_image.channels() == 3)
        cvtColor(gray_image, gray_image, COLOR_BGR2GRAY);

    blur(gray_image, blur_image, Size(5, 5));
    threshold_image(blur_image, thresh);
    blur_image.convertTo(binary, CV_8U);

    //Поиск контуров
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); 

    //Создание гистограммы 
    vector<vector<int>> histogram(contours.size());
    for (int i = 0; i < contours.size(); i++)
        histogram[i] = vector<int>(256, 0);

    //Вычисление дескрипторов
    int n = 0, T = 1;
    double area_average = 0., len_average = 0.0, com_average = 0.0;
    vector<double> area_mat, len_mat, com_mat;
    for (int i = 0; i < contours.size(); i++) {
        double compact = 0.;
        double area = contourArea(contours[i], false);
        double length = arcLength(contours[i], false);
        if (area != 0)
            compact = pow(length, 2) / area;
        if (area < T) 
            n++;
        if ((area > T) && (length > T) && (compact > T)) {
            area_average += area;
            len_average += length;
            com_average += compact;
        }
        area_mat.push_back(area);
        len_mat.push_back(length);
        com_mat.push_back(compact);
    }
    area_average /= (contours.size() - n);
    len_average /= (contours.size() - n);
    com_average /= (contours.size() - n);

    double area_variance = 0., len_variance = 0., com_variance = 0.;
    for (int i = 0; i < contours.size(); i++) {
        if ((area_mat[i] > T) && (len_mat[i] > T) && (com_mat[i] > T)) {
            area_variance += pow(area_mat[i] - area_average, 2);
            len_variance += pow(len_mat[i] - len_average, 2);
            com_variance += pow(com_mat[i] - com_average, 2);
        }
    }
    area_variance = area_variance / (contours.size() - n);
    len_variance = len_variance / (contours.size() - n);
    com_variance = com_variance / (contours.size() - n);

    Mat marks = Mat::zeros(gray_image.size(), CV_32SC1);
    for (int i = 0; i < contours.size(); i++)
        drawContours(marks, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1), -1);

    cv::circle(marks, Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
    cv::watershed(src, marks);
    Mat mark = Mat::zeros(marks.size(), CV_8UC1);
    marks.convertTo(mark, CV_8UC1);
    cv::bitwise_not(mark, mark);

    vector<Vec3b> colors;
    for (int i = 0; i < contours.size(); i++) {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    Mat watershed = Mat::zeros(marks.size(), CV_8UC3);
    for (int y = 0; y < marks.rows; y++) {
        for (int x = 0; x < marks.cols; x++) {
            int index = marks.at<int>(y, x);
            watershed.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
            if (index > 0 && index <= static_cast<int>(contours.size()))
                watershed.at<Vec3b>(y, x) = colors[index - 1];
        }
    }

    Mat lbp = LBP(src);
    for (int y = 0; y < lbp.rows; y++) {
        for (int x = 0; x < lbp.cols; x++) {
            int idx = marks.at<int>(y, x);
            if (idx > 0 && idx <= static_cast<int>(contours.size()))
                histogram[idx - 1][lbp.at<uchar>(y, x)] += 1;
        }
    }

    int max_histogram = 0;
    for (int i = 0; i < 256; i++) {
        int sum = 0;
        for (int j = 0; j < contours.size(); j++)
            sum += histogram[j][i];
        if (max_histogram < sum)
            max_histogram = sum;
    }
    double scale = (0.95 * 256) / max_histogram;

    return watershed;
}