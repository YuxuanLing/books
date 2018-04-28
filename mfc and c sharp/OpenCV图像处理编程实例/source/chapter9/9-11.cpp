// 功能：代码 9-11 TLD 单目标跟踪
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <vector>
using namespace cv;
// 移动鼠标 选取矩形框
void mouseClickCallback(int event, 
	int x, int y, int flags, void* userdata)
{
	// 矩形数据返回
	cv::Rect2d * pRect =
		reinterpret_cast<cv::Rect2d*>(userdata);
	// 鼠标按下操作
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "LBUTTONDOWN ("
			<< x << ", " << y << ")" << std::endl;
		// 获取x，y坐标
		pRect->x = x;
		pRect->y = y;
	}
	// 鼠标抬起操作
	else if (event == cv::EVENT_LBUTTONUP)
	{
		std::cout << "LBUTTONUP (" 
			<< x << ", " << y << ")" << std::endl;
		// 获取矩形宽高
		pRect->width =  std::abs(x - pRect->x);
		pRect->height = std::abs(y - pRect->y);
	}
}
int main(int argc, char** argv)
{
	// 读取视频流
	cv::VideoCapture cap("..\\images\\car.avi"); 
	if (!cap.isOpened())
	{
		std::cout << " on data! " << std::endl;
		return -1;
	}
	cap.set(CV_CAP_PROP_POS_MSEC, 2*1000);
	cv::Mat frame;
	// 初始化TLD追踪器
	cv::Rect2d *rect(new cv::Rect2d);
	cv::Ptr<cv::TrackerTLD> tracker = 
		cv::TrackerTLD::createTracker();
	// 读取第一帧初始化矩形框
	cap >> frame; 
	cv::resize(frame, frame, cv::Size(), 0.25,0.25);
	cv::imshow("TrackerTLD", frame);
	// 鼠标移动获取矩形区域
	cv::setMouseCallback("TrackerTLD", mouseClickCallback,
		reinterpret_cast<void*>(rect));
	cv::waitKey();
	if (rect->area() == 0.0)
		return -1;
	// 跟踪器初始
	tracker->init(frame, *rect);
	double fps = 1.0;
	while(true)
	{
		cap >> frame;
		cv::resize(frame, frame, cv::Size(), 0.25,0.25);
		if (frame.empty()) 
			break;
		// 追踪器更新
		if (tracker->update(frame, *rect))
			// 绘制追踪结果
			cv::rectangle(frame, *rect, 
				cv::Scalar(255, 0, 0 ), 2, 1);
		cv::imshow("TrackerTLD", frame);
		char c = cv::waitKey(10);
		if (27 == c)
			break;
	}
	cap.release();
	return 0;
}


