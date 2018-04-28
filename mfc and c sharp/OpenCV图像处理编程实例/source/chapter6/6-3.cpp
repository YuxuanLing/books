// 功能：代码 6-3 形态学梯度操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\test.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// 定义结构元素
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat gradMat;
	// 形态学梯度
	cv::morphologyEx(srcGray, gradMat, 
		cv::MORPH_GRADIENT, element);
	cv::imshow(" srcGray ", srcGray);
	cv::imshow(" gradMat ", gradMat);
	cv::waitKey();
	return 0;
}
