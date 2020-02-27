#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // плавный градиент
    Mat m(120, 768, CV_8U);
    for (int i = 0; i < 61; i += 1)
    {
        for (int j = 0; j < m.cols; j += 1)
        {
            m.at<uchar>(i, j) = j/3;            
        }
    }
    // гамма-коррекция
    double gamma = 2.2;
    for (int i = 61; i < m.rows; i += 1)
    {
        for (int j = 0; j < m.cols; j += 1)
        {
            m.at<uchar>(i, j) = pow((double)m.at<uchar>(i - 60, j) / 255, gamma) * 255;
        }
    }


    // ступенчатый градиент
    Mat m1(120, 768, CV_8U);
    for (int i = 0; i < 61; i += 1)
    {
        for (int j = 0; j < m1.cols; j += 1)
        {
            m1.at<uchar>(i, j) = (j/30)*10+5;
        }
    }
    // гамма-коррекция
    double gamma1 = 2.2;
    for (int i = 61; i < m1.rows; i += 1)
    {
        for (int j = 0; j < m1.cols; j += 1)
        {
            m1.at<uchar>(i, j) = pow((double)m1.at<uchar>(i - 60, j) / 255, gamma1) * 255;
        }
    }

    imshow("gradient_smooth", m);
    imshow("gradient_step", m1);
    waitKey(0);
    return 0;
}