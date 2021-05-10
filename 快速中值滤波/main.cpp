/*
*  实现中值滤波(算法来源：A Fast Two-Dimensional Median Filtering Algorithm)
*  环境：opencv4.4   debug  x64
*  博客链接：
*  仅供学习
*/


#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>


using namespace std;
using namespace cv;

void QuickMedianFluter(Mat OriImage, Mat& ResImage, int size);
int FindMedian(int H[], int n,int size,int &mNum);



int main()
{
	Mat image1 = imread("salt_pepper_Image.jpg",IMREAD_GRAYSCALE);
	if (image1.empty())
	{
		cout << "读取图片失败。" << endl;
	}
	imshow("Origin Image", image1);



	//中值滤波,调用opencv自带的函数 
	Mat result1;
	medianBlur(image1, result1, 3);
	imshow("Result1 Image(after median fluter,opencv自带)", result1);

	//快速中值滤波，利用自己编写的函数
	Mat result2;

	//直接clone过去即可，中间部分会随着滤波过程的进行随之改变
	result2 = image1.clone();
	//ResImage = OriImage.clone();
	QuickMedianFluter(image1, result2, 3);
	imshow("Result2 Image(自我编写函数)", result2);


	waitKey(0);
	return 0;
}



/***********************************************************
* 函数功能：中值滤波(利用直方图法快速实现)
* 参数介绍：OriInage:原图    ResImage:滤波后的图
*			size:滤波器(或者领域)边长，大小为size x size(如3x3) 
***********************************************************/



void QuickMedianFluter(Mat OriImage, Mat& ResImage, int size)
{
	int m = OriImage.rows;   //m是行，对应下面的x
	int n = OriImage.cols;   //n是列，对应下面的n
	int *Histogram = new int[256];
	memset(Histogram, 0, 256 * sizeof(int));
	int radius = size / 2;    //半径
	int th = size * size / 2 + 1;    //算法中的th
	int median = 0;     //保存直方图中的中值对应的像素
	int mNum = 0;       //保存小于中值像素median的总个数
	int left = 0;       //最左列将要移除的
	int right = 0;      //最右边将要加入的

	cout << "行：" << m << endl;
	cout << "列：" << n << endl;


	//处理边界，边界没法进行中值滤波，因此将边界所有像素赋值给ResImage
	for (int i = radius; i < m - radius; i++)  //m是行，对应x从上至下
	{
		//初始化Histogram
		memset(Histogram, 0, 256 * sizeof(int));
		for (int k = i-radius; k <= i+radius; k++)
		{
			for (int h = 0; h < size; h++)
			{
				Histogram[OriImage.at<uchar>(k, h)]++;
			}
		}
		median= FindMedian(Histogram, 256, size,mNum);
		ResImage.at<uchar>(i,radius) = median;


		for (int j = radius; j < n - radius; j++)   //n是列，对应y从左至右
		{
			//j在radius处，直方图已求，跳过
			if (j == radius) continue;   
			//根据算法，中心向右移动一位，将最左列的数移除直方图中
			for (int k = i-radius; k <= i + radius; k++)
			{
				left = OriImage.at<uchar>(k, j - 1 - radius);
				Histogram[left]--;
				if (left <= median) mNum = mNum - 1;
			}
			
			//根据算法，中心向右移动一位，将最右侧的数移入直方图中
			for (int k = i-radius; k <= i + radius; k++)
			{
				right = OriImage.at<uchar>(k, j + radius);
				Histogram[right]++;
				if (right <= median) mNum = mNum + 1;
			}

			if (mNum == th)
			{
				ResImage.at<uchar>(i, j) = median;
				continue;

			}
			//利用前一中值和所有小于等于中值median的数mNum,求当前中值
			if (mNum < th)
			{
				//小于th(第th个数为中值)，在当前median右边，往右找（像素加一寻找）
				while (mNum < th) {
					median = median + 1;
					mNum = mNum + Histogram[median];
				}
			}
			else {
				//大于th(第th个数为中值)，在当前median左边，往右找（像素减一寻找）
				while (mNum > th)
				{
					mNum = mNum - Histogram[median];
					median = median - 1;
				}
			}
			ResImage.at<uchar>(i, j) = median;
			
		}
	}

	delete[] Histogram;
}

/**************************************************************
* 函数功能：通过直方图返回中值
* 参数介绍：H[]:直方图数组  n:直方图维数
*			size:滤波器的大小
****************************************************************/



int FindMedian(int H[], int n,int size,int &mNum)
{
	int median = 0;   //初始化中值为0
	int sum_cout = 0;  //求和
	int median_flag = size * size / 2;  //中值标志
	for (int i = 0; i < 256; i++)
	{
		sum_cout += H[i];
		if (sum_cout > median_flag)
		{
			median = i;
			break;
		}
	}
	mNum = sum_cout;
	return median;
}

