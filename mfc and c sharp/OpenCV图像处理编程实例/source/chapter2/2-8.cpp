// 功能：代码 2-8 remap 重映射
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
    if(!srcImage.data) 
       return -1;
    // 输出矩阵定义
    cv::Mat resultImage(srcImage.size(), srcImage.type());
    // X与Y方向矩阵
    cv::Mat xMapImage(srcImage.size(), CV_32FC1);
    cv::Mat yMapImage(srcImage.size(), CV_32FC1);
    int rows = srcImage.rows;
    int cols = srcImage.cols;
    for( int j = 0; j < rows; j++ )
    {
      for( int i = 0; i < cols; i++ )
       {
            // x与y均翻转
            xMapImage.at<float>(j,i) = cols - i ;
            yMapImage.at<float>(j,i) = rows - j ;
       }
    }
    // 重映射操作
    remap( srcImage, resultImage, xMapImage, yMapImage,
           CV_INTER_LINEAR, cv::BORDER_CONSTANT,
           cv::Scalar(0,0, 0) );
    // 输出结果
    cv::imshow("srcImage", srcImage);
    cv::imshow("resultImage", resultImage);
    cv::waitKey(0);
    return 0;
}
