// 功能：代码 7-7 奇异区域检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include "opencv2/opencv.hpp"  
#include <iostream>
using namespace cv;
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\flow.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	// 向量关键点
	std::vector<KeyPoint> keypoints;
	//  blob类定义
	SimpleBlobDetector::Params params;
	// 参数定义
	params.filterByArea = true;
	params.minArea = 10;
	params.maxArea = 100;
	Ptr<SimpleBlobDetector>	blobDetector = SimpleBlobDetector::create(params);
	// 奇异区域检测
	blobDetector->detect(srcImage, keypoints);
	// 绘制关键点
	drawKeypoints(srcImage, keypoints,
		srcImage, Scalar(255, 0, 0));
	cv::imshow("result", srcImage);
	cv::waitKey();
	return 0;
}
