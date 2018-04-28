// 功能：代码 3-20 Gamma 校正
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace std;
using namespace cv;
// Gamma变换函数实现
cv::Mat gammaTransform(cv::Mat& srcImage, float kFactor)
{
	// 建立查表文件LUT
	unsigned char LUT[256];
	for( int i = 0; i < 256; i++ )
	{
		// Gamma变换表达式
		LUT[i] = saturate_cast<uchar>(pow( ( float)( 
               i / 255.0 ), kFactor ) * 255.0f );
	}
	cv::Mat resultImage = srcImage.clone();
	// 输入通道为单通道时 直接进行变换
	if(srcImage.channels() == 1)
	{
		cv::MatIterator_<uchar> iterator = 
                 resultImage.begin<uchar>();
		cv::MatIterator_<uchar> iteratorEnd = 
                 resultImage.end<uchar>();
		for( ; iterator != iteratorEnd; iterator ++ )
			*iterator = LUT[(*iterator)];
	}else
	{
	    // 输入通道为三通道时 需对每个通道分别进行变换
        cv::MatIterator_<cv::Vec3b> iterator = 
               resultImage.begin<Vec3b>();
        cv::MatIterator_<cv::Vec3b> iteratorEnd = 
               resultImage.end<Vec3b>();
       //  通过查找表进行转换
		for( ; iterator != iteratorEnd; iterator++ )
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}
	return resultImage;
}
int main()
{
     cv::Mat srcImage =  imread("..\\images\\lakeWater.jpg");
     if( !srcImage.data ) 
	      return -1;
     // 初始化两种不同参数 对比分析效果
     float kFactor1 =  0.3;
     float kFactor2 =  3.0;
	 cv::Mat result1 = gammaTransform(srcImage, kFactor1);
	 cv::Mat result2 = gammaTransform(srcImage, kFactor2);
     cv::imshow("srcImage", srcImage);
     cv::imshow("result1", result1);
     cv::imshow("result2", result2);
     cv::waitKey(0);
	 return 0;
}
