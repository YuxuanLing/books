// 功能：代码 9-10 运动目标检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;
Ptr<BackgroundSubtractorMOG2> pBackgroundKnn;
// MOG2目标建模检测
std::vector<cv::Rect> get_foreground_objects(cv::Mat scene,
	double scale, bool isFlag) 
{	
	// 标志位控制当前检测图像是否开启背景建模
	if (isFlag == false)
	{
		std::vector<cv::Rect> one_rect;
		cv::Rect whole;
		whole.x = whole.y = 0;
		whole.height = scene.rows;
		whole.width = scene.cols;
		one_rect.push_back(whole);
		return one_rect;
	}
	cv::Mat img;
	// 图像尺寸缩放 
	cv::resize(scene, img, cv::Size(0, 0), scale, scale);
	cv::Mat fgmask, fgimg, bgimg;
	// 更新背景模型
	pBackgroundKnn->apply(img, fgmask);
	// 中值滤波
	cv::medianBlur(fgmask,fgmask, 5);
	// cv::imshow("fgmask",fgmask);
    // 形态学闭操作
	cv::morphologyEx(fgmask, fgmask, cv::MORPH_CLOSE,
		cv::Mat::ones(15, 3, CV_8UC1));
	// 找到连通域
	std::vector<std::vector<cv::Point> > region_contours;
	cv::findContours(fgmask, region_contours, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	std::vector<cv::Rect> objects;
	
	// 输出检测连通域最小矩形
	for (size_t i = 0; i != region_contours.size(); ++i)
	{
		cv::Rect rect = cv::boundingRect(region_contours[i]);
		//对检测得到的外界矩形区域进行缩放
		rect.y += rect.height * 1 / 4;
		rect.height *= 3 / 4.0;
		rect.x /= scale;
		rect.width /= scale;
		rect.y /= scale;
		rect.height /= scale;
		if (rect.area() > scene.total() /400)
		{
			objects.push_back(rect);
		}
	}
	return objects;
}
int main(int argc, char* argv[])
{
	// 创建MOG2背景建模类
	pBackgroundKnn = createBackgroundSubtractorMOG2(); 
	// 背景建模检测
	// 视频获取
	VideoCapture capture("..\\images\\car.avi");
	if(!capture.isOpened())
		exit(EXIT_FAILURE);
	// 按下q键
	cv::Mat frame;
	std::vector<cv::Rect> regions;
	while (char(waitKey(1)) != 'q')
	{
		// 读取当前帧
		if(!capture.read(frame)) 
			exit(EXIT_FAILURE);
		// 图像尺寸缩小
		regions = get_foreground_objects(frame, 0.25, true);
		for (int i = 0; i < regions.size(); ++i)
		{
			cv::Mat region_img;
			region_img = frame(regions[i]);
			cv::imshow("region_img", region_img);
		}
	}
	return 0;
}