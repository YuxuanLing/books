// 功能：代码 5-27 Shi-Tomasi 角点检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return -1;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	// 角点检测参数设置
	vector<Point2f> vecCorners;
	// 可允许接受的角点最差质量
	double qualityLevel = 0.01;
	// 角点间的最小的欧式距离
	double minDistance = 10;
	// 像素邻域中计算协方差矩阵窗口的尺寸
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	// 检测到角点输出的最大数目
	int maxCorners = 50;
	int maxTrackbar = 100;
	cv::Mat result = srcImage.clone();
	// 调用函数进行Shi-Tomasi角点检测
	goodFeaturesToTrack(srcGray,
		vecCorners,maxCorners,
		qualityLevel,minDistance,
		Mat(),blockSize,useHarrisDetector,k);
	std::cout << "Corners:" << vecCorners.size() << endl;
	// 绘制检测角点
	for (int i = 0; i < vecCorners.size(); i++)
	{
		circle(result, vecCorners[i], 4, 
			Scalar(0, 0, 255), 2);
	}
	cv::imshow("srcImage", srcImage);
	cv::imshow("result", result);
	cv::waitKey(0);
	return(0);
}
