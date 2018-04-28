// 功能：代码 8-3 SIFT 特征检测及匹配
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 注解：需重新编译OpenCV3.1 contrib，见本书附录2
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>

using namespace cv::xfeatures2d;
using namespace std;
using namespace cv;
// 计算图像的SIFT特征及匹配
float cacSIFTFeatureAndCompare(cv::Mat srcImage1,
	cv::Mat srcImage2, float paraHessian)
{
	CV_Assert(srcImage1.data != NULL && srcImage2.data != NULL);
	// 转换为灰度
	cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);
	// 初始化SIFT检测描述子
	cv::Ptr<Feature2D> sift = xfeatures2d::SIFT::create();
	
	// 关键点及特征描述矩阵声明
	vector<cv::KeyPoint> keyPoints1, keyPoints2;
	cv::Mat descriptorMat1, descriptorMat2;
		
	sift->detectAndCompute(grayMat1, Mat(), keyPoints1, descriptorMat1);
	sift->detectAndCompute(grayMat2, Mat(), keyPoints2, descriptorMat2);
	float result = 0;
	// 特征点匹配
	if (keyPoints1.size() > 0 && keyPoints2.size() > 0)
	{
		// 计算特征匹配点
		cv::FlannBasedMatcher matcher;
		vector< cv::DMatch > matches;
		std::vector<cv::DMatch> viewMatches;
		matcher.match(descriptorMat1, descriptorMat2, matches);
		// 最优匹配判断
		double minDist = 100;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance < minDist)
				minDist = matches[i].distance;
		}
		// 计算距离特征符合要求的特征点
		int num = 0;
		std::cout << "minDist: " << minDist << std::endl;
		for (int i = 0; i < matches.size(); i++)
		{
			// 特征点匹配距离判断
			if (matches[i].distance <= 2 * minDist)
			{
				result += matches[i].distance * matches[i].distance;
				viewMatches.push_back(matches[i]);
				num++;
			}
		}
		// 匹配度计算
		result /= num;
		// 绘制特征点匹配结果
		cv::Mat matchMat;
		cv::drawMatches(srcImage1, keyPoints1,
			srcImage2, keyPoints2, matches, matchMat);
		cv::imshow("matchMat", matchMat);
		cv::waitKey(0);
	}
	return result;
}
int main()
{
	// 读取源图像及待匹配图像
	cv::Mat srcImage1 =
		cv::imread("..\\images\\hand1.jpg", 1);
	if (srcImage1.empty())
		return -1;
	cv::Mat srcImage2 =
		cv::imread("..\\images\\hand3.jpg", 1);
	if (srcImage2.empty())
		return -1;
	float matchRate = cacSIFTFeatureAndCompare(srcImage1, srcImage2, 1000);
	std::cout << "matchRate: " << matchRate << std::endl;
	return 0;
}