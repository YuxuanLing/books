// 功能：代码 2-18 鼠标事件示例
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
// 全局变量 
cv::Mat srcImage;
void MouseEvent(int event, int x, int y, int flags, void* data)
{
    char charText[30];
    cv::Mat tempImage, hsvImage;
    tempImage = srcImage.clone();
    // 左键按下移动显示RGB信息
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        cv::Vec3b p = tempImage.at<cv::Vec3b>(y,x);
        sprintf(charText, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
        // 写RGB文本信息到图像
	    cv::putText(tempImage, charText, cv::Point(8,20),
	           cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255,255,255));
        imwrite("..\\images\\RGBFlower4.jpg", tempImage);
    }
    // 右键按下移动显示HSV信息
    else if (event == CV_EVENT_RBUTTONDOWN)
    {
        // 转换成HSV图像
        cv::cvtColor(tempImage, hsvImage, CV_BGR2HSV);
        cv::Vec3b p = hsvImage.at<cv::Vec3b>(y,x);
        // 获取相应的通道值
        sprintf(charText, "H=%d, S=%d, V=%d", p[0], p[1], p[2]);
        // 写HSV文本信息到图像
    	cv::putText(tempImage, charText, cv::Point(8,20),
           cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255,255,255));
        imwrite("..\\images\\HSVFlower4.jpg", tempImage);
    }
    // 没有按下键显示对应坐标
    else
    {
	    // 移动鼠标显示坐标
	    sprintf(charText, "x=%d, y=%d", x, y);
	    // 写XY坐标文本信息到图像
    	cv::putText(tempImage, charText, cv::Point(8,20),
           cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255,255,255));
	    imwrite("..\\images\\NOFlower4.jpg", tempImage);
	}
    cv::imshow("srcImage", tempImage);
    
}
int main(int argc, char** argv)
{
	// 读取图像及判断是否正确读入
    srcImage =  cv::imread("..\\images\\flower4.jpg");
    if (srcImage.empty())
        return -1;
    // 回调事件响应
    cv::namedWindow("srcImage");
    cv::setMouseCallback("srcImage", MouseEvent, 0);
    cv::imshow("srcImage", srcImage);
    cv::waitKey(0);
    return 0;
}
