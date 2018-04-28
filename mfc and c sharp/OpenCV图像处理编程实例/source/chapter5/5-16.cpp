// 功能：代码 5-16 霍夫变换线检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main( )
{
  cv::Mat srcImage = 
      cv::imread("..\\images\\building.jpg", 0);
  if (!srcImage.data)   
       return -1;
  cv::Mat edgeMat, houghMat;
  // Canny边缘检测 二值图像
  Canny(srcImage, edgeMat, 50, 200, 3);
  cvtColor(edgeMat, houghMat, CV_GRAY2BGR);
  #if 0
  // 标准的霍夫变换
  vector<Vec2f> lines;
  HoughLines(edgeMat, lines, 1, CV_PI/180, 100, 0, 0 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
     // 根据直线参数表达式绘制相应检测结果
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 1000*(-b));
     pt1.y = cvRound(y0 + 1000*(a));
     pt2.x = cvRound(x0 - 1000*(-b));
     pt2.y = cvRound(y0 - 1000*(a));
     line( houghMat, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
  }
  #else
  // 统计概率的霍夫变换
  vector<Vec4i> lines;
  HoughLinesP(edgeMat, lines, 1, CV_PI/180, 50, 50, 10 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    // 绘制线检测结果
    line( houghMat, Point(l[0], l[1]), 
       Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }
  #endif
  cv::imshow("srcImage", srcImage);
  cv::imshow("houghMat", houghMat);
  cv::waitKey();
  return 0;
}
