// 功能：代码2-3 Mat 类常用函数用法示例
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main( )
{
  cv::Mat Image1( 10, 8, CV_8UC1, cv::Scalar(5) );
  // 矩阵行列数获取
  std::cout << "Image1 row: " << Image1.rows << std::endl;
  std::cout << "Image1 col: " << Image1.cols << std::endl;
  // 取指定行列元素
  std::cout << Image1.rowRange(1,3) << std::endl;
  std::cout << Image1.colRange(2,4) << std::endl;
  // 创建 8X8 复数矩阵1+5j
  cv::Mat Image2(8, 8, CV_32FC2, cv::Scalar(1,5));  
  // 利用create方法重新创建 10X10的8位无符号3通道矩阵
  Image2.create(10, 10, CV_8UC(3));
  std::cout <<"Image2 channels:" << 
         Image2.channels() << std::endl;
  // 矩阵类型转换
  Image2.convertTo(Image2, CV_32F);
  std::cout <<"Image2 depth:" << Image2.depth() << std::endl;
  // zeros 创建矩阵
  cv::Mat Image3 = 
      cv::Mat::zeros(Image2.rows, Image2.cols, CV_8UC1); 
  // srcImage1的第4行元素变换成srcImage1的第5行元素乘2
  Image1.row(4) = Image1.row(5) * 2; 
  std::cout << Image1 << std::endl;
  // 创建srcImage4矩阵赋值为srcImage1的第4列
  cv::Mat Image4 = Image1.col(4);  
  std::cout << Image4 << std::endl;
 // 创建srcImage1矩阵的第一列拷贝到srcImage4中
  Image1.col(1).copyTo(Image4);
  std::cout << Image4 << std::endl;
  return 0;
} 
