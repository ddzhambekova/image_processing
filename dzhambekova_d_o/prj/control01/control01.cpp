#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat s1(200, 200, CV_8UC1), s2(200, 200, CV_8UC1), s3(200, 200, CV_8UC1),
        s4(200, 200, CV_8UC1), s5(200, 200, CV_8UC1), s6(200, 200, CV_8UC1);

    s1 = 255;
    circle(s1, Point(s1.rows/2, s1.rows / 2), 50, 0, CV_FILLED, 8, 0);
    //imshow("s1", s1);

    s2 = 127;
    circle(s2, Point(s1.rows / 2, s1.rows / 2), 50, 0, CV_FILLED, 8, 0);
    //imshow("s2", s2);

    s3 = 0;
    circle(s3, Point(s1.rows / 2, s1.rows / 2), 50, 127, CV_FILLED, 8, 0);
    //imshow("s3", s3);

    s4 = 127;
    circle(s4, Point(s1.rows / 2, s1.rows / 2), 50, 255, CV_FILLED, 8, 0);
    //imshow("s4", s4);

    s5 = 0;
    circle(s5, Point(s1.rows / 2, s1.rows / 2), 50, 255, CV_FILLED, 8, 0);
    //imshow("s5", s5);

    s6 = 255;
    circle(s6, Point(s1.rows / 2, s1.rows / 2), 50,127, CV_FILLED, 8, 0);
    //imshow("s6", s6);

    Mat tmp, res;
    hconcat(s1, s2, tmp);
    hconcat(tmp, s3, tmp);
    
    hconcat(s4, s5, res);
    hconcat(res, s6, res);
    vconcat(tmp, res, res);
    imshow("res", res);

    Mat resf;
    res.convertTo(resf, CV_32F, 1.0 / 255.0);

    Mat kernel1(3, 3, CV_32F), kernel2(3, 3, CV_32F), res1, res2;
    kernel1.at<float>(0, 0) = 1;
    kernel1.at<float>(0, 1) = 0;
    kernel1.at<float>(0, 2) = -1;

    kernel1.at<float>(1, 0) = 2;
    kernel1.at<float>(1, 1) = 0;
    kernel1.at<float>(1, 2) = -2;

    kernel1.at<float>(2, 0) = 1;
    kernel1.at<float>(2, 1) = 0;
    kernel1.at<float>(2, 2) = -1;


    filter2D(resf, res1, -1, kernel1, Point(-1,-1), 0, BORDER_DEFAULT);
    res1 += 4.0;
    res1 /= 8.0;
    imshow("res1", res1);

    transpose(kernel1, kernel2);
    filter2D(resf, res2, -1, kernel2, Point(-1, -1), 0, BORDER_DEFAULT);
    res2 += 4.0;
    res2 /= 8.0;
    imshow("res2", res2);

    Mat sq1, sq2;
    pow(res1, 2, sq1);
    pow(res2, 2, sq2);
    Mat res3;
    sqrt(sq1 + sq2, res3);
    imshow("res3", res3);

    waitKey(0);
}

