//#include "stdafx.h"
/*计算hsv图像的直方图*/
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

class CalcHistogram
{
private:
	int histSize[3];         //直方图项的数量
	float hranges[2];        //h通道像素的最小和最大值
	float sranges[2];        //s通道像素的最小和最大值
	float vranges[2];        //v通道像素的最小和最大值
	const float* ranges[3];  //各通道的范围
	int channels[3];         //三个通道
	int dims;                //直方图的维数

public:
	CalcHistogram(int hbins = 30, int sbins = 32, int vbins = 32)
	{
		histSize[0] = hbins;
		histSize[1] = sbins;
		histSize[2] = vbins;
		hranges[0] = 0; hranges[1] = 180;
		sranges[0] = 0; sranges[1] = 256;
		vranges[0] = 0; vranges[1] = 256;
		ranges[0] = hranges;
		ranges[1] = sranges;
		ranges[2] = vranges;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;
		dims = 3;
	}

	Mat getHistogram(const Mat& image);
	void getHistogramImage(const Mat& image);
};

Mat CalcHistogram::getHistogram(const Mat& image)
{
	Mat hist;
	calcHist(&image,  //导入Mat类数组
		1,            //与image一起的，1说明只有一张图
		channels,     //const* channels 
		Mat(),        //Mat()：构造函数，此处为掩模作用，掩模多用来对图像进行裁剪
		hist,         //输出直方图数组，dims维
		dims,         //确定维度，HSV三个特征，取三维
		histSize,     //用于指出直方图数组每一维的大小的数组，即指出每一维的bin的个数的数组
		ranges,       //
		true,      //直方图每一维的histSize是均匀的
		false
	);

	return hist;
}

void CalcHistogram::getHistogramImage(const Mat& image)
{
	Mat hist = getHistogram(image);
	int scale = 4;
	int hbins = histSize[0];
	int sbins = histSize[1];
	int vbins = histSize[2];
	float* hist_sta = new float[sbins];
	float* hist_val = new float[vbins];
	float* hist_hue = new float[hbins];
	memset(hist_val, 0, vbins * sizeof(float)); //将hist_val初始化为0
	// memset函数的原型是 extern void *memset(void *buffer, int c, int count)；
	// buffer 是指针或者数组，void是要初始化的首内存的首地址；a是要初始化的变为的数据，count是buffer的长度，即大小
	// 作用：清空数组buffer
	memset(hist_sta, 0, sbins * sizeof(float));
	memset(hist_hue, 0, hbins * sizeof(float));

	for (int s = 0; s < sbins; s++)
	{
		for (int v = 0; v < vbins; v++)
		{
			for (int h = 0; h < hbins; h++)
			{
				float binVal = hist.at<float>(h, s, v);
				hist_hue[h] += binVal;
				hist_val[v] += binVal;
				hist_sta[s] += binVal;
			}
		}
	}

	double max_sta = 0, max_val = 0, max_hue = 0;
	for (int i = 0; i < sbins; ++i)
	{
		if (hist_sta[i] > max_sta)
			max_sta = hist_sta[i];
	}
	for (int i = 0; i < vbins; ++i)
	{
		if (hist_val[i] > max_val)
			max_val = hist_val[i];
	}
	for (int i = 0; i < hbins; ++i)
	{
		if (hist_hue[i] > max_hue)
			max_hue = hist_hue[i];
	}

	Mat sta_img = Mat::zeros(240, sbins * scale + 20, CV_8UC3);
	Mat val_img = Mat::zeros(240, vbins * scale + 20, CV_8UC3);
	Mat hue_img = Mat::zeros(240, hbins * scale + 20, CV_8UC3);

	for (int i = 0; i < sbins; ++i)
	{
		//cvRound(double value):返回最接近的整数——四舍五入
		int intensity = cvRound(hist_sta[i] * (sta_img.rows - 10) / max_sta);
		rectangle(sta_img, Point(i * scale + 10, sta_img.rows - intensity), Point((i + 1) * scale - 1 + 10, sta_img.rows - 1), Scalar(0, 255, 0), 1);
	}
	for (int i = 0; i < vbins; ++i)
	{
		int intensity = cvRound(hist_val[i] * (val_img.rows - 10) / max_val);
		rectangle(val_img, Point(i * scale + 10, val_img.rows - intensity), Point((i + 1) * scale - 1 + 10, val_img.rows - 1), Scalar(0, 0, 255), 1);
	}
	for (int i = 0; i < hbins; ++i)
	{
		int intensity = cvRound(hist_hue[i] * (hue_img.rows - 10) / max_hue);
		rectangle(hue_img, Point(i * scale + 10, hue_img.rows - intensity), Point((i + 1) * scale - 1 + 10, hue_img.rows - 1), Scalar(255, 0, 0), 1);
	}

	imshow("Shist", sta_img);
	imshow("Vhist", val_img);
	imshow("Hhist", hue_img);

	delete[] hist_sta;
	delete[] hist_val;
	delete[] hist_hue;
}

int main()
{
	Mat src = imread("E:\\学习资料\\研一下\\视频图像处理_茅\\homework_NeedHandIn\\火焰检测\\image1.jpg"), hsv;
	if (!src.data)
	{
		cout << "error, the image is not built!" << endl;
		return -1;
	}
	cvtColor(src, hsv, CV_BGR2HSV);
	imshow("src", src);
	imshow("hsv", hsv);
	CalcHistogram h;
	h.getHistogram(hsv);
	h.getHistogramImage(hsv);
	waitKey();
	return 0;
}