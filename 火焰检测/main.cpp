#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>
#include"FireDetection.h"

using namespace std;
using namespace cv;
void ShowHistogram(Mat& Orimage);   //显示直方图


int main()
{
	Mat image = imread("E:\\学习资料\\研一下\\视频图像处理_茅\\homework3\\火焰检测\\image6.jpg");
	if (image.empty()) {
		cout << "图片读取失败！" << endl;
	}
	imshow("Original Image", image);
	//imshow("firedetection", FireDetection(image));
	ShowHistogram(image);
	waitKey(0);
	return 0;
}

void ShowHistogram(Mat& Orimage) 
{
	int* redHistogram = new int[256];
	int* greenHistogram = new int[256];
	int* blueHistogram = new int[256];
	memset(redHistogram, 0, 256 * sizeof(int));
	memset(greenHistogram, 0, 256 * sizeof(int));
	memset(blueHistogram, 0, 256 * sizeof(int));

	Mat image = Orimage.clone();
	uchar* p;
	//将红绿蓝三元素分量分别放入三个数组中
	for (int n = 0; n <= 2; n++)
	{
		for (int i = 0; i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				switch (n) {
				case 0:redHistogram[(int)image.at<Vec3b>(i, j)[0]]++; break;
				case 1:greenHistogram[(int)image.at<Vec3b>(i, j)[1]]++; break;
				case 2:blueHistogram[(int)image.at<Vec3b>(i, j)[2]]++; break;
				}
			}
		}
		
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "红色像素为： " << i << "  的个数： " << redHistogram[i] << endl;
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "绿色像素为： " << i << "  的个数： " << greenHistogram[i] << endl;
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "蓝色像素为： " << i << "  的个数： " << blueHistogram[i] << endl;
	}

	//找到每一个直方图统计矩阵的最大值
	int Max_redhi = 0;
	int Max_greenhi = 0;
	int Max_bluehi = 0;
	for (int i = 0; i < 256; i++)
	{
		if (redHistogram[i] >= Max_redhi) Max_redhi = redHistogram[i];
		if (greenHistogram[i] >= Max_greenhi) Max_greenhi = greenHistogram[i];
		if (blueHistogram[i] >= Max_bluehi)Max_bluehi = blueHistogram[i];
	}
	
	Mat redhi_image =Mat::zeros(256, 256, CV_8UC3);
	Mat greenhi_image = Mat::zeros(266, 256, CV_8UC3);
	Mat bluehi_image = Mat::zeros(256, 256, CV_8UC3);

	//绘制红绿蓝三元素的直方图
	//绘制直方图需要用到函数：rectangle(Mat& image,Point pt1,Point pt2,Scalar &color,int thickness=1,int lineType=8,intshift=0)
	/****     rectangle(cv::InputOutputArrar img  可以是Mat类型，表示直方图图片，将直方图存储在变量img中
	*					Point pt1   Point坐标类型，表示所画矩阵的左上角坐标，以图片为例，x轴为图片最上面一条线即行=0的线(方向为：从左到右)
	*					Point pt2   另外一点（两个对角点确定一个矩阵）
	*					Scalar &color  颜色（0，0，0）为黑色（255，255，255）为白色
	*					其他看字面意思即可
	* 需要注意的是坐标向量的定义，x轴为最上面一条线，方向：从左到右
	)
	*     
	*************/
	for (int i = 0; i < 256; i++)
	{
		int RedValue = redHistogram[i] / Max_redhi * 256;
		rectangle(redhi_image, Point(i, 255), Point(i + 1, 255 - RedValue), Scalar(255, 0, 0));

		int GreenValue = greenHistogram[i] / Max_greenhi * 256;
		rectangle(greenhi_image, Point(i, 255), Point(i + 1, 255 - GreenValue), Scalar(0, 255, 0));

		int blueValue = blueHistogram[i] / Max_bluehi * 256;
		rectangle(bluehi_image, Point(i, 255), Point(i + 1, 255 - blueValue), Scalar(0, 0, 255));

	}

	imshow("redHistogram", redhi_image);
	imshow("greenHistogram", greenhi_image);
	imshow("blueHistogram", bluehi_image);

	delete[] redHistogram;
	delete[] greenHistogram;
	delete[] blueHistogram;


}