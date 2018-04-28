// 功能：代码 3-1 OTSU 二值化的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <stdio.h>
#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
// 大均法函数实现
int OTSU(cv::Mat srcImage)
{
	int nCols = srcImage.cols;
	int nRows = srcImage.rows;
	int threshold = 0;
	// 初始化统计参数
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	// 统计灰度级中每个像素在整幅图像中的个数 
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			nSumPix[(int)srcImage.at<uchar>(i, j)]++;
		}
	}
	// 计算每个灰度级占图像中的概率分布
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols * nRows);
	}
	// 遍历灰度级[0,255],计算出最大类间方差下的阈值  
	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 0; i < 256; i++)
	{
		// 初始化相关参数
		w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;
		for (int j = 0; j < 256; j++)
		{
			//背景部分 
			if (j <= i)
			{
				// 当前i为分割阈值，第一类总的概率  
				w0 += nProDis[j];
				u0_temp += j * nProDis[j];
			}
			//前景部分   
			else
			{
				// 当前i为分割阈值，第一类总的概率
				w1 += nProDis[j];
				u1_temp += j * nProDis[j];
			}
		}
		// 分别计算各类的平均灰度 
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		delta_temp = (float)(w0 *w1* pow((u0 - u1), 2));
		// 依次找到最大类间方差下的阈值    
		if (delta_temp > delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}
	return threshold;
}
int main()
{
	// 图像读取及判断
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return 1;
	// 灰度转换
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::imshow("srcGray", srcGray);
	// 调用OTSU二值化算法得到阈值
	int  ostuThreshold = OTSU(srcGray);
	std::cout << ostuThreshold << std::endl;
	// 定义输出结果图像
	cv::Mat otsuResultImage =
		cv::Mat::zeros(srcGray.rows, srcGray.cols, CV_8UC1);
	// 利用得到的阈值实现二值化操作
	for (int i = 0; i < srcGray.rows; i++)
	{
		for (int j = 0; j < srcGray.cols; j++)
		{
			// 满足大于阈值ostuThreshold置255
			if (srcGray.at<uchar>(i, j) > ostuThreshold)
				otsuResultImage.at<uchar>(i, j) = 255;
			else
				otsuResultImage.at<uchar>(i, j) = 0;
		}
	}
	cv::imshow("otsuResultImage", otsuResultImage);
	cv::waitKey(0);
	return 0;
}
