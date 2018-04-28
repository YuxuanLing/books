// 功能：代码 5-19 连通区域轮廓检测
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
Mat srcImage; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// 用Canny算子检测边缘
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	// 寻找轮廓
	findContours(canny_output, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/// 绘出轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	// 显示轮廓结果
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int main()
{
	cv::Mat srcImage = 
      cv::imread("..\\images\\circle.jpg");
 	if (!srcImage.data)   
       return -1;
	// 转成灰度并平滑
	cvtColor(srcImage, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	// 创建窗体
	char* source_window = "srcImage";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, srcImage);
	// 滑动条控制canny阈值
	createTrackbar(" threth:", "srcImage", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	cv::waitKey(0);
	return(0);
}
