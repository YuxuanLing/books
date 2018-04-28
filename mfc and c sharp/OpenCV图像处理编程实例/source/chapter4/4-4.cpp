// 功能：代码 4-4 图像金字塔操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
// 图像金子塔采样操作
void Pyramid(cv::Mat srcImage)
{
  // 根据图像源尺寸判断是否需要缩放
  if(srcImage.rows > 400 && srcImage.cols > 400)
    cv::resize(srcImage, srcImage, cv::Size(), 0.5,0.5);
  else
    cv::resize(srcImage, srcImage, cv::Size(), 1,1);
  cv::imshow("srcImage", srcImage);
  cv::Mat pyrDownImage, pyrUpImage;
  // 下采样过程
  pyrDown(srcImage, pyrDownImage, 
    cv::Size(srcImage.cols/2, srcImage.rows/2));
  cv::imshow("pyrDown", pyrDownImage);
  // 上采样过程
  pyrUp(srcImage, pyrUpImage, 
    cv::Size(srcImage.cols*2, srcImage.rows*2));
  cv::imshow("pyrUp", pyrUpImage);
  // 对下采样过程重构
  cv::Mat pyrBuildImage;
  pyrUp(pyrDownImage, pyrBuildImage, 
    cv::Size(pyrDownImage.cols*2, pyrDownImage.rows*2));
  cv::imshow("pyrBuildImage", pyrBuildImage);
  // 比较重构性能
  cv::Mat diffImage;
  cv::absdiff(srcImage, pyrBuildImage, diffImage);
  cv::imshow("diffImage", diffImage);
  cv::waitKey(0);
}
int main()
{ 
  cv::Mat srcImage=cv::imread("..\\images\\flower3.jpg");
  if( !srcImage.data )
      return -1; 
  Pyramid(srcImage);
  return 0;
}
