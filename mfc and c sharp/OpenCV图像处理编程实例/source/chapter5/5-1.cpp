// 功能：代码 5-1 差分边缘检测实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
// 图像差分操作
void diffOperation(const cv::Mat srcImage, cv::Mat& edgeXImage,
	cv::Mat& edgeYImage)
{
	cv::Mat tempImage = srcImage.clone();
	int nRows = tempImage.rows;
	int nCols = tempImage.cols;
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j < nCols - 1; j++)
		{
			// 计算垂直边边缘
			edgeXImage.at<uchar>(i, j) =
				abs(tempImage.at<uchar>(i + 1, j) -
					tempImage.at<uchar>(i, j));
			// 计算水平边缘
			edgeYImage.at<uchar>(i, j) =
				abs(tempImage.at<uchar>(i, j + 1) -
					tempImage.at<uchar>(i, j));
		}
	}
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat edgeXImage(srcImage.size(), srcImage.type());
	cv::Mat edgeYImage(srcImage.size(), srcImage.type());
	// 计算查分图像
	diffOperation(srcImage, edgeXImage, edgeYImage);
	cv::imshow("edgeXImage", edgeXImage);
	cv::imshow("edgeYImage", edgeYImage);
	cv::Mat edgeImage(srcImage.size(), srcImage.type());
	// 水平与垂直边缘图像叠加
	addWeighted(edgeXImage, 0.5, edgeYImage,
		0.5, 0.0, edgeImage);
	cv::imshow("edgeImage", edgeImage);
	cv::waitKey(0);
	return 0;
}
