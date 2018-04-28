// 功能：代码 7-5 Grabcut 图像分割
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;
// 全局变量区域
cv::Point point1, point2;
int drag = 0;
cv::Rect rect; 
cv::Mat srcImage, roiImg; 
bool select_flag = true;
cv::Mat rectimg;
vector<Point>Pf,Pb;
// 鼠标响应回调
void mouseHandler(int event, int x, int y, int flags, void* param)
{
    // 左键按下 
	if (event == CV_EVENT_LBUTTONDOWN && !drag)
	{
		point1 = Point(x, y);
		drag = 1;
	}
    // 鼠标移动
	else if (event == CV_EVENT_MOUSEMOVE && drag)
	{	
		Mat img1 = srcImage.clone();
		point2 = Point(x, y);
		rectangle(img1, point1, point2,
			 CV_RGB(255, 0, 0), 3, 8, 0);
		imshow("srcImage", img1);		
	}
    // 左键抬起与拖拽标志
	else if (event == CV_EVENT_LBUTTONUP && drag)
	{
		point2 = Point(x, y);
		rect = Rect(point1.x,point1.y,x-point1.x,y-point1.y);
		drag = 0;
		roiImg = srcImage(rect);		
	}
	// 右键按下
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		select_flag = false;
		drag = 0;
		imshow("ROI", roiImg);
	}
}
int main()
{		
	srcImage= imread("..\\images\\sea.jpg");
	if (srcImage.empty())
		return -1;
	// 定义前景与输出图像
	cv::Mat srcImage2 = srcImage.clone();
	cv::Mat foreground(srcImage.size(),
		CV_8UC3,cv::Scalar(255,255,255));
	cv::Mat result(srcImage.size(),CV_8UC1);
	// grabcut分割前景与背景
	cv::Mat fgMat,bgMat;
	namedWindow("srcImage",1);
	imshow("srcImage", srcImage);
	// 迭代次数
	int i = 20;
	std::cout<<"20 iters"<< std::endl;
    // 鼠标响应
	setMouseCallback("srcImage", mouseHandler, NULL);
	// 选择区域有效，按下esc退出
	while((select_flag==true) && (waitKey(0)!=27))
	{
		// 图割算法熟悉
		grabCut(srcImage,result,rect,bgMat,
			fgMat,i,GC_INIT_WITH_RECT);
		// 图像匹配
		cv::compare(result,cv::GC_PR_FGD,
			result,cv::CMP_EQ);
		// 生成前景图像
		srcImage.copyTo(foreground,result); 
		imshow("foreground",foreground);	
	}	
	cv::waitKey(0);
	return 0;
}