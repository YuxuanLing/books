// 功能：代码 8-14 特征点匹配目标提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>

using namespace cv::xfeatures2d;
using namespace std;
using namespace cv;

cv::Mat flannMatchExtract(cv::Mat srcImage1, cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != 0 && srcImage2.data != 0);
	// 转换为灰度
	/*cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);*/
	// 构造SURF检测器
	int hessPara = 300;
	// 初始化SURF检测描述子
	cv::Ptr<Feature2D> surf = xfeatures2d::SURF::create();

	// 关键点及特征描述矩阵声明
	vector<cv::KeyPoint> kPoint1, kPoint2;
	cv::Mat despMat1, despMat2;

	surf->detectAndCompute(srcImage1, Mat(), kPoint1, despMat1);
	surf->detectAndCompute(srcImage2, Mat(), kPoint2, despMat2);

	//SurfFeatureDetector  detector(hessPara);
	//vector<KeyPoint> kPoint1, kPoint2;
	// 特征点检测
	//detector.detect(srcImage1, kPoint1);
	//detector.detect(srcImage2, kPoint2);
	//SurfDescriptorExtractor extractor;
	// 描述子提取
	//cv::Mat despMat1, despMat2;
	//extractor.compute(srcImage1, kPoint1, despMat1);
	//extractor.compute(srcImage2, kPoint2, despMat2);
	// Flann 特征点匹配
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(despMat1, despMat2, matches);
	double max_dist = 0; double min_dist = 100;
	// 距离判断-最优匹配点 
	for (int i = 0; i < despMat1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}
	printf("Max dist : %f \n", max_dist);
	printf("Min dist : %f \n", min_dist);
	// 最佳匹配点
	vector< DMatch > matchVec;
	// 检测点
	for (int i = 0; i < despMat1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			matchVec.push_back(matches[i]);
		}
	}
	// 绘制检测点
	cv::Mat matchMat, matchMat2;
	drawMatches(srcImage1, kPoint1, srcImage2, kPoint2,
		matchVec, matchMat, Scalar::all(-1),
		Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("matchMat", matchMat);
	// 特征点一致性检测
	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(kPoint1[matchVec[i].queryIdx].pt);
		scene.push_back(kPoint2[matchVec[i].trainIdx].pt);
	}
	// 随机一致性
	Mat H = findHomography(obj, scene, CV_RANSAC);
	// 构造变换矩阵 
	Point2f objCorner[4] = { cvPoint(0,0),
		cvPoint(srcImage1.cols, 0),
		cvPoint(srcImage1.cols, srcImage1.rows),
		cvPoint(0, srcImage1.rows)
	};
	// 绘制匹配点
	cv::Point sceneCors[4];
	for (int i = 0; i < 4; i++)
	{
		double x = objCorner[i].x;
		double y = objCorner[i].y;
		// 映射矩阵构造
		double Z = 1. / (H.at<double>(2, 0)*x +
			H.at<double>(2, 1)*y + H.at<double>(2, 2));
		double X = (H.at<double>(0, 0)*x +
			H.at<double>(0, 1)*y + H.at<double>(0, 2))*Z;
		double Y = (H.at<double>(1, 0)*x +
			H.at<double>(1, 1)*y + H.at<double>(1, 2))*Z;
		sceneCors[i] = cvPoint(cvRound(X) +
			srcImage1.cols, cvRound(Y));
	}
	// 绘制匹配出目标   
	line(matchMat, sceneCors[0],
		sceneCors[1], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[1],
		sceneCors[2], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[2],
		sceneCors[3], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[3],
		sceneCors[0], Scalar(0, 255, 0), 2);
	imshow("ObjectMat", matchMat);
	return matchMat;
}
int main()
{
	cv::Mat srcImage1 =
		imread("..\\images\\sAcar.jpg");
	cv::Mat srcImage2 =
		imread("..\\images\\Acar.jpg");
	if (!srcImage1.data || !srcImage2.data)
		return -1;
	
	cv::Mat resMatchMat = flannMatchExtract(srcImage1, srcImage2);
	cv::waitKey(0);
	return 0;
}
