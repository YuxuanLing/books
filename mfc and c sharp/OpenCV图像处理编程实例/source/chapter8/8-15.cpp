// 功能：代码 8-15 MSER 候选车牌区域检测s
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
// Mser车牌目标检测
std::vector<cv::Rect> mserGetPlate(cv::Mat srcImage)
{
	// HSV空间转换
	cv::Mat gray, gray_neg;
	cv::Mat hsi;
	cv::cvtColor(srcImage, hsi, CV_BGR2HSV);
	// 通道分离
	std::vector<cv::Mat> channels;
	cv::split(hsi, channels);
	// 提取h通道
	gray = channels[1];
	// 灰度转换 
	cv::cvtColor(srcImage, gray, CV_BGR2GRAY);
	// 取反值灰度
	gray_neg = 255 - gray;
	std::vector<std::vector<cv::Point> > regContours;
	std::vector<std::vector<cv::Point> > charContours;
	
	// 创建MSER对象
	cv::Ptr<cv::MSER> mesr1 = cv::MSER::create(2, 10, 5000, 0.5, 0.3);
	cv::Ptr<cv::MSER> mesr2 = cv::MSER::create(2, 2, 400, 0.1, 0.3);
	std::vector<cv::Rect> bboxes1;
	std::vector<cv::Rect> bboxes2;
	// MSER+ 检测
	mesr1->detectRegions(gray, regContours, bboxes1);
	// MSER-操作
	mesr2->detectRegions(gray_neg, charContours, bboxes2);
	
	cv::Mat mserMapMat =
		cv::Mat::zeros(srcImage.size(), CV_8UC1);
	cv::Mat mserNegMapMat =
		cv::Mat::zeros(srcImage.size(), CV_8UC1);
	
	for (int i = (int)regContours.size() - 1; i >= 0; i--)
	{
		// 根据检测区域点生成mser+结果
		const std::vector<cv::Point>& r = regContours[i];
		for (int j = 0; j < (int)r.size(); j++)
		{
			cv::Point pt = r[j];
			mserMapMat.at<unsigned char>(pt) = 255;
		}
	}
	// MSER- 检测
	for (int i = (int)charContours.size() - 1; i >= 0; i--)
	{
		// 根据检测区域点生成mser-结果
		const std::vector<cv::Point>& r = charContours[i];
		for (int j = 0; j < (int)r.size(); j++)
		{
			cv::Point pt = r[j];
			mserNegMapMat.at<unsigned char>(pt) = 255;
		}
	}
	// mser结果输出
	cv::Mat mserResMat;
	// mser+与mser-位与操作
	mserResMat = mserMapMat & mserNegMapMat;
	cv::imshow("mserMapMat", mserMapMat);
	cv::imshow("mserNegMapMat", mserNegMapMat);
	cv::imshow("mserResMat", mserResMat);
	// 闭操作连接缝隙
	cv::Mat mserClosedMat;
	cv::morphologyEx(mserResMat, mserClosedMat,
		cv::MORPH_CLOSE, cv::Mat::ones(1, 20, CV_8UC1));
	cv::imshow("mserClosedMat", mserClosedMat);
	// 寻找外部轮廓
	std::vector<std::vector<cv::Point> > plate_contours;
	cv::findContours(mserClosedMat, plate_contours,
		CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	// 候选车牌区域判断输出
	std::vector<cv::Rect> candidates;
	for (size_t i = 0; i != plate_contours.size(); ++i)
	{
		// 求解最小外界矩形
		cv::Rect rect = cv::boundingRect(plate_contours[i]);
		// 宽高比例
		double wh_ratio = rect.width / double(rect.height);
		// 不符合尺寸条件判断
		if (rect.height > 20 && wh_ratio > 4 && wh_ratio < 7)
			candidates.push_back(rect);
	}
	return  candidates;
}
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\car.jpg");
	if (srcImage.empty())
		return-1;
	// 候选车牌区域检测
	std::vector<cv::Rect> candidates;
	candidates = mserGetPlate(srcImage);
	// 车牌区域显示
	for (int i = 0; i < candidates.size(); ++i) {
		cv::imshow("rect", srcImage(candidates[i]));
		cv::waitKey();
	}
	return 0;
}
