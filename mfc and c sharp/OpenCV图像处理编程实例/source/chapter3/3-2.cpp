// 功能：代码 3-2 threshold 二值化的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
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
  cv::Mat dstImage;
  // 初始化阈值参数
  int thresh = 130; 
  // 初始化阈值化处理的类型 
  /* 0: 二进制阈值 1: 反二进制阈值 2: 截断阈值
     3: 0阈值   4: 反0阈值*/
  int threshType = 0; 
  // 预设最大值
  const int maxVal = 255;
  // 固定阈值化操作
  cv::threshold( srcGray, dstImage, thresh, 
          maxVal , threshType );
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
}
