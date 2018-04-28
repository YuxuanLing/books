// 功能：代码 5-7 Laplace 边缘检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
int main()
{
  cv::Mat srcImage =
    cv::imread("..\\images\\building.jpg", 0);
  if (!srcImage.data)
    return -1;
  // 高斯平滑
  GaussianBlur(srcImage, srcImage, cv::Size(3, 3),
    0, 0, cv::BORDER_DEFAULT);
  cv::Mat dstImage;
  // 拉普拉斯变换
  Laplacian(srcImage, dstImage, CV_16S, 3);
  convertScaleAbs(dstImage, dstImage);
  cv::imshow("srcImage", srcImage);
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
}
