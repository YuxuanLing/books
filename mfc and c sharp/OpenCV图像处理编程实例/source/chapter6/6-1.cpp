// 功能：代码 6-1 腐蚀膨胀操作
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
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::Mat segDst, dilDst, eroDst;
	// 分通道二值化
	cv::inRange(srcGray, cv::Scalar(0, 0, 100),
		cv::Scalar(40, 30, 255), segDst);
	// 定义结构元素
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_ELLIPSE, cv::Size(5, 5));
	// 腐蚀膨胀操作
	cv::dilate(segDst, dilDst, element);
	cv::erode(segDst, eroDst, element);
	cv::imshow(" srcGray ", srcGray);
	cv::imshow(" segDst ", segDst);
	cv::imshow(" dilDst ", dilDst);
	cv::imshow(" eroDst ", eroDst);
	cv::waitKey();
	return 0;
}