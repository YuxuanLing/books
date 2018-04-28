// 功能：代码 6-5 形态学滤波实现角点检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// 定义结构元素
	Mat CrossMat(5, 5, CV_8U, Scalar(0));
	Mat diamondMat(5, 5, CV_8U, Scalar(1));
	Mat squareMat(5, 5, CV_8U, Scalar(1));
	Mat x(5, 5, CV_8U, Scalar(0));
	//  十字形形状  
	for (int i = 0; i<5; i++)
	{
		CrossMat.at<uchar>(2, i) = 1;
		CrossMat.at<uchar>(i, 2) = 1;
	}
	// 菱形形状
	diamondMat.at<uchar>(0, 0) = 0;
	diamondMat.at<uchar>(0, 1) = 0;
	diamondMat.at<uchar>(1, 0) = 0;
	diamondMat.at<uchar>(4, 4) = 0;
	diamondMat.at<uchar>(3, 4) = 0;
	diamondMat.at<uchar>(4, 3) = 0;
	diamondMat.at<uchar>(4, 0) = 0;
	diamondMat.at<uchar>(4, 1) = 0;
	diamondMat.at<uchar>(3, 0) = 0;
	diamondMat.at<uchar>(0, 4) = 0;
	diamondMat.at<uchar>(0, 3) = 0;
	diamondMat.at<uchar>(1, 4) = 0;
	// X形状
	for (int i = 0; i<5; i++){
		x.at<uchar>(i, i) = 1;
		x.at<uchar>(4 - i, i) = 1;
	}
	// 第1步：十字形对原图进行膨胀
	Mat result;
	dilate(srcGray, result, CrossMat);
	// 第2步：菱形对上步进行腐蚀
	erode(result, result, diamondMat);
	Mat result2;
	// 第3步：X形对原图进行腐蚀
	dilate(srcGray, result2, x);
	// 第4步：正方形对上步进行腐蚀
	erode(result2, result2, squareMat);
	// 第4步：计算差值
	absdiff(result2, result, result);
	threshold(result, result, 40, 255, THRESH_BINARY);
	// 绘图
	for (int i = 0; i < result.rows; i++)
	{
		// 获取行指针
		const uchar* data = result.ptr<uchar>(i);
		for (int j = 0; j < result.cols; j++)
		{
			// 如果是角点 则进行绘制圆圈
			if (data[j])
			   circle(srcImage, Point(j, i), 8, 
			   	Scalar(0, 255, 0));
		}
	}
	cv::imshow("result", result);
	cv::imshow("srcImage", srcImage);
	cv::waitKey(0);
	return 0;
}
