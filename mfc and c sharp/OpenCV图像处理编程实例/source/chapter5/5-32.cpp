// 功能：代码 5-32 车牌区域提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。	// 
	// 形态学闭操作
	cv::Mat morph;
	cv::morphologyEx(bw_blue_edge, morph, cv::MORPH_CLOSE,
		cv::Mat::ones(2, 25, CV_8UC1));
	cv::Mat imshow5;
	cv::resize(bw_blue_edge, imshow5, cv::Size(), 1, 1);
	cv::imshow("morphology_bw_blue_edge", imshow5);
	cv::waitKey(0);
	// 连通区域提取
	cv::imshow("morph", morph);
	std::vector<std::vector<cv::Point> > region_contours;
	cv::findContours(morph.clone(), region_contours,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	std::vector<cv::Rect> candidates;
	std::vector<cv::Mat> candidates_img;
	cv::Mat result;
	for (size_t n = 0; n != region_contours.size(); ++n)
	{
		// 去除高度宽度不符合条件区域
		cv::Rect rect = cv::boundingRect(region_contours[n]);
		int sub = cv::countNonZero(morph(rect));
		double ratio = double(sub) / rect.area();
		double wh_ratio = double(rect.width) / rect.height;
		if (ratio > 0.5 && wh_ratio > 2 && wh_ratio < 5 &&
			rect.height > 12 && rect.width > 60)
		{
			cv::Mat small = bw_blue_edge(rect);
			result = srcImage(rect);
			cv::imshow("rect", srcImage(rect));
			cv::waitKey(0);
		}
	}