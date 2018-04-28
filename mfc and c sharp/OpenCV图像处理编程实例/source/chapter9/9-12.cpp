// 功能：代码 9-12 人眼目标检测初始化
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。    // 
    // 初始化摄像头读取视频流
	cv::VideoCapture cap(0);
	// 宽高设置为320*256
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 256);
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
