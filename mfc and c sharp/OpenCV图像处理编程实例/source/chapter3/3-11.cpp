// 功能：代码 3-11 彩色直方图均衡化实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
int main()
{
  // 图像获取及验证
  cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
  if( !srcImage.data ) 
    return 1;
  // 存储彩色直方图及图像通道向量
  cv::Mat colorHeqImage;   
  std::vector<cv::Mat> BGR_plane;  
  // 对BGR通道进行分离
  cv::split(srcImage,BGR_plane);
  // 分别对BGR进行直方图均衡化
  for(int i=0; i < BGR_plane.size(); i++)
      cv::equalizeHist(BGR_plane[i], BGR_plane[i]);
  // 合并对应各个通道
  cv::merge(BGR_plane,colorHeqImage);
     cv::imshow("srcImage", srcImage);
  cv::imshow("colorHeqImage", colorHeqImage);
  cv::waitKey(0);
  return 0;
}
