// 功能：代码 8-16 字符特征提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 提取字符的特征向量
cv::Mat char_feature(cv::Mat srcImage)
{
	cv::Mat gray;
	cv::cvtColor(srcImage, gray, CV_BGR2GRAY);
	// 特征字符尺寸归一化
	cv::resize(gray, gray, cv::Size(16, 32));
	// 直方图均衡
	cv::equalizeHist(gray, gray);
	gray.convertTo(gray, CV_32FC1);
	gray /= cv::norm(gray, cv::NORM_L2);
	// Sobel边缘检测
	cv::Mat sobel_v_kernel = (cv::Mat_<float>(3,3) <<
	    -0.125, 0, 0.125,
		-0.25,  0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat sobel_h_kernel = (cv::Mat_<float>(3,3) << 
		-0.125, -0.25, -0.125,
		0, 0, 0,
		0.125, 0.25, 0.125);
	cv::Mat h_edges, v_edges;
	// 卷积操作
	cv::filter2D(gray, h_edges, gray.type(), sobel_h_kernel,
		cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
	cv::filter2D(gray, v_edges, gray.type(), sobel_v_kernel,
		cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
	// 计算梯度模值及方向矩阵
	cv::Mat magnitude = cv::Mat(h_edges.size(), CV_32FC1);
	cv::Mat angle = cv::Mat(h_edges.size(), CV_32FC1);
	cv::cartToPolar(v_edges, h_edges, magnitude, angle);
	// 将八个方向范围梯度的模长分别放入八个矩阵 
	// 八个矩阵的首指针分别保存在 eight_ptr[8] 之中
	cv::Mat eight_direction[8];
	float* eight_ptr[8];
	float thre[9] = {0, CV_PI / 4, CV_PI / 2, CV_PI * 3 / 4, CV_PI,
		CV_PI * 5 / 4, CV_PI * 6 / 4, CV_PI * 7 / 4, CV_PI * 2};
	for (int i = 0; i != 8; ++i)
	{
		eight_direction[i] = cv::Mat::zeros(h_edges.size(),
           CV_32FC1);
		eight_ptr[i] = (float*)(eight_direction[i].data);
	}
	// 计算方向及梯度
	float* ang_ptr = (float*)angle.data;
	float* mag_ptr = (float*)magnitude.data;
	for (size_t i = 0; i != h_edges.total();
	    ++i, ++ang_ptr, ++mag_ptr)
	{
		for (int i = 0; i != 8; ++i)
		{
			if ((*ang_ptr) >= thre[i] && (*ang_ptr) < thre[i + 1])
			{
				*eight_ptr[i] = *mag_ptr;
			}
			++eight_ptr[i];
		}
	}
	// 统计八个模长矩阵的 4 * 2 个子块每个的模长之和，
	// 共计 8 * 8 = 64 维特征向量
	cv::Mat feature = cv::Mat::zeros(1, 112, CV_32FC1);
	float* fea_ptr = (float*)feature.data;
	for (int i = 0; i != 8; ++i)
	{
		for (int j = 0; j != 2; ++j)
		{
			for (int k = 0; k != 4; ++k)
			{
				cv::Rect roi;
				roi.x = j * 8;
				roi.y = k * 8;
				roi.width = roi.height = 8;
				*(fea_ptr++) = 
               cv::sum(eight_direction[i](roi)).val[0];
			}
		}
	}
	//字符的水平投影 32 维及垂直投影 16 维向量
   // 共计112 维特征
	cv::Mat proj_row, proj_col;
	cv::reduce(gray, proj_row, 0, CV_REDUCE_SUM);
	cv::reduce(gray, proj_col, 1, CV_REDUCE_SUM);
	float* tp = (float*)feature.data;
	float* dd = (float*)proj_row.data;
	for (int i = 64; i != 80; ++i)
	{
		tp[i] = dd[i - 64];
	}
	feature.colRange(80, 112) = proj_col.t();
	return feature;
}
