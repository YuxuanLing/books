// 功能：代码 3-19 distanceTransform 距离变换
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\sea.jpg"); 
    if( !srcImage.data ) 
 	   return -1;
    // 转换为灰度图像
    cv::Mat srcGray;
    cvtColor(srcImage, srcGray, CV_BGR2GRAY);  
    // 转换为二值图像
    cv::Mat srcBinary;
    threshold(srcGray, srcBinary, 160, 255,cv::THRESH_BINARY);
    // 距离变换
    cv::Mat dstImage;
    cv::distanceTransform(srcBinary, dstImage, CV_DIST_L2,
         CV_DIST_MASK_PRECISE);
    // 归一化矩阵
    cv::normalize(dstImage, dstImage, 0, 1., cv::NORM_MINMAX);   
    cv::imshow("srcBinary", srcBinary);
    cv::imshow("dstImage", dstImage);
    cv::waitKey(0);
    return 0;
}
