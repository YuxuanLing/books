// 功能：代码 7-1-2 分水岭算法
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
// 分水岭分割显示
cv::Mat displaySegResult(cv::Mat & segments, int numOfSegments, cv::Mat & image)
{
	cv::Mat wshed(segments.size(), CV_8UC3);
	// 创建对于颜色分量
	vector<Vec3b> colorTab;
	for (int i = 0; i < numOfSegments; i++)
	{
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	//应用不同颜色对每个部分
	for (int i = 0; i < segments.rows; i++)
	{
		for (int j = 0; j < segments.cols; j++)
		{
			int index = segments.at<int>(i, j);
			if (index == -1)
				wshed.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			else if (index <= 0 || index > numOfSegments)
				wshed.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			else
				wshed.at<Vec3b>(i, j) = colorTab[index - 1];
		}
	}
	if (image.dims>0)
		wshed = wshed*0.5 + image*0.5;
	return wshed;
}
// 分割合并
void segMerge(cv::Mat & image, cv::Mat & segments, int & numSeg)
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
			{
				samples[index].push_back(image(Rect(j, i, 1, 1)));
			}
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
		if (samples[c].dims>0) {
			// 将区域部分转换成hsv
			cvtColor(samples[c], hsv_base, CV_BGR2HSV);
			// 直方图统计
			calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
			// 直方图归一化
			normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
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
				if (hist_bases[c].dims>0 && hist_bases[q].dims>0)
				{
					similarity = compareHist(hist_bases[c], hist_bases[q], CV_COMP_BHATTACHARYYA);
					if (similarity>0.8)
					{
						mearged[q] = true;
						if (q != c)
						{
							//区域部分减少
							newNumSeg--;
							for (int i = 0; i < segments.rows; i++)
							{
								for (int j = 0; j < segments.cols; j++)
								{
									int index = segments.at<int>(i, j);
									// 合并
									if (index == q) {
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
cv::Mat watershedSegment(cv::Mat & image, int & noOfSegments)
{
	cv::Mat gray;
	cv::Mat ret;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	cv::imshow("Gray Image", gray);
	// 阈值操作
	cv::threshold(gray, ret, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
	cv::imshow("Image after OTSU Thresholding", ret);
	// 形态学开操作
	cv::morphologyEx(ret, ret, MORPH_OPEN, Mat::ones(9, 9, CV_8SC1), Point(4, 4), 2);
	cv::imshow("Thresholded Image after Morphological open", ret);
	// 距离变换
	cv::Mat distTransformed(ret.rows, ret.cols, CV_32FC1);
	distanceTransform(ret, distTransformed, CV_DIST_L2, 3);
	// 归一化
	normalize(distTransformed, distTransformed, 0.0, 1, NORM_MINMAX);
	cv::imshow("Distance Transformation", distTransformed);
	// 阈值化分割图像
	threshold(distTransformed, distTransformed, 0.1, 1, CV_THRESH_BINARY);
	//归一化统计图像到0-255
	normalize(distTransformed, distTransformed, 0.0, 255.0, NORM_MINMAX);
	distTransformed.convertTo(distTransformed, CV_8UC1);
	cv::imshow("Thresholded Distance Transformation", distTransformed);
	//计算标记的分割块
	int i, j, compCount = 0;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(distTransformed, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if (contours.empty())
		return Mat();
	Mat markers(distTransformed.size(), CV_32S);
	markers = Scalar::all(0);
	int idx = 0;
	// 绘制区域块
	for (; idx >= 0; idx = hierarchy[idx][0], compCount++)
		drawContours(markers, contours, idx, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
	if (compCount == 0)
		return Mat();
	//计算算法的时间复杂度
	double t = (double)getTickCount();
	watershed(image, markers);
	t = (double)getTickCount() - t;
	printf("execution time = %gms\n", t*1000. / getTickFrequency());
	Mat wshed = displaySegResult(markers, compCount,image);
	imshow("watershed transform", wshed);
	noOfSegments = compCount;
	return markers;
}


int main()
{
	cv::Mat srcImage = imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return 1;
	cv::imshow("Original Image", srcImage);
	// 转换成hsv图像
	cv::Mat hsv;
	cv::cvtColor(srcImage, hsv, CV_BGR2HSV);
	cv::imshow("hsv", hsv);
	// 分水岭操作
	int numOfSegments = 0;
	cv::Mat segments = watershedSegment(srcImage, numOfSegments);
	// 分割排序减少过分割
	segMerge(srcImage, segments, numOfSegments);
	// 显示分割图像
	cv::Mat wshed = displaySegResult(segments, numOfSegments,srcImage);
	// 显示分割后合并图像
	cv::Mat wshedWithImage = displaySegResult(segments, numOfSegments, srcImage);
	cv::imshow("Merged segments", wshed);
	cv::imshow("Merged segments with image", wshedWithImage);
	cv::waitKey(0);
	return 0;
}

