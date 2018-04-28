// 功能：代码 3-3 adaptiveThreshold 阈值化的实现
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
  cv::Mat dstImage;
  // 初始化自适应阈值参数
  int blockSize = 5;  
  int constValue = 10;  
  const int maxVal = 255;
    /* 自适应阈值算法
  0：ADAPTIVE_THRESH_MEAN_C
  1: ADAPTIVE_THRESH_GAUSSIAN_C
  阈值类型
  0: THRESH_BINARY
  1: THRESH_BINARY_INV */
  int adaptiveMethod = 0;
  int thresholdType = 1;
  // 图像自适应阈值操作
  cv::adaptiveThreshold(srcGray, dstImage, 
    maxVal, adaptiveMethod, 
    thresholdType, blockSize, 
    constValue);   
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
}
