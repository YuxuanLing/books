// 功能：代码 2-21 鼠标按键获取感兴趣区域 1
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 适用于单次鼠标操作
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
// 全局变量图像源
cv::Mat srcImage;
// 所选矩形区域  
cv::Rect roiRect;  
// 起始点
cv::Point startPoint; 
 // 终止点
cv::Point endPoint; 
// 完成所选区域标志位
bool downFlag = false; 
bool upFlag = false;
void MouseEvent(int event, int x, int y, int flags, void* data)
{
    // 鼠标左键按下 获取起始点 
	if(event == EVENT_LBUTTONDOWN)
	{	
		downFlag = true;
		startPoint.x = x;
		startPoint.y = y;
	}
	// 鼠标拖到松开 获取终止点
	if(event == EVENT_LBUTTONUP)
	{	
		upFlag = true;
		endPoint.x = x;
		endPoint.y = y;
	}
	// 显示拖到图像区域
	if(downFlag == true && upFlag == false)
	{
		Point tempPoint;
		tempPoint.x = x;
		tempPoint.y = y;
		// 用于显示图像生成
		cv::Mat tempImage = srcImage.clone();
		cv::rectangle(tempImage, startPoint, tempPoint,
           Scalar(255, 0, 0),2,3,0);
		cv::imshow("ROIing", tempImage);
	}	// 选择区域生成
	if(downFlag == true && upFlag == true)
	{
		// 获取选择区域的ROI
		roiRect.width = abs(startPoint.x - endPoint.x);
		roiRect.height = abs(startPoint.y - endPoint.y);
		roiRect.x = min(startPoint.x, endPoint.x);
		roiRect.y = min(startPoint.y, endPoint.y); 
		cv::Mat roiMat(srcImage, roiRect);
		imshow("ROI", roiMat);
		downFlag = false;
		upFlag = false;
	}
	cv::waitKey(0);    
}
int main(int argc, char** argv)
{
	// 读取图像及判断是否正确读入
    srcImage =  cv::imread("..\\images\\flower3.jpg");
    if (srcImage.empty())
        return -1;
    // 回调事件响应
    cv::namedWindow("ROIing");
    cv::imshow("ROIing", srcImage);
    cv::setMouseCallback("ROIing", MouseEvent, 0);
    cv::waitKey(0);
    return 0;
}

