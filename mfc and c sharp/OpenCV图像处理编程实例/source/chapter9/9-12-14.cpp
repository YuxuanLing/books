// 功能：代码 9 12-14人脸、人眼检测与跟踪
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 人脸、人眼检测与跟踪
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;
 //  人眼检测
int detectEye(cv::Mat& im, cv::Mat& tpl, cv::Rect& rect)
{
	std::vector<cv::Rect> faces, eyes;
	// 多尺度人脸检测
	face_cascade.detectMultiScale(im, faces, 
		1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
	// 遍历人脸检测结果查找人眼目标
	for (int i = 0; i < faces.size(); i++)
	{
		cv::Mat face = im(faces[i]);
		// 多尺度人眼检测
		eye_cascade.detectMultiScale(face, eyes, 
			1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(20,20));
		// 人眼检测区域输出
		if (eyes.size())
		{
			rect = eyes[0] + cv::Point(faces[i].x, faces[i].y);
			tpl  = im(rect);
		}
	}
	return eyes.size();
}
// 人眼跟踪
void trackEye(cv::Mat& im, cv::Mat& tpl, cv::Rect& rect)
{
	// 人眼位置
	cv::Size pSize(rect.width * 2, rect.height * 2);
	// 矩形区域
	cv::Rect tRect(rect + pSize - 
		cv::Point(pSize.width/2, pSize.height/2));
	tRect &= cv::Rect(0, 0, im.cols, im.rows);
    // 匹配模板生成
	cv::Mat tempMat(tRect.width - tpl.rows + 1, 
		tRect.height - tpl.cols + 1, CV_32FC1);
	// 模板匹配
	cv::matchTemplate(im(tRect), tpl, tempMat,
	    CV_TM_SQDIFF_NORMED);
	// 计算最小最大值
	double minval, maxval;
	cv::Point minloc, maxloc;
	cv::minMaxLoc(tempMat, &minval, &maxval, 
		&minloc, &maxloc);
    // 区域检测判断
	if (minval <= 0.2)
	{
		rect.x = tRect.x + minloc.x;
		rect.y = tRect.y + minloc.y;
	}
	else
		rect.x = rect.y = rect.width = rect.height = 0;
}
int main()
{

 // 初始化摄像头读取视频流
	cv::VideoCapture cap(0);
	// 宽高设置为320*256
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 420);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 400);
	// 读取级联分类器
	// 文件存放在opencv\sources\data\haarcascades	
	bool flagGlasses = false;
	if(flagGlasses)
	{
		face_cascade.load("haarcascade_frontalface_alt2.xml");
		eye_cascade.load("haarcascade_eye.xml");
	}else
	{
		face_cascade.load("haarcascade_frontalface_alt2.xml");
 	eye_cascade.load("haarcascade_eye_tree_eyeglasses.xml");
	}
	// 判断初始化设置是否正常
	if (face_cascade.empty() || eye_cascade.empty() 
     || !cap.isOpened())
		return 1;
	// 视频流操作
	cv::Mat frame, eyeMat;
	cv::Rect eyeRect;
	while (cv::waitKey(10) != 'q')
	{
		cap >> frame;
		if (frame.empty())
			break;
		// 水平翻转
		cv::flip(frame, frame, 1);
		// 灰度转换
		cv::Mat gray;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);
		// 人眼检测尺寸判断 若不符合则需要重新检测
		if (eyeRect.width <= 2 || eyeRect.height <= 2)
		{
			// 人眼检测
			detectEye(gray, eyeMat, eyeRect);
		}
		else // 符合则进行人眼跟踪
		{
			// 人眼跟踪
			trackEye(gray, eyeMat, eyeRect);
			// 人眼结果绘制
			cv::rectangle(frame, eyeRect, CV_RGB(0,255,0));
		}
		cv::imshow("video", frame);
	}
}