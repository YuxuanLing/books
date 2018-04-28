// 功能：代码 2-22 鼠标按键获取感兴趣区域 2
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
bool eventFlag = false; 
void MouseEvent(int event, int x, int y, int flags, void* data)
{
    cv::Mat tempImage = srcImage.clone();
    // 根据标志位判断当前按键有效性
    if(eventFlag)
    {
    	// 计算选取区域的大小
        roiRect.x = MIN(startPoint.x,x);
        roiRect.width=abs(x-startPoint.x);
        roiRect.height=abs(y-startPoint.y);
    }
    // 鼠标按下操作
    if(event == CV_EVENT_LBUTTONDOWN)
    {
    	// 鼠标左键按下 起始点获取
        eventFlag = true;
        startPoint = Point(x,y);
        roiRect = Rect(x,y,0,0);
    }
    // 鼠标抬起操作
    else if(event == CV_EVENT_LBUTTONUP)
    {
        eventFlag = false;
        //画出矩形框
        cv::imshow("ROI", tempImage(roiRect));
	    rectangle(tempImage,roiRect,Scalar(255,0,0),2,3,0);
	    cv::imshow("ROIing", tempImage );
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

