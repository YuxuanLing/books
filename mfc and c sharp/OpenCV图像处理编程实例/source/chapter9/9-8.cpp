// 功能：代码 9-8 BackgroundSubtractorGMG 背景建模
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/bgsegm.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;
using namespace bgsegm;
// GMG目标建模检测
void detectBackground(Ptr<BackgroundSubtractorGMG> pBackgroundGMG,
	string videoFilename) 
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
		pBackgroundGMG->setDefaultLearningRate(0.05);
		pBackgroundGMG->setDecisionThreshold(0.9);
		pBackgroundGMG->setSmoothingRadius(9);
		pBackgroundGMG->setNumFrames(100);
		//  背景模型生成
		pBackgroundGMG->apply(frame, FGMask);
		// 输出当前帧号
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
			cv::Scalar(255,255,255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		// 左上角显示帧号
		putText(frame, frameNumberString.c_str(),
			cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
		// 输出结果
		imshow("Frame", frame);
		imshow("FGMask", FGMask);
		keyboard = waitKey(30);
	}
	// 视频流释放
	capture.release();
}
int main(int argc, char* argv[])
{
    // 创建GMG背景建模类
    Ptr<BackgroundSubtractorGMG> pBackgroundGMG = 
		createBackgroundSubtractorGMG(); 
	string inputPath = "..\\images\\car.avi";
	// 背景建模检测
    detectBackground(pBackgroundGMG, inputPath);
    return 0;
}
