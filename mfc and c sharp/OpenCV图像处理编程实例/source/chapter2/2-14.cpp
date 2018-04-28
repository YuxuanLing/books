// 功能：代码 2-14 图像仿射变换
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace cv;
int main()
{
  // 读取图像及验证读入正确
  cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
  if(!srcImage.data) 
       return -1;
  cv::imshow("srcImage", srcImage);
  int nRows = srcImage.rows;
  int nCols = srcImage.cols;
  //定义仿射变换的二维点数组
  //源图像和目标图像对应映射的三点
  cv::Point2f srcPoint[3];
  cv::Point2f resPoint[3];
  srcPoint[0] = cv::Point2f(0, 0);
  srcPoint[1] = cv::Point2f(nCols-1, 0);
  srcPoint[2] = cv::Point2f(0, nRows-1);
  resPoint[0] = cv::Point2f(nCols*0, nRows*0.33);
  resPoint[1] = cv::Point2f(nCols*0.85, nRows*0.25);
  resPoint[2] = cv::Point2f(nCols*0.15, nRows*0.7);
  // 定义仿射变换矩阵2X3
  cv::Mat warpMat(cv::Size(2,3),CV_32F);
  cv::Mat resultImage = 
   cv::Mat::zeros(nRows, nCols, srcImage.type());
  // 计算仿射变换矩阵，即仿射变换的2*3数组
  warpMat = cv::getAffineTransform(srcPoint, resPoint);  
  // 根据仿射矩阵计算图像仿射变换
  cv::warpAffine(srcImage, resultImage,
      warpMat, resultImage.size());
  cv::imshow("resultImage1",resultImage);
  // 仿射变换参数设置
  cv::Point2f centerPoint = cv::Point2f(nCols/2, nRows/2);
  double angle = -50;
  double scale = 0.7;
  // 获取仿射变换矩阵
  warpMat = getRotationMatrix2D(centerPoint, angle, scale);
  // 对原图像角度仿射变换
  cv::warpAffine(srcImage, resultImage, 
      warpMat, resultImage.size());
  cv::imshow("resultImage2",resultImage);
  cv::waitKey(0);
}
