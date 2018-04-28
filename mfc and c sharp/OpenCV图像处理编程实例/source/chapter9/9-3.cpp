// 功能：代码 9-3 图像拼接操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>
#include <vector>  
using namespace std;
using namespace cv;
void stitch(std::vector<cv::Mat> imgs, cv::Mat& resultMat)
{
	bool Flag = true;
	// 定义Stitcher类
	Stitcher stitcher = Stitcher::createDefault(Flag);
	Stitcher::Status status = stitcher.stitch(imgs, resultMat);
	if (status != Stitcher::OK) {
		std::cout << "error" << std::endl;
	}
}
void stitch2(Mat& srcImage1, Mat& srcImage2, Mat& panorama)
{
	// SURF特征点描述
	Mat srcImage2Warped;
	// 初始化SURF检测描述子
	cv::Ptr<Feature2D> surf = xfeatures2d::SURF::create();

	// 关键点及特征描述矩阵声明
	vector<cv::KeyPoint> kPointMat, kPointMat2;;
	cv::Mat desMat1, desMat2;

	surf->detectAndCompute(srcImage1, Mat(), kPointMat, desMat1);
	surf->detectAndCompute(srcImage2, Mat(), kPointMat2, desMat2);

	// FLANN 关键点匹配
	// FLANN 初始化 RANSAC一致性 最近邻特征
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(desMat1, desMat2, matches);
	double max_dist = 0, min_dist = 100;
	// 特征点最大与最小距离查找
	for (int i = 0; i < desMat1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	// 使用good 特征构建距离限定 
	std::vector< DMatch > good_matches;
	for (int i = 0; i < desMat1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	// 图像的关键点匹配
	std::vector<Point2f> srcImage1_matchedKPs;
	std::vector<Point2f> srcImage2_matchedKPs;
	for (size_t i = 0; i < good_matches.size(); i++)
	{
		srcImage1_matchedKPs.push_back(
			kPointMat[good_matches[i].queryIdx].pt);		srcImage2_matchedKPs.push_back(
				kPointMat2[good_matches[i].trainIdx].pt);
	}
	// 计算图像1与图像2的映射
	Mat H = findHomography(Mat(srcImage2_matchedKPs),
		Mat(srcImage1_matchedKPs), CV_RANSAC);
	// 仿射变换
	warpPerspective(srcImage2, srcImage2Warped, H,
		Size(srcImage2.cols * 2, srcImage2.rows), INTER_CUBIC);
	panorama = srcImage2Warped.clone();
	// 结果输出
	Mat roi(panorama, Rect(0, 0,
		srcImage1.cols, srcImage1.rows));
	srcImage1.copyTo(roi);
}
int main(int argc, char* argv[])
{
	cv::Mat image1 = imread("..\\images\\img07.JPG");
	cv::Mat image2 = imread("..\\images\\img08.JPG");
	cv::Mat image3 = imread("..\\images\\img09.JPG");
	if (!image1.data || !image2.data || !image3.data)
		return -1;
	vector<Mat> imgs;
	imgs.push_back(image1);
	imgs.push_back(image2);
	imgs.push_back(image3);
	cv::Mat resultMat1, resultMat2;
	stitch(imgs, resultMat1);
	cv::imshow("resultMat1", resultMat1);
	stitch2(image1, image2, resultMat2);
	cv::imshow("resultMat2", resultMat2);
	cv::waitKey(0);
	return 0;
}
