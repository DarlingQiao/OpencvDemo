#pragma once
#include  <iostream>
#include  <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2\imgproc\types_c.h>

#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")



using namespace cv;
using namespace std;
class BoundingRect {
public:
  BoundingRect(const std::string& imgeName) {
    // Declares a vector of vectors for store the contours
    Mat originalimage;
    Mat image;

    // Loads the original image
    originalimage = imread(imgeName.c_str());
    imshow("src", originalimage);
    // Converts original image to an 8UC1 image
    cvtColor(originalimage, image, CV_BGR2GRAY);
    // 	imshow("cvtColor", image);
    // 	// ��˹ģ������Ҫ���ڽ���
    //	GaussianBlur(image, image, Size(3, 3), 0);
    // 	imshow("GaussianBlurͼ", image);
    // 	// ��ֵ��ͼ����Ҫ����ɫ����ת�ɰ�ɫ��ʹ����Ϊ��ɫ
    threshold(image, image, 165, 255, THRESH_BINARY);
    // 	imshow("thresholdͼ", image);
    // 	// ��ֵ�˲���ͬ�����ڽ���
    // 	medianBlur(image, image, 3);
    // 	imshow("medianBlurͼ", image);
    // 	// ��ʴ��������Ҫ�����ݲ�����������ָ�ʴ��ʹ���������ӣ�������������ѡȡ
    // 	erode(image, image, Mat(9, 9, CV_8U));
    // Finds contours
    vector<vector<Point> > v;
    vector<Vec4i> hierarchy;
    Mat result;
    Rect rect;
    findContours(image, v, hierarchy, RETR_CCOMP, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < hierarchy.size(); i++)
    {
      rect = boundingRect(v.at(i));
      // ����С��Բ�����ź�ɫ
      drawContours(originalimage, v, i, Scalar(0, 0, 255), 1, 8, hierarchy);
      // �����ΰ�ΧԲ
      rectangle(originalimage, rect, Scalar(255, 0, 0));
    }
    namedWindow("Ejemplo");
    imshow("Ejemplo", originalimage);
    waitKey(60000);
  }

};