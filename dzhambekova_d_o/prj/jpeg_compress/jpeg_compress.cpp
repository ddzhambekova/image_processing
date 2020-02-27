#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("png_cubes.png");
    Mat img1(img.rows, img.cols, CV_8UC3);

    for (int i = 0; i < img1.rows; i++)
    {
        for (int j = 0; j < img1.cols / 3; j++)
        {
            img1.at<Vec3b>(i, j).val[0] = 255;
            img1.at<Vec3b>(i, j).val[1] = 0;
            img1.at<Vec3b>(i, j).val[2] = 0;
        }
        for (int j = img1.cols / 3; j < 2 * img1.cols / 3; j++)
        {
            img1.at<Vec3b>(i, j).val[0] = 0;
            img1.at<Vec3b>(i, j).val[1] = 255;
            img1.at<Vec3b>(i, j).val[2] = 0;
        }
        for (int j = 2*img1.cols / 3; j < img1.cols; j++)
        {
            img1.at<Vec3b>(i, j).val[0] = 0;
            img1.at<Vec3b>(i, j).val[1] = 0;
            img1.at<Vec3b>(i, j).val[2] = 255;
        }
    }

    //imshow("img1", img1);
    
    vector<int> quality_params = vector<int>(2);

    quality_params[0] = CV_IMWRITE_JPEG_QUALITY;

    quality_params[1] = 65;
    imwrite("jpg65_cubes.jpg", img, quality_params);
    Mat jpg65 = imread("jpg65_cubes.jpg");

    quality_params[1] = 95;
    imwrite("jpg95_cubes.jpg", img, quality_params);
    Mat jpg95 = imread("jpg95_cubes.jpg");

    namedWindow("Original Image", 1);
    imshow("Original Image", img);


    vector<Mat> rgbChannels_img(3), rgbChannels_jpg65(3), rgbChannels_jpg95(3);
    split(img, rgbChannels_img); 
    split(jpg65, rgbChannels_jpg65);
    split(jpg95, rgbChannels_jpg95);

    Mat tmp, tmp1, all_dif;
    Mat difb65= rgbChannels_img[0]- rgbChannels_jpg65[0];
    Mat difg65= rgbChannels_img[1] - rgbChannels_jpg65[1];
    Mat difr65 = rgbChannels_img[2] - rgbChannels_jpg65[2];

    Mat difb95 = rgbChannels_img[0] - rgbChannels_jpg95[0];
    Mat difg95 = rgbChannels_img[1] - rgbChannels_jpg95[1];
    Mat difr95 = rgbChannels_img[2] - rgbChannels_jpg95[2];

    hconcat(difb65, difg65, tmp);
    hconcat(tmp, difr65, tmp);

    hconcat(difb95, difg95, tmp1);
    hconcat(tmp1, difr95, tmp1);

    vconcat(tmp, tmp1, all_dif);

    imshow("difference", all_dif);
    imshow("jpg65", jpg65);
    imshow("jpg95", jpg95);

    //Mat g = Mat::zeros(img.rows, img.cols, CV_8UC3);
    //vector<Mat> channels;
    //channels.push_back(g);
    //channels.push_back(g);
    //channels.push_back(difb65);

    //Mat fin_img;
    //merge(channels, fin_img);
    //namedWindow("Red", 1);
    //imshow("Red", fin_img);

   

    waitKey(0);
}