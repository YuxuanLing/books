// 功能：代码 3-16 直方图反向投影
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
  // 加载源图像并验证
  cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
  if( !srcImage.data ) 
    return 1;
  // 转换到 HSV 空间
  cv::Mat hsvImage;
  cvtColor( srcImage, hsvImage, CV_BGR2HSV );
  // Hue 通道分离 
  cv::Mat hueImage; 
  hueImage.create( hsvImage.size(), hsvImage.depth() );
  int ch[] = { 0, 0 };
  mixChannels( &hsvImage, 1, &hueImage, 1, ch, 1 );
  // 初始化直方图计算参数
  int bins = 25;
  cv::MatND hist;
  int histSize = MAX( bins, 2 );
  float hue_range[] = { 0, 100 };
  const float* ranges = { hue_range };
  // 计算直方图
  calcHist( &hueImage, 1, 0, cv::Mat(),
            hist, 1, &histSize, &ranges, true, false );
  // 归一化直方图
  normalize( hist, hist, 0, 255, cv::NORM_MINMAX,
           -1, cv::Mat() );
  // 计算反向投影
  MatND backproj;
  calcBackProject( &hueImage, 1, 0, hist, backproj, 
            &ranges, 1, true );
  // 定义输出图像
  int w = 320; int h = 360;
  int bin_w = cvRound( (double) w / histSize );
  cv::Mat histImg = cv::Mat::zeros( w, h, CV_8UC3 );
  for( int i = 0; i < bins; i ++ )
  {
      // 绘制直方图
      rectangle( histImg, cv::Point( i * bin_w, h ),
           cv::Point( (i+1)*bin_w,
           h - cvRound( hist.at<float>(i) * h / 255.0 ) ),
           cv::Scalar( 0, 0, 255 ), -1 ); 
  } 
  // 显示源图像与反向投影图像
  imshow( "BackProj", backproj );
  imshow( "srcImage", srcImage);
  imshow( "Histogram", histImg );
  // 直方图均衡化
  cv::equalizeHist(backproj , backproj);
  imshow( "backproj_equa", backproj );
  waitKey(0);
  return 0;
}
