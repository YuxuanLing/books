// 功能：代码 3-8 BGR 三通道直方图实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

using namespace cv;
int main()
{
  cv::Mat srcImage = cv::imread("../images/circle.jpg");
  if( !srcImage.data ) 
    return 1;
  cv::imshow("srcImage", srcImage);
  cv::Mat bgr_planes[3];
  cv::split( srcImage, bgr_planes );
  
  // 初始化直方图计算参数
  int histSize = 256; 
  float range[] = { 0, 256 }; 
  const float* histRange = { range }; 
  bool uniform = true; 
  bool accumulate = false;
  cv::Mat b_hist, g_hist, r_hist;
  // 计算各个通道的直方图
  calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, 
    &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, 
    &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[2], 1, 0, cv::Mat(),r_hist, 1, 
    &histSize, &histRange, uniform, accumulate );
  // 设置直方图绘图参数
  int hist_w = 640; int hist_h = 512;
  int bin_w = cvRound( (double) hist_w/histSize );
  cv::Mat histImage( hist_h, hist_w, 
    CV_8UC3, cv::Scalar( 0,0,0) );
  // 分别归一化直方图到[ 0, histImage.rows ]
  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, 
    -1, Mat() );
  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, 
    -1, Mat() );
  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, 
    -1, Mat() );
  // 分别对每个通道进行绘图
  for( int i = 1; i < histSize; i++ )
  {
    line( histImage, Point( bin_w*(i-1), 
      hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
      Point( bin_w*(i), hist_h - 
      cvRound(b_hist.at<float>(i)) ),
      Scalar( 255, 0, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - 
      cvRound(g_hist.at<float>(i-1)) ) ,
      Point( bin_w*(i), hist_h - 
      cvRound(g_hist.at<float>(i)) ),
      Scalar( 0, 255, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - 
      cvRound(r_hist.at<float>(i-1)) ) ,
      Point( bin_w*(i), hist_h - 
      cvRound(r_hist.at<float>(i)) ),
      Scalar( 0, 0, 255), 2, 8, 0  );
  }
  imshow("calcHist", histImage );
  cv::waitKey(0);
  return 0;
}