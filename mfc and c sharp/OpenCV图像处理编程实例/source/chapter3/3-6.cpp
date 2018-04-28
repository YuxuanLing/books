// 功能：代码 3-6 灰度直方图的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2\opencv.hpp>  
int main()
{
    // 图像源获取及判断 
    cv::Mat Image, ImageGray;
    Image = cv::imread("..\\images\\flower3.jpg"); 
    if(Image.empty()) 
      return -1;
    cv::imshow("Image",Image);
    // 转换为灰度图像
    cv::cvtColor(Image,ImageGray,CV_BGR2GRAY);
    // 定义直方图参数
    const int channels[1]={0};
    const int histSize[1]={256};
    float pranges[2]={0,255};
    const float* ranges[1]={pranges};
    cv::MatND hist;
    // 计算直方图
    cv::calcHist(&ImageGray,1,channels,cv::Mat(),hist,1,
    histSize,ranges);
    // 初始化画布参数
    int hist_w = 500; 
    int hist_h = 500;
    int nHistSize = 255;
    // 区间
    int bin_w = cvRound( (double) hist_w / nHistSize );
    cv::Mat histImage( hist_w, hist_h,
             CV_8UC3,   cv::Scalar( 0,0,0) );
	  // 将直方图归一化到范围 [ 0, histImage.rows ]
	  normalize(hist, hist, 0, histImage.rows, 
               cv::NORM_MINMAX,  -1, cv::Mat() );
	  // 在直方图画布上画出直方图
    for( int i = 1; i < nHistSize; i++ )
    {
      line( histImage, cv::Point(bin_w*(i-1),
             hist_h-cvRound(hist.at<float>(i-1)) ) ,
             cv::Point( bin_w*(i), 
             hist_h - cvRound(hist.at<float>(i)) ),
             cv::Scalar( 0, 0, 255), 2, 8, 0  );
    }
    // 显示直方图
    cv::imshow("histImage", histImage);
    cv::waitKey();
    return 0;
}
