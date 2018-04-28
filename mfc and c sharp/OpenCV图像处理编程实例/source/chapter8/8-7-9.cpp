// 功能：代码  HOG特征计算
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define NBINS 9
#define THETA 180 / NBINS
#define CELLSIZE 20
#define BLOCKSIZE 2
#define R (CELLSIZE * (BLOCKSIZE) * 0.5)
// 计算积分图
std::vector<Mat> CalculateIntegralHOG(Mat& srcMat)
{
	// sobel边缘检测
	Mat sobelMatX, sobelMatY;
	Sobel(srcMat, sobelMatX, CV_32F, 1, 0);
	Sobel(srcMat, sobelMatY, CV_32F, 0, 1);
	std::vector<Mat> bins(NBINS);
	for (int i = 0; i < NBINS; i++)
	{
		bins[i] = Mat::zeros(srcMat.size(), CV_32F);
	}
	Mat magnMat, angleMat;
	// 坐标转换
	cartToPolar(sobelMatX, sobelMatY, magnMat, angleMat, true);
	// 角度变换
	add(angleMat, Scalar(180), angleMat, angleMat<0);
	add(angleMat, Scalar(-180), angleMat, angleMat >= 180);
	angleMat /= THETA;
	for (int y = 0; y < srcMat.rows; y++)
	{
		for (int x = 0; x < srcMat.cols; x++)
		{
			// 计算bins下幅值
			int ind = angleMat.at<float>(y, x);
			bins[ind].at<float>(y, x) +=
				magnMat.at<float>(y, x);
		}
	}
	// 积分图像的生成
	std::vector<Mat> integrals(NBINS);
	for (int i = 0; i < NBINS; i++)
	{
		integral(bins[i], integrals[i]);
	}
	return integrals;
}
// 计算单个cell HOG特征
void cacHOGinCell(Mat& HOGCellMat, Rect roi,
	std::vector<Mat>& integrals)
{
	// 快速积分HOG实现
	int x0 = roi.x, y0 = roi.y;
	int x1 = x0 + roi.width, y1 = y0 + roi.height;
	for (int i = 0; i < NBINS; i++)
	{
		// 根据矩阵的上下左右坐标
		Mat integral = integrals[i];
		float a = integral.at<double>(y0, x0);
		float b = integral.at<double>(y1, x1);
		float c = integral.at<double>(y0, x1);
		float d = integral.at<double>(y1, x0);
		HOGCellMat.at<float>(0, i) = (a + b) - (c + d);
	}
}
// HOG直方图获取
cv::Mat getHog(Point pt, std::vector<Mat> &integrals)
{
	if (pt.x - R < 0 || pt.y - R < 0 ||
		pt.x + R >= integrals[0].cols ||
		pt.y + R >= integrals[0].rows)
	{
		return Mat();
	}
	// 直方图
	Mat hist(Size(NBINS*BLOCKSIZE*BLOCKSIZE, 1), CV_32F);
	Point tl(0, pt.y - R);
	int c = 0;
	// 遍历块
	for (int i = 0; i < BLOCKSIZE; i++)
	{
		tl.x = pt.x - R;
		for (int j = 0; j < BLOCKSIZE; j++)
		{
			// 获取当前窗口进行局部直方图计算
			Rect roi(tl, tl + Point(CELLSIZE, CELLSIZE));
			Mat hist_temp = hist.colRange(c, c + NBINS);
			cacHOGinCell(hist_temp, roi, integrals);
			tl.x += CELLSIZE;
			c += NBINS;
		}
		tl.y = CELLSIZE;
	}
	normalize(hist, hist, 1, 0, NORM_L2);
	return hist;
}
// 计算HOG特征
std::vector<Mat> cacHOGFeature(cv::Mat srcImage)
{
	Mat grayImage;
	std::vector<Mat> HOGMatVector;
	cv::cvtColor(srcImage, grayImage, CV_RGB2GRAY);
	grayImage.convertTo(grayImage, CV_8UC1);
	// 积分图像生成
	std::vector<Mat> integrals = CalculateIntegralHOG(grayImage);
	Mat image = grayImage.clone();
	image *= 0.5;
	// Block遍历
	cv::Mat HOGBlockMat(Size(NBINS, 1), CV_32F);
	for (int y = CELLSIZE / 2; y < grayImage.rows; y += CELLSIZE)
	{
		for (int x = CELLSIZE / 2; x < grayImage.cols; x += CELLSIZE)
		{
			// 获取当前窗口HOG
			cv::Mat hist = getHog(Point(x, y), integrals);
			if (hist.empty())
				continue;
			HOGBlockMat = Scalar(0);
			for (int i = 0; i < NBINS; i++)
			{
				for (int j = 0; j < BLOCKSIZE; j++)
				{
					HOGBlockMat.at<float>(0, i) += hist.at<float>(0, i + j*NBINS);
				}
			}
			// L2范数归一化
			normalize(HOGBlockMat, HOGBlockMat, 1, 0, CV_L2);
			HOGMatVector.push_back(HOGBlockMat);
			Point center(x, y);
			// 绘制HOG特征图
			for (int i = 0; i < NBINS; i++)
			{
				double theta = (i * THETA + 90.0) * CV_PI / 180.0;
				Point rd(CELLSIZE*0.5*cos(theta), CELLSIZE*0.5*sin(theta));
				Point rp = center - rd;
				Point lp = center - -rd;
				line(image, rp, lp, Scalar(255 * HOGBlockMat.at<float>(0, i), 255, 255));
			}
		}
	}
	imshow("out", image);
	return HOGMatVector;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
	if (srcImage.empty())
		return -1;
	cv::imshow("srcImage ", srcImage);
	std::vector<Mat> HOGFeatureMat = cacHOGFeature(srcImage);
	cv::waitKey(0);
	return 0;
}
