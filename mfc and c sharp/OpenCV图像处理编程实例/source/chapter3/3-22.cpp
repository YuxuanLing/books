// 功能：代码 3-22 对数变换的三种实现方法
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
// 对数变换方法1
cv::Mat logTransform1(cv::Mat srcImage, int c)
{
    // 输入图像判断
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;  
    cv::Mat resultImage = 
      cv::Mat::zeros(srcImage.size(), srcImage.type());
    // 计算 1 + r
    cv::add(srcImage, cv::Scalar(1.0), srcImage);
    // 转换为32位浮点数
    srcImage.convertTo(srcImage, CV_32F); 
    // 计算 log(1 + r)
    log(srcImage, resultImage);
    resultImage = c * resultImage;
    // 归一化处理
    cv::normalize(resultImage,resultImage,
        0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage,resultImage);
    return resultImage;
}
// 对数变换方法2
cv::Mat logTransform2(Mat srcImage,float c)  
{  
    // 输入图像判断
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;
    cv::Mat resultImage = 
      cv::Mat::zeros(srcImage.size(), srcImage.type());  
    double gray = 0;
    // 图像遍历分别计算每个像素点的对数变换  
    for(int i = 0;i < srcImage.rows;i++){  
        for(int j = 0; j < srcImage.cols; j++){  
            gray = (double)srcImage.at<uchar>(i,j); 
            gray = c*log((double)(1 + gray));  
            resultImage.at<uchar>(i,j)=saturate_cast<uchar>(gray); 
        }  
    }
    // 归一化处理
    cv::normalize(resultImage,resultImage,
        0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage,resultImage);
    return resultImage; 
}
// 对数变换方法3
cv::Mat logTransform3(Mat srcImage, float c)  
{  
    // 输入图像判断
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;
    cv::Mat resultImage = 
      cv::Mat::zeros(srcImage.size(), srcImage.type());  
    srcImage.convertTo(resultImage,CV_32F);
    resultImage = resultImage + 1;
    cv::log(resultImage,resultImage);
    resultImage = c * resultImage;
    cv::normalize(resultImage,resultImage,0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage,resultImage);
    return resultImage; 
}
int main()
{
    // 读取灰度图像及验证
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg",0); 
    if(!srcImage.data) 
        return -1;
    // 验证三种不同方式的对数变换速度
    cv::imshow("srcImage", srcImage); 
    float c = 1.1;
    cv::Mat resultImage;
    double tTime;
    tTime = (double)getTickCount();
    const int nTimes = 100;
    for(int i  = 0;  i < nTimes; i++)
    {
        resultImage = logTransform3(srcImage, c); 
    }
    tTime = 1000*((double)getTickCount() - tTime)/
    getTickFrequency();
    tTime /= nTimes;
    std::cout << tTime << std::endl;   
    cv::imshow("resultImage", resultImage);
    cv::waitKey(0);
    return 0;
}
