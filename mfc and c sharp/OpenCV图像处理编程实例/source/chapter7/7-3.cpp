// 功能：代码 7-3 FloodFill 图像分割
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
// 初识化参数
Mat image, gray, mask;
int ffillMode = 1;
int loDiff = 20, upDiff = 20;
int connectivity = 4;
int isColor = true;
bool useMask = false;
int newMaskVal = 255;
// 鼠标响应函数
static void onMouse(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;
	// floodfill参数设置
	Point seed = Point(x, y);
	int lo = ffillMode == 0 ? 0 : loDiff;
	int up = ffillMode == 0 ? 0 : upDiff;
	int flags = connectivity + (newMaskVal << 8) +
		(ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	// 颜色分量随机选取
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	// 颜色选择
	Scalar newVal = isColor ? Scalar(b, g, r)
	    : Scalar(r*0.299 + g*0.587 + b*0.114);
	Mat dst = isColor ? image : gray;
	int area;
	// 根据标志位选择泛洪填充
	if (useMask)
	{
		// 阈值化操作
		threshold(mask, mask, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, mask, seed, 
			newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
		imshow("mask", mask);
	}
	else
	{
		// 泛洪填充
		area = floodFill(dst, seed, newVal, &ccomp,
		    Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
	}
	imshow("image", dst);
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (srcImage.empty())
		return 0;
	srcImage.copyTo(image);
	cvtColor(srcImage, gray, CV_BGR2GRAY);
	mask.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);
	// 鼠标响应回调函数
	namedWindow("image", 0);
	setMouseCallback("image", onMouse, 0);
	for (;;)
	{
		imshow("image", isColor ? image : gray);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "Exiting ...\n";
			break;
		}
		if (c == 'r')
		{
			cout << "Original image is restored\n";
			srcImage.copyTo(image);
			cvtColor(image, gray, CV_BGR2GRAY);
			mask = Scalar::all(0);
		}
	}
	return 0;
}
