// 功能：代码 5-20 凸包及缺陷检测
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
Mat srcImage, srcGary;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void*)
{
	Mat srcTemp = srcImage.clone();
	Mat threMat;
	// 轮廓检测参数
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// 阈值化操作
	threshold(srcGary, threMat, thresh, 255, THRESH_BINARY);
	// 轮廓检测
	findContours(threMat, contours, hierarchy,
		 CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 凸包及缺陷检测参数
	vector<vector<Point> > pointHull(contours.size());
	vector<vector<int> >   intHull(contours.size());
	vector<vector<Vec4i> > hullDefect(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		// Point类型凸包检测
		convexHull(Mat(contours[i]), pointHull[i], false);
		// int类型凸包检测
		convexHull(Mat(contours[i]), intHull[i], false);
		// 凸包缺陷检测
		convexityDefects(Mat(contours[i]), intHull[i], hullDefect[i]);
	}
	// 绘制凸包及缺陷检测
	Mat drawing = Mat::zeros(threMat.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), 
			rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1,
		 	8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, pointHull, i, color, 
			1, 8, vector<Vec4i>(), 0, Point());
		// 绘制缺陷
		size_t count = contours[i].size();
		if (count < 300)
			continue;
		// 凸包缺陷迭代器设置
		vector<Vec4i>::iterator iterDefects = hullDefect[i].begin();
		// 遍历得到4个特征量
		while (iterDefects != hullDefect[i].end()) {
			Vec4i& v = (*iterDefects);
			// 起始位置
			int startidx = v[0];
			Point ptStart(contours[i][startidx]); 
			// 终止位置
			int endidx = v[1];
			Point ptEnd(contours[i][endidx]); 
		    // 内凸壳的最远的点缺陷
			int faridx = v[2];
			Point ptFar(contours[i][faridx]);
			// 凸包之间的最远点
			int depth = v[3] / 256;
			if (depth > 20 && depth < 80)
			{
				line(drawing, ptStart, ptFar, CV_RGB(0, 255, 0), 2);
				line(drawing, ptEnd, ptFar, CV_RGB(0, 255, 0), 2);
				circle(drawing, ptStart, 4, Scalar(255, 0, 100), 2);
				circle(drawing, ptEnd, 4, Scalar(255, 0, 100), 2);
				circle(drawing, ptFar, 4, Scalar(100, 0, 255), 2);
			}
			iterDefects++;
		}
	}
	cv::imshow("result", drawing);
}
int main()
{
	srcImage = imread("..\\images\\hand2.jpg");
	if (!srcImage.data)   
       return -1;
	cvtColor(srcImage, srcGary, CV_BGR2GRAY);
	blur(srcGary, srcGary, Size(3, 3));
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, srcImage);
	createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return(0);
}
