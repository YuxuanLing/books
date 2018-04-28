// 功能：代码 3-21 线性变换
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
// 图像线性变换操作
cv::Mat linearTransform(cv::Mat srcImage, float a, int b)
{
    if(srcImage.empty()){  
        std::cout<< "No data!" <<std::endl;  
    } 
    const int nRows = srcImage.rows;
    const int nCols = srcImage.cols;
    cv::Mat resultImage = 
        cv::Mat::zeros(srcImage.size(), srcImage.type());
    // 图像元素遍历
    for( int i = 0; i < nRows; i++ )
    {
        for( int j = 0; j < nCols; j++ )
        {
            for( int c = 0; c < 3; c++ )
            {
                // 矩阵at操作，检查下标防止越界
                resultImage.at<Vec3b>(i,j)[c] = 
                  saturate_cast<uchar>(a * 
                  (srcImage.at<Vec3b>(i,j)[c]) + b);
            }
        }
    }
    return resultImage;
}
int main()
{
    // 图像获取及验证
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
    if(!srcImage.data) 
       return -1;
    cv::imshow("srcImage", srcImage);
    //  cv::waitKey(0);
    // 线性变换
    float a = 1.2;
    int b = 50;
    cv::Mat new_image  = linearTransform(srcImage, a, b);  
    cv::imshow("dst", new_image);
    cv::waitKey(0);
    return 0;
}
