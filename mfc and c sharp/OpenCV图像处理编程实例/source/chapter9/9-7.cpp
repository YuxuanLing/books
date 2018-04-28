// 功能：代码 9-7 BackgroundSubtractorKNN 背景建模
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
void processVideo(Ptr<BackgroundSubtractorKNN> pBackgroundKnn, string videoFilename) 
{
	cv::Mat frame,FGMask; 
	int keyboard=0;
	// 视频获取
	VideoCapture capture(videoFilename);
	if(!capture.isOpened())
		exit(EXIT_FAILURE);
	// 按下q键和esc退出
	while( (char)keyboard != 'q' && (char)keyboard != 27 )
	{
		// 读取当前帧
		if(!capture.read(frame)) 
			exit(EXIT_FAILURE);
		// 图像尺寸缩小
		cv::resize(frame, frame,cv::Size(), 0.2,0.2);
		// 背景建模参数设定
		pBackgroundKnn->setHistory(200);
		pBackgroundKnn->setDist2Threshold(600);
		pBackgroundKnn->setShadowThreshold(0.5);
		//  背景模型生成
		pBackgroundKnn->apply(frame, FGMask);
		// 输出当前帧号
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
			cv::Scalar(255,255,255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		// 左上角显示帧号
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
		// 输出结果
		imshow("Frame", frame);
		imshow("FGMask", FGMask);
		keyboard = waitKey(30);
	}
	capture.release();
}
int main(int argc, char* argv[])
{
    // 创建背景建模类
    Ptr<BackgroundSubtractorKNN> pBackgroundKnn = 
		createBackgroundSubtractorKNN(); 
	string inputPath = "..\\images\\car.avi";
    processVideo( pBackgroundKnn, inputPath);
    return 0;
}
