// 功能：代码 2-19 利用 createTrackbar 进行二值化
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
//createTrackbar的回调响应函数
void onChangeTrackBar (int pos,void* data)
{
	// 强制类型转换
	cv::Mat srcImage = *(cv::Mat*)(data);   
	cv::Mat dstImage;
	// 根据滑动条的值进行二值化
	cv::threshold(srcImage, dstImage, pos, 255, 0);
	cv::imshow ("dyn_threshold",dstImage);
}
int main ()
{			
	// 源图像载入及判断
	cv::Mat srcImage = cv::imread ("..\\images\\flower4.jpg");  
	if( !srcImage.data ) 
       return 1;
   // 转换为灰度图像
    cv::Mat srcGray;
    cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY); 
	cv::namedWindow("dyn_threshold");      
	cv::imshow ("dyn_threshold",srcGray); 
	//创建滑动条createTrackbar，调用回调函数
	createTrackbar ("pos","dyn_threshold",
		0, 255, onChangeTrackBar ,&srcGray);
	cv::waitKey(0);
	return 0;
}
