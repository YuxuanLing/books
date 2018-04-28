// 功能：代码 5-21 最小矩形与圆生成
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 5-22 轮廓边界矩形与圆
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
#include <stdio.h>
using namespace cv;
using namespace std;
// 计算外接矩形与圆轮廓
void  cacBounding(cv::Mat src)
{
	RNG rng(12345);
	Mat threMat;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// 二值化操作
	threshold(src, threMat, 120, 255, THRESH_BINARY);
	cv::imshow("threMat", threMat);
	// 计算边界轮廓
	findContours(threMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 多边形逼近轮廓,获取矩形和圆形边界框
	vector<vector<Point> > conPoint(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		// 多边形近似
		approxPolyDP(Mat(contours[i]), conPoint[i], 3, true);
		// 最小外接矩形计算
		boundRect[i] = boundingRect(Mat(conPoint[i]));
		// 最小封闭圆生成
		minEnclosingCircle(conPoint[i], center[i], radius[i]);
	}
	// 绘图显示
	Mat resultMat = Mat::zeros(threMat.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		// 随机生成颜色
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		// 绘制多边形轮廓
		drawContours(resultMat, conPoint, i, color,
			1, 8, vector<Vec4i>(), 0, Point());
		// 绘制多边形包围的矩形框
		rectangle(resultMat, boundRect[i].tl(),
		    boundRect[i].br(), color, 2, 8, 0);
		// 绘制多边形圆形框
		circle(resultMat, center[i], (int)radius[i],
		   color, 2, 8, 0);
	}
	cv::imshow("boundRectResult", resultMat);
}
// 计算可倾斜外接矩形与圆轮廓
void  cacBoundRectRandomDirection(cv::Mat src)
{
	RNG rng(12345);
	Mat threMat;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//  二值化操作
	threshold(src, threMat, 120, 255, THRESH_BINARY);
	// 计算边界轮廓
	findContours(threMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 对每个找到的轮廓创建可倾斜的边界框和椭圆
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		// 计算最小面积矩形
		minRect[i] = minAreaRect(Mat(contours[i]));
		// 求外接轮廓的椭圆
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}
	// 绘出轮廓及其可倾斜的边界框和边界椭圆
	Mat resultMat = Mat::zeros(threMat.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		// 随机生成颜色
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		// 边界轮廓绘制
		drawContours(resultMat, contours, i, color, 1, 8,
		    vector<Vec4i>(), 0, Point());
		// 绘制边界椭圆
		ellipse(resultMat, minEllipse[i], color, 2, 8);
		// 绘制边界矩形
		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(resultMat, rect_points[j], rect_points[(j + 1) %
			 4], color, 1, 8);
	}
	imshow("resultMat", resultMat);
}
int main()
{
	cv::Mat srcImage=imread("..\\images\\boudingRect.jpg");
	if (!srcImage.data)
		return -1;
	// 转化成灰度图像并进行平滑
	cv::Mat srcGray, blurMat;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	blur(srcGray, blurMat, Size(3, 3));
	// cv::imshow( "blurMat", blurMat );
	// 计算外接矩形与圆轮廓
	cacBoundRectRandomDirection(blurMat);
    // 计算可倾斜外接矩形与圆轮廓
	cacBounding(blurMat);
	cv::imshow("srcImage", srcImage);
	cv::waitKey(0);
	return(0);
}
