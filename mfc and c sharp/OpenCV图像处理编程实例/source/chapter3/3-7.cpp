// 功能：代码 3-7 2 维 H-S 直方图的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream> 
using namespace std;
using namespace cv;
int main()
{
    cv::Mat srcImage, hsvMat;
    srcImage = cv::imread("..\\images\\flower3.jpg");
    if(srcImage.empty()) 
        return -1;
    cv::cvtColor(srcImage, hsvMat, CV_BGR2HSV);
    // 初始化灰度阶参数
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // 灰度变化范围设置
    float hranges[] = { 0, 180 };
    // 饱和度变化范围
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    cv::MatND hist;
    // 选取计算直方图通道
    int channels[] = {0, 1};
    // 计算当前通道直方图
    cv::calcHist( &hsvMat, 1, channels, cv::Mat(), 
        hist, 2, histSize, ranges,
        true, false );
    double maxVal=0;
    // 找到直方图的最大值
    cv::minMaxLoc(hist, 0, &maxVal, 0, 0);
    int scale = 10;
    cv::Mat histImg = cv::Mat::zeros(sbins*scale, 
        hbins*10,CV_8UC3);
    // 遍历hs通道
    for( int h = 0; h < hbins; h++ )
    {
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            // 根据最大值计算变换范围
            int intensity = cvRound(binVal*255/maxVal);
            // 绘图显示
            cv::rectangle( histImg, 
                cv::Point(h*scale, s*scale),
                cv::Point( (h+1)*scale - 1, 
                (s+1)*scale - 1),
                cv::Scalar::all(intensity),
                CV_FILLED );
        }
    }
    cv::imshow( "Source", srcImage);
    cv::imshow( "H-S Histogram", histImg);
    cv::waitKey();
}
