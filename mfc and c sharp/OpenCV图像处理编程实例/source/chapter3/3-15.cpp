// 功能：代码 3-15 直方图对比实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
// ***Opencv tutorials***//
int main( int argc, char** argv )
{
   cv::Mat src_base, hsv_base;
   cv::Mat src_test1, hsv_test1;
   cv::Mat src_test2, hsv_test2;
   cv::Mat hsv_half_down;
   // 加载不同环境下三幅图像
   src_base  = cv::imread( "..\\images\\hand1.jpg");
   src_test1 = cv::imread( "..\\images\\hand2.jpg");
   src_test2 = cv::imread( "..\\images\\hand3.jpg");
   cv::imshow("HistComSource0", src_base );
   cv::imshow("HistComSource1", src_test1);
   cv::imshow("HistComSource2", src_test2);
   cv::waitKey(0);
   if( !src_base.data || !src_test1.data || !src_test2.data) 
    return 1;
   // 分别转换为HSV通道下的图像
   cvtColor( src_base, hsv_base, CV_BGR2HSV );
   cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
   cvtColor( src_test2, hsv_test2, CV_BGR2HSV );
   hsv_half_down = hsv_base( cv::Range( hsv_base.rows/2, 
             hsv_base.rows - 1 ), cv::Range( 0, 
             hsv_base.cols - 1 ) );
   /// hue通道设置为30bins, saturatoin通道设置32bins
   int h_bins = 50; int s_bins = 60;
   int histSize[] = { h_bins, s_bins };
   // 设置hue的取值从0到256, saturation取值从0到180
   float h_ranges[] = { 0, 256 };
   float s_ranges[] = { 0, 180 };
   const float* ranges[] = { h_ranges, s_ranges };
   int channels[] = { 0, 1 };
   // 建立直方图
   cv::MatND hist_base;
   cv::MatND hist_half_down;
   cv::MatND hist_test1;
   cv::MatND hist_test2;
   // 计算相应通道的下直方图
   cv::calcHist( &hsv_base, 1, channels, cv::Mat(),
        hist_base, 2, histSize, ranges, true, false );
   cv::normalize( hist_base, hist_base, 0, 1, 
            cv::NORM_MINMAX, -1, cv::Mat() );
   cv::calcHist( &hsv_half_down, 1, channels, cv::Mat(),
            hist_half_down, 2, histSize, ranges, true, false );
   cv::normalize( hist_half_down, hist_half_down, 0, 1, 
            cv::NORM_MINMAX, -1, cv::Mat() );
   cv::calcHist( &hsv_test1, 1, channels, cv::Mat(),
            hist_test1, 2, histSize, ranges, true, false );
   cv::normalize( hist_test1, hist_test1, 0, 1, 
            cv::NORM_MINMAX, -1, cv::Mat() );
   cv::calcHist( &hsv_test2, 1, channels, cv::Mat(),
            hist_test2, 2, histSize, ranges, true, false );
   cv::normalize( hist_test2, hist_test2, 0, 1,
            cv::NORM_MINMAX, -1, cv::Mat() );
   // 应用不同直方图对比方法
   for( int i = 0; i < 4; i++ )
      { 
        int compare_method = i;
        double base_base = compareHist( hist_base, 
                    hist_base, compare_method );
        double base_half = compareHist( hist_base, 
                    hist_half_down, compare_method );
        double base_test1 = compareHist( hist_base,
                    hist_test1, compare_method );
        double base_test2 = compareHist( hist_base,
                    hist_test2, compare_method );
        printf( " Method [%d] Perfect, Base-Half,Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n",
                 i, base_base, base_half , base_test1,          base_test2 );
      }
    return 0;
}
