// 功能：代码 4-10-14 滤波实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main(){
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg",0);
     if(srcImage.empty())
          return-1;
    cv::imshow("srcImage",srcImage);
    cv::Mat resBlurMat, resMedMat, resGauMat, resBilMat;
    // 均值滤波
    blur(srcImage, resBlurMat, cv::Size(5, 5), cv::Point(-1,-1));
    // 中值滤波
    medianBlur (srcImage, resMedMat, 5);
    // 高斯滤波
    GaussianBlur(srcImage,resGauMat,cv::Size(3,3),0,0);
    // 双边滤波
    bilateralFilter(srcImage,resBilMat,7,20.0,5.0);
    cv::imshow("resBlurMat", resBlurMat);
    cv::imshow("resMedMat", resMedMat);
    cv::imshow("resGauMat", resGauMat);
    cv::imshow("resBilMat", resBilMat);
    cv::waitKey(0);
}
