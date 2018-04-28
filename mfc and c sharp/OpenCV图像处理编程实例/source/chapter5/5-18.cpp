// 功能：代码 5-18 霍夫圆检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
int main(int argc, char** argv)
{
	cv::Mat srcImage = imread("..\\images\\circle.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	// 转换为灰度图像
	cv::Mat src_gray;
	cvtColor(srcImage, src_gray, CV_BGR2GRAY);
	// 高斯平滑滤波
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	// 霍夫圆检测
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 
		1, src_gray.rows / 8, 200, 100, 0, 0);
	// 将得到的结果绘图
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// 检测圆中心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// 检测圆轮廓
		circle(srcImage, center, radius, Scalar(120, 120, 120), 3, 8, 0);
	}
	cv::imshow("HoughResult", srcImage);
	cv::waitKey(0);
	return 0;
}
