// 功能：代码 3-10 灰度直方图均衡化实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include <opencv2/opencv.hpp>
int main()
{
   cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
    if( !srcImage.data ) 
      return 1;
   cv::Mat srcGray;
   cv::cvtColor(srcImage, srcGray, CV_BGR2GRAY);
   cv::imshow("srcGray", srcGray);
   // 直方图均衡化
   cv::Mat heqResult;
   cv::equalizeHist(srcGray, heqResult);
   cv::imshow("heqResult", heqResult);
     cv::waitKey(0);
   return 0;
}
