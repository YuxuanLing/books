// 功能：代码 6-2 形态学开闭操作
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
	cv::Mat srcGray, segImage;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// 阈值化
	cv::threshold(srcGray, segImage,
		255 * (0.5), 255, cv::THRESH_BINARY);
	// 定义结构元素
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_ELLIPSE, cv::Size(20, 20));
	// 形态学闭操作
	cv::Mat closedMat;
	cv::morphologyEx(segImage, closedMat, 
		cv::MORPH_CLOSE, element);
	// 形态学开操作 
	cv::Mat openedMat;
	cv::morphologyEx(segImage, openedMat,
	 cv::MORPH_OPEN, element);
	cv::imshow(" srcGray ", srcGray);
	cv::imshow(" segImage ", segImage);
	cv::imshow(" closedMat ", closedMat);
	cv::imshow(" openedMat ", openedMat);
	cv::waitKey();
	return 0;
}
