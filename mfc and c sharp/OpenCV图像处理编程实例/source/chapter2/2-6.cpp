// 功能：代码 2-6 图像读取显示保存操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main( )
{
  // 读取图像源
  cv::Mat srcImage = cv::imread("..\\images\\pool.jpg");
  if( srcImage.empty() ) 
      return -1;
  // 转为灰度图像
  cv::Mat srcGray;
  cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
  cv::imshow("srcGray", srcGray);
  // 均值平滑
  cv::Mat blurDstImage;
  blur( srcGray, blurDstImage, cv::Size(5,5),
       cv::Point(-1,-1) ); 
  cv::imshow("blurDstImage", blurDstImage);
  // 写入图像文件
  cv::imwrite("blurDstImage.png", blurDstImage);
  cv::waitKey(0);
  return 0;
}
