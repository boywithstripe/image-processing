#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

Mat FireDetection(Mat& image);  //利用R>=G>=B并且R>=R_mean来进行火焰检测
Mat FireDetectionHSV(Mat& image);	//利用HSV划分阈值进行火焰检测
