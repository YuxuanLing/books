// 功能：代码 2-12 图像翻转
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\pool.jpg");
	if (!srcImage.data)
		return -1;
	// 逆时针旋转90度
	cv::Mat resultImage1;
	transpose(srcImage, resultImage1);
	// 水平翻转
	cv::Mat resultImage2;
	flip(resultImage1, resultImage2, 1);
	// 垂直翻转
	cv::Mat resultImage3;
	flip(resultImage1, resultImage3, 0);
	// 垂直和水平翻转
	cv::Mat resultImage4;
	flip(srcImage, resultImage4, -1);

	cv::imshow("srcImage", srcImage);
	cv::imshow("resultImage1", resultImage1);
	cv::imshow("resultImage2", resultImage2);
	cv::imshow("resultImage3", resultImage3);
	cv::imshow("resultImage4", resultImage4);
	
	cv::waitKey(0);
	return 0;
}