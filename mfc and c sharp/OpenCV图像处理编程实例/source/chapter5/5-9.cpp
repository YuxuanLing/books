// 功能：代码 5-9 Prewitt 边缘检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
// prewitt算子实现
cv::Mat prewitts(cv::Mat img, bool verFlag = false)
{
	img.convertTo(img, CV_32FC1);
	cv::Mat prewitt_kernel =
		(cv::Mat_<float>(3, 3) << 0.1667, 0.1667, 0.1667,
			0, 0, 0,
			-0.1667, -0.1667, -0.1667);
	// 水平边缘
	if (verFlag) {
		prewitt_kernel = prewitt_kernel.t();
		cv::Mat z1 = cv::Mat::zeros(img.rows, 1, CV_32FC1);
		cv::Mat z2 = cv::Mat::zeros(1, img.cols, CV_32FC1);
		// 将图像的四边设为 0 
		z1.copyTo(img.col(0));
		z1.copyTo(img.col(img.cols - 1));
		z2.copyTo(img.row(0));
		z2.copyTo(img.row(img.rows - 1));
	}
	cv::Mat edges;
	cv::filter2D(img, edges, img.type(), prewitt_kernel);
	cv::Mat mag;
	cv::multiply(edges, edges, mag);
	// 水平边缘边界黑边去除
	if (verFlag)
	{
		cv::Mat black_region = img < 0.03;
		cv::Mat se = cv::Mat::ones(5, 5, CV_8UC1);
		cv::dilate(black_region, black_region, se);
		mag.setTo(0, black_region);
	}
	// 根据模长算出梯度的阈值
	double thresh = 4.0f * cv::mean(mag).val[0];
	// 仅在某点梯度大于水平方向或
	// 垂直方向邻点梯度时才设该位置输出值为 255
	// 并应用阈值thresh
	cv::Mat dstImage = cv::Mat::zeros(mag.size(), mag.type());
	float* dptr = (float*)mag.data;
	float* tptr = (float*)dstImage.data;
	int r = edges.rows, c = edges.cols;
	for (int i = 1; i != r - 1; ++i)
	{
		for (int j = 1; j != c - 1; ++j)
		{
			// 非极大值抑制
			bool b1 = (dptr[i * c + j] > dptr[i * c + j - 1]);
			bool b2 = (dptr[i * c + j] > dptr[i * c + j + 1]);
			bool b3 = (dptr[i * c + j] > dptr[(i - 1) * c + j]);
			bool b4 = (dptr[i * c + j] > dptr[(i + 1) * c + j]);
			tptr[i * c + j] = 255 * ((dptr[i * c + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	dstImage.convertTo(dstImage, CV_8UC1);
	return dstImage;
}
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::Mat dstImage = prewitts(srcImage);
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
