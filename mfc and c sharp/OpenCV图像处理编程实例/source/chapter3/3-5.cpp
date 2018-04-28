// 功能：代码 3-5 半阈值法的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream> 
using namespace std;
using namespace cv;
int main( )
{
  // 读取源图像及判断
  cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
  if( !srcImage.data ) 
      return 1;
  // 转化为灰度图像
  cv::Mat srcGray;
  cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
  cv::imshow("srcGray", srcGray);
  // 初始化阈值参数
  const int maxVal = 255;
  int thresholdVal  = 150;
  cv::Mat dstTempImage, dstImage;
  // 阈值对源灰度图像进行阈值化操作
  cv::threshold( srcGray, dstTempImage, 
             thresholdVal, 255, cv::THRESH_BINARY );
  // 矩阵与运算得到二值化结果
  cv::bitwise_and( srcGray, dstTempImage, dstImage );
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
} 
