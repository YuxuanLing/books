// 功能：代码 5-28 颜色圆检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <vector>
int main() 
{
	cv::Mat srcImage = cv::imread("..\\images\\circles.png");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage = srcImage.clone();
	// 中值滤波
	cv::medianBlur(srcImage, srcImage, 3);
	// 转换成hsv颜色空间
	cv::Mat hsvImage;
	cv::cvtColor(srcImage, hsvImage, cv::COLOR_BGR2HSV);
	cv::imshow("hsvImage", hsvImage);
	// 颜色阈值化处理
	cv::Mat lowTempMat;
	cv::Mat upperTempMat;
	// 低阈值限定
	cv::inRange(hsvImage, cv::Scalar(0, 100, 100), 
		cv::Scalar(10, 255, 255), lowTempMat);
	// 高阈值限定
	cv::inRange(hsvImage, cv::Scalar(160, 100, 100),
	    cv::Scalar(179, 255, 255), upperTempMat);
	cv::imshow("lowTempMat", lowTempMat);
	cv::imshow("upperTempMat", upperTempMat);
	// 颜色阈值限定合并
	cv::Mat redTempMat;
	cv::addWeighted(lowTempMat, 1.0, upperTempMat, 
		1.0, 0.0, redTempMat);
	// 高斯平滑
	cv::GaussianBlur(redTempMat, redTempMat, cv::Size(9, 9), 2, 2);
	// 霍夫变换
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(redTempMat, circles, CV_HOUGH_GRADIENT,
		1, redTempMat.rows / 8, 100, 20, 0, 0);
	// 颜色圆检测结果判断
	if (circles.size() == 0) 
		return 1;
	for (int i = 0; i < circles.size(); ++i)
	{
		// 绘制检测到颜色圆
		cv::Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);
		cv::circle(resultImage, center, radius, 
			cv::Scalar(0, 255, 0), 5);
	}
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
