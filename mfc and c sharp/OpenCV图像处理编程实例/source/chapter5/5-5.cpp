// 功能：5-5 Sobel 边缘检测主程序
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
int main()
{
    cv::Mat srcImage= cv::imread("lena.jpg", 0);
	if (!srcImage.data)   
       return -1;
    cv::imshow("srcImage", srcImage);
    cv::Mat resultImage;
    // 非极大值抑制细化竖直sobel检测
    SobelVerEdge(srcImage,resultImage);
    cv::imshow("resultImage", resultImage);
    cv::Mat resultImage2;
    // 图像直接卷积实现sobel检测
    sobelEdge(srcImage, resultImage2, 100);
    cv::imshow("resultImage2", resultImage2);
    cv::Mat resultImage3;
    int flag = 2;
    // 图像卷积下非极大值抑制
    sobelOptaEdge(srcImage, resultImage3,2);
    cv::imshow("resultImage3", resultImage3);
    cv::waitKey(0);
	return 0;
}
