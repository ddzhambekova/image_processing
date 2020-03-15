#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
    // 1) построение гистограммы серого изображения
    //Mat img = imread("test.png");
    Mat img = imread("gray.jpg");
    imshow("0 original image", img);

    array<int, 256> ar_hist = {};
    for (int i = 0; i < img.rows; i += 1)
    {
        for (int j = 0; j < img.cols; j += 1)
        {
            ar_hist.at(img.at<uchar>(i, j)) += 1;
        }
    }

    Mat histImg = Mat(400, 256, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 1; i < 256; i++)
    {
        line(histImg, Point(i - 1, ar_hist[i - 1]), Point(i, ar_hist[i]), 250, 1, 4, 0);
    }
    imshow("1 histogram", histImg);

    // 2) применяем функцию к яркости картинки и выводим новую гистограмму
    array<uchar, 256> lut; //lookup table
    for (int i = 0; i < 256; i += 1)
    {
        lut.at(i) = 255 - i;//pow(i, 0.8);
    }
    Mat img1;
    LUT(img, lut, img1);
    imshow("2 image", img1);
    array<int, 256> ar_hist1 = {};
    for (int i = 0; i < img.rows; i += 1)
    {
        for (int j = 0; j < img.cols; j += 1)
        {
            ar_hist1.at(img1.at<uchar>(i, j)) += 1;
        }
    }
    Mat hist1 = Mat(400, 256, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 1; i < 256; i++)
    {
        line(hist1, Point(i - 1, ar_hist1[i - 1]), Point(i, ar_hist1[i]), 250, 1, 4, 0);
    }
    imshow("2 histogram", hist1);


    // 3) применяем clahe
    Mat clahe_img;
    Ptr<CLAHE> clahe = createCLAHE();
    cvtColor(img, img, COLOR_BGR2GRAY);
    clahe->setClipLimit(2);
    clahe->apply(img, clahe_img);
    imshow("3 clahe", clahe_img);

    array<int, 256> ar_hist_cl = {};
    for (int i = 0; i < img.rows; i += 1)
    {
        for (int j = 0; j < img.cols; j += 1)
        {
            ar_hist_cl.at(clahe_img.at<uchar>(i, j)) += 1;
        }
    }
    Mat histImgCl = Mat(400, 256, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 1; i < 256; i++)
    {
        line(histImgCl, Point(i - 1, ar_hist_cl[i - 1]), Point(i, ar_hist_cl[i]), 250, 1, 4, 0);
    }
    imshow("3 clahe histogram", histImgCl);

    // 4) глобальная бинаризация, метод Оцу
    float disp_otsu, w1, w2, a, max = 0;
    int m = 0, n = 0, alpha1 = 0, beta1 = 0, thresh = 0;
    for (int t = 0; t < 256; t += 1)
    {
        m += t * ar_hist[t];
        n += ar_hist[t];
    }
    for (int t = 0; t < 256; t += 1)
    {
        alpha1 += t * ar_hist[t];
        beta1 += ar_hist[t];

        w1 = (float)beta1 / n;
        a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);

        disp_otsu = w1 * (1 - w1) * a * a;
        if (disp_otsu > max)
        {
            max = disp_otsu;
            thresh = t;
        }
    }
    cout << thresh << endl;

    Mat img_otsu(img.rows, img.cols, CV_8UC1);
    for (int i = 0; i < img.rows; i += 1)
    {
        for (int j = 0; j < img.cols; j += 1)
        {
            if (img.at<uchar>(i, j) > thresh)
                img_otsu.at<uchar>(i, j) = 255;
            else
                img_otsu.at<uchar>(i, j) = 0;
        }
    }
    imshow("4 otsu method", img_otsu);


    // 5) локальная бинаризация, метод Ниблэка

    Mat imgf;
    img.convertTo(imgf, CV_32F, 1 / 255.0);    

    Mat img_sqr, mx2;
    pow(imgf, 2, img_sqr);
    int q = 16;
    boxFilter(img_sqr, mx2, -1, Size(q, q), Point(1, -1), true, BORDER_DEFAULT);

    Mat avg, m2x;
    boxFilter(imgf, avg, -1, Size(q, q), Point(1, -1), true, BORDER_DEFAULT);
    pow(avg, 2, m2x);

    Mat dx = mx2 - m2x;
    Mat stddev(img.rows, img.cols, CV_32FC1);

    sqrt(dx, stddev);

    double k = -0.2;
    Mat threshold = avg + k * stddev;
    Mat niblack(img.rows, img.cols, CV_32FC1);

    for (int i = 0; i < img.rows; i += 1)
    {
        for (int j = 0; j < img.cols; j += 1)
        {
            if (imgf.at<float>(i, j) > threshold.at<float>(i, j))
                niblack.at<float>(i, j) = 255;
            else niblack.at<float>(i, j) = 0;
        }
    }

    imshow("5 niblack method", niblack);

    // 6 морфологии
    Mat open, close;
    morphologyEx(img_otsu, close, MORPH_CLOSE, Mat(), Point(-1,1), 1, 0);
    imshow("close", close);
    morphologyEx(img_otsu, open, MORPH_OPEN, Mat(), Point(-1, 1), 1, 0);
    imshow("open", open);

    // 7 альфа-блендинг
    double alpha = 0.5;
    Mat alpha_blend;
    addWeighted(img, alpha, open, 1 - alpha, 0.0, alpha_blend);
    imshow("7 alpha blending", alpha_blend);
    


    waitKey(0);
}