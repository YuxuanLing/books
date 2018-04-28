// 功能：代码 9-14 人眼模板匹配自动跟踪
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
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
