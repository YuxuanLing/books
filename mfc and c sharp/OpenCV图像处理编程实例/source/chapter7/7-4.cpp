// 功能：代码 7-4 均值漂移图像分割
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
//颜色通道分离
static void MergeSeg(Mat& img
	, const Scalar& colorDiff = Scalar::all(1))
{
	CV_Assert(!img.empty());
	RNG rng = theRNG();
	// 定义掩码图像
	Mat mask(img.rows + 2, img.cols + 2, 
		CV_8UC1, Scalar::all(0));
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)
			{
				// 颜色定义
				Scalar newVal(rng(256), rng(256), rng(256));
				// 泛洪合并
				floodFill(img, mask, Point(x, y)
					, newVal, 0, colorDiff, colorDiff);
			}
		}
	}
}
int main(int argc, char** argv)
{
	cv::Mat srcImg = imread("..\\images\\sea.jpg");
	if (srcImg.empty())
		return -1;
	// 参数设定
	int spatialRad = 20;
	int colorRad = 20;
	int maxPyrLevel = 6;
	cv::Mat resImg;
	// 均值漂移分割
	pyrMeanShiftFiltering(srcImg, resImg, 
		spatialRad, colorRad, maxPyrLevel);
	// 颜色通道分离合并
	MergeSeg(resImg, Scalar::all(2));
	cv::imshow("src", srcImg);
	cv::imshow("resImg", resImg);
	cv::waitKey();
	return 0;
}
