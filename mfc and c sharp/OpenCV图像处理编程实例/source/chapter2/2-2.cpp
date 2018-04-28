// 功能：代码 2-2 新建 Mat 类对象方法示例
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main( )
{
  // 方法1：创建无初始化矩阵
  cv::Mat image1; 
  // 方法2：创建6行6列类型为8位单通道矩阵
  cv::Mat image2( 6, 6, CV_8UC1 );
  // 方法3：创建大小为7x7类型为8位3通道矩阵
  cv::Mat image3( cv::Size(7,7), CV_8UC3 );
  // 方法4：创建一个用1+3j填充的 8x8 复矩阵
  cv::Mat image4( 8, 8, CV_32FC2, cv::Scalar(1,3) );
  // 方法5：创建大小为 9x9 类型为8位3通道矩阵
  cv::Mat image5( cv::Size(9,9), CV_8UC3, cv::Scalar(1,2,3) );
  //方法6：创建以image2赋值给image6，共用数据对象
  cv::Mat image6( image2 );
  // 输出矩阵结果
  std::cout << image1 << std::endl;
  std::cout << image2 << std::endl;
  std::cout << image3 << std::endl;
  std::cout << image4 << std::endl;
  std::cout << image5 << std::endl;
  std::cout << image6 << std::endl;
  return 0;
}
