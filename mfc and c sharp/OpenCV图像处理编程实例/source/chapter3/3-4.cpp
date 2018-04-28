// 功能：代码 3-4 双阈值法的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main( )
{
  // 图像读取及判断
  cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
  if( !srcImage.data ) 
      return 1;
  // 灰度转换
  cv::Mat srcGray;
  cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
  cv::imshow("srcGray", srcGray);
  // 初始化阈值参数
  const int maxVal = 255;
  int low_threshold  = 150;
  int high_threshold = 210;
  cv::Mat dstTempImage1, dstTempImage2, dstImage;
  // 小阈值对源灰度图像进行阈值化操作
  cv::threshold( srcGray, dstTempImage1, 
       low_threshold, maxVal, cv::THRESH_BINARY );
  // 大阈值对源灰度图像进行阈值化操作
  cv::threshold( srcGray, dstTempImage2, 
       high_threshold, maxVal,cv::THRESH_BINARY_INV );
  // 矩阵与运算得到二值化结果
  cv::bitwise_and( dstTempImage1, 
      dstTempImage2, dstImage );
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
} 
