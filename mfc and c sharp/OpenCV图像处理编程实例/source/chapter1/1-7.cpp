// 功能：代码1-7  测试Sublime示例
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main( )
{
	// 读取图像
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	// 图像读取是否成功
	if( !srcImage.data ) 
	  return 1; 
	// 对图像的缩放与旋转,旋转中心  
	cv::Point2f center = 
	    cv::Point2f(srcImage.cols / 2, srcImage.rows / 2); 
	// 旋转角度 
	double angle = 60; 
	// 缩放尺度 
	double scale = 0.5;   
    // 计算旋转的仿射变换矩阵
	cv::Mat rotateImage;   
	rotateImage = cv::getRotationMatrix2D(center, 
         angle, scale);  
    // 仿射变换 
	cv::Mat rotateImg;  
	cv::warpAffine(srcImage, rotateImg, rotateImage,
         srcImage.size()); 
    // 图像显示 
	cv::imshow("srcImage", srcImage);
	cv::imshow("rotateImg",rotateImg);
	cv::waitKey(0);
	return 0;
} 
