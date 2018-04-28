// 功能：代码 8-12 计算 LBP 特征
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 8-12 计算 LBP 特征
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
// 计算原始LBP特征
cv::Mat OLBP(cv::Mat& srcImage)
{
	const int nRows = srcImage.rows;
	const int nCols = srcImage.cols;
	cv::Mat resultMat(srcImage.size(), srcImage.type());
	// 遍历图像，生成LBP特征
	for (int y = 1; y < nRows - 1; y++)
	{
		for (int x = 1; x < nCols - 1; x++)
		{
			// 定义邻域
			uchar neighbor[8] = { 0 };
			neighbor[0] = srcImage.at<uchar>(y - 1, x - 1);
			neighbor[1] = srcImage.at<uchar>(y - 1, x);
			neighbor[2] = srcImage.at<uchar>(y - 1, x + 1);
			neighbor[3] = srcImage.at<uchar>(y, x + 1);
			neighbor[4] = srcImage.at<uchar>(y + 1, x + 1);
			neighbor[5] = srcImage.at<uchar>(y + 1, x);
			neighbor[6] = srcImage.at<uchar>(y + 1, x - 1);
			neighbor[7] = srcImage.at<uchar>(y, x - 1);
			// 当前图像的处理中心 
			uchar center = srcImage.at<uchar>(y, x);
			uchar temp = 0;
			// 计算LBP的值 
			for (int k = 0; k < 8; k++)
			{
				// 遍历中心点邻域
				temp += (neighbor[k] >= center)* (1 << k);
			}
			resultMat.at<uchar>(y, x) = temp;
		}
	}
	return resultMat;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg", 0);
	if (!srcImage.data)
		return 0;
	cv::Mat resultMat = OLBP(srcImage);
	cv::imshow("srcImage", srcImage);
	cv::imshow("resultMat", resultMat);
	cv::waitKey(0);
	return 0;
}
