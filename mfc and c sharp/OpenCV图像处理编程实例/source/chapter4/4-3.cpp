// 功能：代码 4-3 resize 插值操作性能对比
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace cv;
void ResizeExample(cv::Mat srcImage)
{
    CV_Assert(srcImage.data != NULL);
    cv::imshow("srcImage", srcImage);
    cv::Mat dstImage(156,156,CV_8UC3);
    // 测试1 默认参数 双线性插值
    double tTime;
    tTime = (double)getTickCount();
    const int nTimes = 100;
    for(int i  = 0;  i < nTimes; i++)
    {
    	resize(srcImage, dstImage, dstImage.size(), 0, 0);
    }
    tTime= 1000*((double)getTickCount() - tTime)/ 
         getTickFrequency();
    tTime /= nTimes;
    std::cout << "test1: "  << tTime << std::endl;
    cv::imshow("1 default parameters:dstImage", dstImage);
    // 测试2 最近邻插值 
    tTime = (double)getTickCount();
    for(int i  = 0;  i < nTimes; i++)
    {
    	resize(srcImage, dstImage, cv::Size(156,156), 0, 0, 
            cv::INTER_NEAREST); 
    }
    tTime= 1000*((double)getTickCount() - tTime)/
          getTickFrequency();
    tTime /= nTimes;
    std::cout << "test2: "  << tTime << std::endl;
    cv::imshow("2 INTER_NEAREST:dstImage", dstImage);
    // 测试3 像素区域插值 
    tTime = (double)getTickCount();
    for(int i  = 0;  i < nTimes; i++)
    {
    	resize(srcImage, dstImage, cv::Size(156,156), 0.5, 0.5, 
               cv::INTER_AREA); 
    }
    tTime= 1000*((double)getTickCount() - tTime)/
            getTickFrequency();
    tTime /= nTimes;
    std::cout << "test3: "  << tTime << std::endl; 
    cv::imshow("3 INTER_AREA:dstImage", dstImage);
    // 测试4 三次插值 
    tTime = (double)getTickCount();
    for(int i  = 0;  i < nTimes; i++)
    {
       resize(srcImage, dstImage, cv::Size(), 0.5, 0.5,
                cv::INTER_CUBIC); 
    }
    tTime = 1000*((double)getTickCount() - tTime)/
            getTickFrequency();
    tTime /= nTimes;
    std::cout << "test4: "  << tTime << std::endl;   
    cv::imshow("4 INTER_CUBIC", dstImage);
    // 测试5 三次插值 
    tTime = (double)getTickCount();
    for(int i  = 0;  i < nTimes; i++)
    {
        resize(srcImage, dstImage, cv::Size(), 0.5, 0.5, 
                cv::INTER_LANCZOS4); 
    }
    tTime= 1000*((double)getTickCount() - tTime)/
            getTickFrequency();
    tTime /= nTimes;
    std::cout << "test5: "  << tTime << std::endl;
    cv::imshow("5 INTER_LANCZOS4", dstImage);
    cv::waitKey(0);
}
int main()
{
	cv::Mat srcImage =  cv::imread("..\\images\\flower3.jpg");
    if( !srcImage.data ) 
        return -1;
	ResizeExample(srcImage);
	return 0;
}
