// 功能：代码1-4  测试OpenCV示例2
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 头文件
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
// 使用标准的cv库
using namespace cv;
int main( )
{
  // 读取源图像并转化为灰度图像
  Mat srcImage = cv::imread("..\\images\\flower.jpg");
  // 判断文件是否读入正确
  if( !srcImage.data ) 
	      return 1;
  // 图像显示
  imshow("srcImage", srcImage);
  // 等待键盘键入
  waitKey(0);
  return 0;
}
