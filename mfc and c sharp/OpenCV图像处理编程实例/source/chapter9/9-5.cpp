// 功能：代码 9-5 高斯混合背景建模
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
Mat frame; 
Mat fgMaskMOG2; 
Ptr<BackgroundSubtractor> pMOG2;
int keyboard; 
void processVideo(string videoFilename) 
{
	// 视频获取
	VideoCapture capture(videoFilename);
	if(!capture.isOpened())
	{
		// 输出视频文件打开错误信息
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}
	// 按下q键和esc退出
	while( (char)keyboard != 'q' && (char)keyboard != 27 )
	{
		// 读取当前帧
		if(!capture.read(frame)) 
		{
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
		// 图像尺寸缩小
		cv::resize(frame, frame,cv::Size(), 0.25,0.25);
		//  背景模型生成
		pMOG2->apply(frame, fgMaskMOG2);
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
		imshow("FG Mask MOG 2", fgMaskMOG2);
		keyboard = waitKey(30);
	}
	capture.release();
}
int main(int argc, char* argv[])
{
    // 创建背景建模类
    pMOG2 = createBackgroundSubtractorMOG2(); 
	string inputPath = "..\\images\\car.avi";
    processVideo(inputPath);
    return 0;
}
