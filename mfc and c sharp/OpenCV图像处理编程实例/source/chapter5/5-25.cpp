// 功能：代码 5-25 moravec 角点检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// MoravecCorners角点检测
cv::Mat MoravecCorners(cv::Mat srcImage, int kSize, int threshold)
{
	cv::Mat resMorMat = srcImage.clone();
	// 获取初始化参数信息
	int r = kSize / 2;
	const int nRows = srcImage.rows;
	const int nCols = srcImage.cols;
	int nConut = 0;
	CvPoint *pPoint = new CvPoint[nRows*nCols];
	// 图像遍历
	for (int i = r; i < srcImage.rows-r; i++)
	{
		for (int j = r; j<srcImage.cols-r; j++)
		{
			int wV1, wV2, wV3, wV4;
			wV1 = wV2 = wV3 = wV4 = 0;
			// 计算水平方向窗内兴趣值
			for (int k = -r; k < r; k++)
				wV1 += (srcImage.at<uchar>(i,j+k)-
				srcImage.at<uchar>(i,j+k+1))*(srcImage.at
				<uchar>(i,j+k)-srcImage.at<uchar>(i,j+k+1));
			// 计算垂直方向窗内兴趣值
			for (int k = -r; k < r; k++)
				wV2 += (srcImage.at<uchar>(i+k,j)-
				srcImage.at<uchar>(i+k+1,j))*(srcImage.at
				<uchar>(i+k,j)-srcImage.at<uchar>(i+k+1,j));
			// 计算45度方向窗内兴趣值
			for (int k = -r; k < r; k++)
				wV3 += (srcImage.at<uchar>(i+k,j+k)-
				srcImage.at<uchar>(i+k+1,j+k+1))*(srcImage.at
				<uchar>(i+k,j+k)-srcImage.at<uchar>(i+k+1,j+k+1));
			// 计算135度方向窗内兴趣值
			for (int k = -r; k < r; k++)
				wV4 += (srcImage.at<uchar>(i+k,j-k)-
				srcImage.at<uchar>(i+k+1,j-k-1))*(srcImage.at
				<uchar>(i+k,j-k)-srcImage.at<uchar>(i+k+1,j-k-1));
			//std::cout << wV1 << wV2 <<  wV3 << wV4 << std::endl;
			// 取其中的最小值作为该像素点的最终兴趣值
			int value = min(min(wV1,wV2), min(wV3,wV4));
			// 若兴趣值大于阈值，则将点的坐标存入数组中 
			if (value > threshold)
			{
				pPoint[nConut] = cvPoint(j,i);
				nConut++;
			}
		}
	}
	//绘制兴趣点
	for (int i = 0; i < nConut; i++)
		cv::circle(resMorMat, pPoint[i], 5, cv::Scalar(255,0,0));
    return resMorMat;
}

int main()
{
	cv::Mat srcImage = imread("..\\images\\building.jpg",0);
	if (!srcImage.data)
		return -1;
	cv::Mat resMorMat =  MoravecCorners(srcImage, 5,10000);
	cv::imshow("srcImage", srcImage);
	cv::imshow("resMorMat",resMorMat);
	cv::waitKey(0);
	return 0;
}