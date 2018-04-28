// 功能：代码 2-31 RGB 转 HSV
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main()
{
	// 图像源读取及判断
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)   
       return -1;
    cv::imshow("srcImage", srcImage);
    cv::Mat image_hsv, image_H, image_S, image_V, image_col;
    // HSV颜色空间转换
    cv::cvtColor(srcImage, image_hsv, CV_BGR2HSV);
    cv::imshow("image_hsv", image_hsv);
    // YCrCb颜色空间转换
	cv::cvtColor(srcImage, image_col,  CV_BGR2YCrCb);
	cv::imshow("image_YCrCb", image_col);
	// HLS颜色空间转换
	cv::cvtColor(srcImage, image_col, CV_BGR2HLS);
	cv::imshow("image_HLS", image_hsv);
	// Lab颜色空间转换
	cv::cvtColor(srcImage, image_col, CV_BGR2Lab);
	cv::imshow("image_Lab", image_col);    
    // 分离HSV各个通道
    std::vector<cv::Mat> hsvChannels; 
    cv::split(image_hsv,hsvChannels);
    // 0通道为H分量，1通道为S分量，2通道为V分量
    image_H = hsvChannels[0];
    image_S = hsvChannels[1];
    image_V = hsvChannels[2];
    // 分别显示各通道图像
    cv::imshow("image_H", image_H);
    cv::imshow("image_S", image_S);
    cv::imshow("image_V", image_V);
    cv::waitKey(0);
	return 0;
}
