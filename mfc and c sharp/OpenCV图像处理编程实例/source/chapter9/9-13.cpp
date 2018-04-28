// 功能：代码 9-13 人眼检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
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
