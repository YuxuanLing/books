// 功能：代码 9-1 特征运动点估计
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// good 特征点鉴别
cv::Mat getRansacMat(const std::vector<cv::DMatch>& matches,
const std::vector<cv::KeyPoint>& keypoints1,
const std::vector<cv::KeyPoint>& keypoints2,
std::vector<cv::DMatch>& outMatches)
{
	// 转换特征点格式

	std::vector<cv::Point2f> points1, points2;
	cv::Mat featureMat;
	for (std::vector<cv::DMatch>::const_iterator it =
	matches.begin(); it!= matches.end(); ++it)
	{
		// 获取特征点的左侧位置
		float x= keypoints1[it->queryIdx].pt.x;
		float y= keypoints1[it->queryIdx].pt.y;
		points1.push_back(cv::Point2f(x,y));
		// 获取特征点的右侧位置
		x= keypoints2[it->trainIdx].pt.x;
		y= keypoints2[it->trainIdx].pt.y;
		points2.push_back(cv::Point2f(x,y));
	}
	// 计算 good 特征矩阵
	std::vector<uchar> inliers(points1.size(),0);
	if (points1.size()>0 &&points2.size()>0)
	{
		// 计算两幅图像的对应点的特征矩阵
		cv::Mat featureMat= cv::findFundamentalMat(
		cv::Mat(points1),cv::Mat(points2), inliers,
		CV_FM_RANSAC,distance,confidence);
		// 提取存在特征点匹配
		std::vector<uchar>::const_iterator
		itIn= inliers.begin();
		std::vector<cv::DMatch>::const_iterator
		itM= matches.begin();
		// 遍历所有特征点
		for ( ;itIn!= inliers.end(); ++itIn, ++itM)
		{
			if (*itIn)
			outMatches.push_back(*itM);
		}
		if (refineF)
		{
			points1.clear();
			points2.clear();
			for (std::vector<cv::DMatch>::
			const_iterator it= outMatches.begin();
			it!= outMatches.end(); ++it)
			{
				float x= keypoints1[it->queryIdx].pt.x;
				float y= keypoints1[it->queryIdx].pt.y;
				points1.push_back(cv::Point2f(x,y));
				x= keypoints2[it->trainIdx].pt.x;
				y= keypoints2[it->trainIdx].pt.y;
				points2.push_back(cv::Point2f(x,y));
			}
			// 计算两幅图像的特征矩阵
			if (points1.size()>0 && points2.size()>0)
			{

				featureMat= cv::findFundamentalMat(
				cv::Mat(points1),cv::Mat(points2),
				CV_FM_8POINT);
			}
		}
	}
	return featureMat;
 }