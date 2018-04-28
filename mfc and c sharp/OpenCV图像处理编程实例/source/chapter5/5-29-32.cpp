// 功能：代码 5-29-32 车牌区域提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <iostream>
#include <vector>
#include <stdint.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
// 提取竖直的sobel边缘
bool SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
	CV_Assert(srcImage.channels() == 1);
	srcImage.convertTo(srcImage, CV_32FC1);
	// 水平方向的 Sobel 算子
	cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
		-0.25, 0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat ConResMat;
	// 卷积运算
	cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
	// 计算梯度的幅度
	cv::Mat graMagMat;
	cv::multiply(ConResMat, ConResMat, graMagMat);
	// 根据梯度幅度及参数设置阈值
	int scaleVal = 4;
	double thresh = scaleVal * cv::mean(graMagMat).val[0];
	cv::Mat resultTempMat = cv::Mat::zeros(
		graMagMat.size(), graMagMat.type());
	float* pDataMag = (float*)graMagMat.data;
	float* pDataRes = (float*)resultTempMat.data;
	const int nRows = ConResMat.rows;
	const int nCols = ConResMat.cols;
	for (int i = 1; i != nRows - 1; ++i) {
		for (int j = 1; j != nCols - 1; ++j) {
			// 计算该点梯度与水平或垂直梯度值大小比较结果
			bool b1 = (pDataMag[i * nCols + j] > pDataMag[i *
				nCols + j - 1]);
			bool b2 = (pDataMag[i * nCols + j] > pDataMag[i *
				nCols + j + 1]);
			bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1)
				* nCols + j]);
			bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1)
				* nCols + j]);
			// 判断邻域梯度是否满足大于水平或垂直梯度
			// 并根据自适应阈值参数进行二值化
			pDataRes[i * nCols + j] = 255 * ((pDataMag[i *
				nCols + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resultTempMat.convertTo(resultTempMat, CV_8UC1);
	resultImage = resultTempMat.clone();
	return true;
}
// 疑似区域提取
cv::Mat getPlateArea(cv::Mat srcImage, cv::Mat sobelMat)
{
	// 转换成hsv 
	cv::Mat img_h, img_s, img_v, imghsv;
	std::vector<cv::Mat> hsv_vec;
	cv::cvtColor(srcImage, imghsv, CV_BGR2HSV);
	cv::imshow("hsv", imghsv);
	cv::waitKey(0);
	// 分割hsv通道
	cv::split(imghsv, hsv_vec);
	img_h = hsv_vec[0];
	img_s = hsv_vec[1];
	img_v = hsv_vec[2];
	img_h.convertTo(img_h, CV_32F);
	img_s.convertTo(img_s, CV_32F);
	img_v.convertTo(img_v, CV_32F);
	double max_s, max_h, max_v;
	cv::minMaxIdx(img_h, 0, &max_h);
	cv::minMaxIdx(img_s, 0, &max_s);
	cv::minMaxIdx(img_v, 0, &max_v);
	// 各个通道归一化
	img_h /= max_h;
	img_s /= max_s;
	img_v /= max_v;
	// hsv 限定范围元素提取
	cv::Mat bw_blue = ((img_h>0.45) &
		(img_h<0.75) &
		(img_s>0.15) &
		(img_v>0.25));
	int height = bw_blue.rows;
	int width = bw_blue.cols;
	cv::Mat bw_blue_edge = cv::Mat::zeros(bw_blue.size(), bw_blue.type());
	cv::imshow("bw_blue", bw_blue);
	cv::waitKey(0);
	// 车牌疑似区域提取
	for (int k = 1; k != height - 2; ++k)
	{
		for (int l = 1; l != width - 2; ++l)
		{
			cv::Rect rct;
			rct.x = l - 1;
			rct.y = k - 1;
			rct.height = 3;
			rct.width = 3;
			if ((sobelMat.at<uchar>(k, l) == 255) && (cv::countNonZero(bw_blue(rct)) >= 1))
				bw_blue_edge.at<uchar>(k, l) = 255;
		}
	}
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
	return result;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\car.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::imshow("srcImage", srcImage);
	// sobel 提取边缘
	cv::Mat sobelMat;
	SobelVerEdge(srcGray, sobelMat);
	cv::imshow("Sobel", sobelMat);
	// 疑似区域提取
	cv::Mat result = getPlateArea(srcImage, sobelMat);
	return 0;
}
