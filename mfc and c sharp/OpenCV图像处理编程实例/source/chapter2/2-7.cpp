// 功能：代码 2-7 图像灰度化
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main( )
{
  // 读取源图像并转化为灰度图像
  cv::Mat srcImage = cv::imread("..\\images\\pool.jpg");
  if( !srcImage.data ) 
      return 1;
  // 读取源图像并转化为灰度图像
  cv::Mat srcGray;
  cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
  // 显示源图像及灰度图像
  cv::imshow("srcImage", srcImage);
  cv::imshow("srcGray", srcGray);
  cv::waitKey(0);
  return 0;
}
