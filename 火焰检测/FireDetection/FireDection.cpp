#include"FireDetection.h"

/*基本算法如下：
	R>=G>=B并且R>=R_mean
	改进算法见：《基于颜色特征的火焰检测新特征》耿庆田
	基于视频的火焰检测算法：火焰颜色及动态特征的选择和探测方法

*/


Mat FireDetection(Mat& image)
{
	Mat BinImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
	int RedValue;
	int GreenValue;
	int BlueValue;
	int RedMean=0;
	int RedCount = 0;


	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			RedCount += image.at<Vec3b>(i, j)[0];
		}
		RedMean += RedCount / image.cols;
		RedCount = 0;
	}
	RedMean = RedMean / image.rows;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			//三通道排列顺序是B,G,R
			RedValue = image.at<Vec3b>(i, j)[2];
			GreenValue = image.at<Vec3b>(i, j)[1];
			BlueValue = image.at<Vec3b>(i, j)[0];
			//cout << "(" << RedValue << "," << GreenValue << "," << BlueValue << ")";
			BinImage.at<uchar>(i, j) = (RedValue >= GreenValue && GreenValue >= BlueValue && RedValue >= RedMean) ? 255 : 0;
		}
		//cout << endl;
	}
	return BinImage;
}

/*
*    第二种方法，利用火焰的HSV分量来区分火焰
*    经过多次实验：采用H:0-60  S:160-255  V: 160-255 效果还可以
*    想要更加精确的话可以用多张火焰图片得出其更加精确的范围。
*/


Mat FireDetectionHSV(Mat& image)	//利用HSV划分阈值进行火焰检测
{
	Mat imageHSV;
	cvtColor(image, imageHSV, CV_BGR2HSV);
	Mat BinaryImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < imageHSV.rows; i++)
	{
		for (int j = 0; j < imageHSV.cols; j++)
		{
			int value_h = imageHSV.at<cv::Vec3b>(i, j)[0];
			int value_s = imageHSV.at<cv::Vec3b>(i, j)[1];
			int value_v = imageHSV.at<cv::Vec3b>(i, j)[2];
			if ((value_h >= 0 && value_h <= 60) && (value_s <= 255 && value_s >= 160) && (value_v <= 255 && value_v >= 160))
			{
				BinaryImage.at<uchar>(i, j) = 255;
				image.at<cv::Vec3b>(i, j)[0] = 0;
				image.at<cv::Vec3b>(i, j)[1] = 255;
				image.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}

	return BinaryImage;

}
