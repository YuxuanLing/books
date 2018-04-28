// 功能：代码 7-2 分水岭分割合并
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 分割合并
void segMerge(Mat & image, Mat & segments, int & numSeg)
{
	// 对一个分割部分进行像素统计
	vector<Mat> samples;
	// 统计数据更新
	int newNumSeg = numSeg;
	// 初始化分割部分
	for (int i = 0; i <= numSeg; i++)
	{
		Mat sampleImage;
		samples.push_back(sampleImage);
	}
	// 统计每一个部分
	for (int i = 0; i < segments.rows; i++)
	{
		for (int j = 0; j < segments.cols; j++)
		{
			// 检查每个像素的归属
			int index = segments.at<int>(i, j);
			if (index >= 0 && index<numSeg)
				samples[index].push_back(image(Rect(j,i,1,1)));
		}
	}
	// 创建直方图
	vector<MatND> hist_bases;
	Mat hsv_base;
	// 直方图参数设置
	int h_bins = 35;
	int s_bins = 30;
	int histSize[] = { h_bins, s_bins };
	// hue 变换范围 0 to 256, saturation 变换范围0 to 180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// 使用第0与1通道
	int channels[] = { 0, 1 };
	// 直方图生成
	MatND hist_base;
	for (int c = 1; c < numSeg; c++)
	{
		if (samples[c].dims>0){
			// 将区域部分转换成hsv
			cvtColor(samples[c], hsv_base, CV_BGR2HSV);
			// 直方图统计
			calcHist(&hsv_base, 1, channels, Mat(),
				hist_base, 2, histSize, ranges, true, false);
			// 直方图归一化
			normalize(hist_base, hist_base, 0, 1,
				NORM_MINMAX, -1, Mat());
			// 添加到统计集
			hist_bases.push_back(hist_base);
		}
		else
		{
			hist_bases.push_back(MatND());
		}
		hist_base.release();
	}
	double similarity = 0;
	vector<bool> mearged;
	for (int k = 0; k < hist_bases.size(); k++)
	{
		mearged.push_back(false);
	}
	// 统计每一个部分的直方图相似
	for (int c = 0; c<hist_bases.size(); c++)
	{
		for (int q = c + 1; q<hist_bases.size(); q++)
		{
			if (!mearged[q])
			{
				// 判断直方图的维度
				if (hist_bases[c].dims>0 && hist_bases[q].dims>0)
				{
					// 直方图对比
					similarity = compareHist(hist_bases[c],
						hist_bases[q], CV_COMP_BHATTACHARYYA);
					if (similarity > 0.8)
					{
						mearged[q] = true;
						if (q != c)
						{
							// 区域部分减少
							newNumSeg--;
							for (int i = 0; i < segments.rows; i++)
							{
								for (int j = 0; j < segments.cols; j++)
								{
								int index = segments.at<int>(i, j);
									// 合并
									if (index == q)
									{
										segments.at<int>(i, j) = c;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	numSeg = newNumSeg;
}
