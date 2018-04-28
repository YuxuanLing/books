// 功能：代码 7-8 肤色检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>   
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
#include <vector>     
int main()
{
	cv::Mat srcImage, resultMat;
	srcImage = cv::imread("..\\images\\hand1.jpg");
	if (srcImage.empty())
		return -1;
	// 构建椭圆模型   
	cv::Mat skinMat = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);
	ellipse(skinMat, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
		43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);
	// 结构元素定义
	cv::Mat struElmen = getStructuringElement(cv::MORPH_RECT,
		cv::Size(3, 3), cv::Point(-1, -1));
	cv::Mat YcrcbMat;
	cv::Mat tempMat = cv::Mat::zeros(srcImage.size(), CV_8UC1);
	// 颜色空间转换YCrCb
	cvtColor(srcImage, YcrcbMat, CV_BGR2YCrCb);
	// 椭圆皮肤模型检测
	for (int i = 0; i < srcImage.rows; i++)
	{
		uchar* p = (uchar*)tempMat.ptr<uchar>(i);
		cv::Vec3b* ycrcb = (cv::Vec3b*)YcrcbMat.ptr<cv::Vec3b>(i);
		for (int j = 0; j < srcImage.cols; j++)
		{
			// 颜色判断
			if (skinMat.at<uchar>(ycrcb[j][1], ycrcb[j][2]) > 0)
				p[j] = 255;
		}
	}
	// 形态学闭操作     
	morphologyEx(tempMat, tempMat, cv::MORPH_CLOSE, struElmen);
	// 定义轮廓参数
	std::vector< std::vector<cv::Point> > contours;
	std::vector< std::vector<cv::Point> > resContours;
	std::vector< cv::Vec4i > hierarchy;
	// 连通域查找
	findContours(tempMat, contours, hierarchy,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	// 筛选伪轮廓   
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (fabs(contourArea(cv::Mat(contours[i]))) > 1000)
			resContours.push_back(contours[i]);
	}
	tempMat.setTo(0);
	// 绘制轮廓
	drawContours(tempMat, resContours, -1,
		cv::Scalar(255, 0, 0), CV_FILLED);
	srcImage.copyTo(resultMat, tempMat);
	imshow("srcImage", srcImage);
	imshow("resultMat", resultMat);
	cv::waitKey(0);
	return 0;
}
