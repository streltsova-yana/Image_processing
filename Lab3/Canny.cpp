//#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>
#include "Canny.h"
#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>

using namespace cv;
using namespace std;

int Sobelx(const Mat& image, int posr, int posc)
{
    std::vector<int> x = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    int sobx = 0, count = 0;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            sobx += image.at<uchar>(posr + i, posc + j) * x[count];
            count++;
        }
    return sobx;
}

int Sobely(const Mat& image, int posr, int posc)
{
    std::vector<int> y = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
    int soby = 0, count = 0;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            soby += image.at<uchar>(posr + i, posc + j) * y[count];
            count++;
        }
    return soby;
}

int Direction(int an)
{
    if ((an > 25 && an <= 70) || (-110 >= an && an > -155))
        return 2;
    if ((an > 70 && an <= 115) || (-65 >= an && an > -110))
        return 1;
    if ((an > 115 && an <= 160) || (-20 >= an && an > -65))
        return 4;
    if ((an > 160 && an <= 180) || (an <= -155 && an >= 180) || (-20 < an && an <= 25))
        return 3;
}

bool Edge(Mat img, int r, int c, vector<int> dir)
{
    switch (dir[r * img.cols + c])
    {
    case 1:
        if (img.at<uchar>(r, c) >= img.at<uchar>(r - 1, c) && img.at<uchar>(r, c) >= img.at<uchar>(r + 1, c))
            return true;
        else return false;
    case 2:
        if (img.at<uchar>(r, c) >= img.at<uchar>(r - 1, c + 1) && img.at<uchar>(r, c) >= img.at<uchar>(r + 1, c - 1))
            return true;
        else return false;
    case 3:
        if (img.at<uchar>(r, c) >= img.at<uchar>(r, c + 1) && img.at<uchar>(r, c) >= img.at<uchar>(r + 1, c - 1))
            return true;
        else return false;
    case 4:
        if (img.at<uchar>(r, c) >= img.at<uchar>(r + 1, c + 1) && img.at<uchar>(r, c) >= img.at<uchar>(r - 1, c - 1))
            return true;
        else return false;
    }
    return false;
}

bool Neighborhood(Mat image, int r, int c, int up)
{
    std::vector<int> x = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
    std::vector<int> y = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
    int count = 0;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            if (image.at<uchar>(r + x[count], c + y[count]) > up)
                return true;
            count++;
        }
    return false;
}

Mat Canny(const Mat& image)
{
    int rows = image.rows;
    int cols = image.cols;
    Mat gray = image.clone();
    //imshow("Display Window", resimg);	
    GaussianBlur(gray, gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(gray, gray, COLOR_BGR2GRAY);
    //imshow("Display gray", gray);

    //Собель
    long mediana = 0;
    int sobx = 0, soby = 0, count = 0;
    std::vector<int> dir(rows * cols);
    Mat tmp = Mat::zeros(Size(cols, rows), CV_8UC1);
    double pi = 3.14;
    int gr = 0;
    for (int x = 1; x < rows - 1; x++)
        for (int y = 0; y < cols; y++)
        {
            mediana += gray.at<uchar>(x, y);
            if (y == 0 || y == cols - 1)
                tmp.at<uchar>(x, y) = 0;
            else
            {
                sobx = Sobelx(gray, x, y);
                //cout << sobx << endl;
                soby = Sobely(gray, x, y);
                gr = sqrt(sobx * sobx + soby * soby);

                dir[x * cols + y] = Direction((round(atan2(sobx, soby) * 180) / pi));
                //cout << dir[x * resimg.cols + y] << endl;
                tmp.at<uchar>(x, y) = saturate_cast<uchar>(gr);
            }
        }
    //imshow("Display Sobel", tmp);
    mediana = mediana / cols / (rows - 1);
    //cout << mediana;

    //Уточняем края
    Mat tmp2 = Mat::zeros(Size(cols, rows), CV_8UC1);
    for (int x = 1; x < rows - 1; x++)
        for (int y = 0; y < cols; y++)
        {
            if (y == 0 || y == cols - 1)
                tmp2.at<uchar>(x, y) = 0;
            else
            {
                if (!Edge(tmp, x, y, dir))
                    tmp2.at<uchar>(x, y) = 0;
                else tmp2.at<uchar>(x, y) = tmp.at<uchar>(x, y);
            }
        }
    //imshow("Display ApproxEdge", tmp2);
    // сильные, слабые, ненужные пиксели
    // отбраковка пикселей не имеющих в окрестности сильных
    tmp = Mat::zeros(Size(cols, rows), CV_8UC1);
    int up = saturate_cast<uchar>(mediana + 20);
    int down = saturate_cast<uchar>(mediana);
    vector<int> power(rows * cols);
    for (int x = 1; x < rows - 1; x++)
        for (int y = 1; y < cols; y++)
        {
            if (tmp2.at<uchar>(x, y) > up)
                tmp.at<uchar>(x, y) = tmp2.at<uchar>(x, y);
            else if (tmp2.at<uchar>(x, y) < up&& tmp2.at<uchar>(x, y) > down)
            {
                if (Neighborhood(tmp2, x, y, up))
                    tmp.at<uchar>(x, y) = tmp2.at<uchar>(x, y);
                else
                    tmp.at<uchar>(x, y) = 0;
            }
            else
                tmp.at<uchar>(x, y) = 0;
        }

    for (int i = 0; i < gray.cols; i++)
        tmp.at<uchar>(0, i) = 0;
    for (int i = 0; i < gray.cols; i++)
        tmp.at<uchar>(gray.rows - 1, i) = 0;
    //imshow("Display CannyRes", tmp);

    return tmp;
}