// 功能：代码 3-25 灰度比特平面
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
#include <stdio.h>
using namespace cv; 
using namespace std;
void showMBitPlan(cv::Mat srcImage)
{
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	// 图像连续性判断
	if(srcImage.isContinuous())
	{
		nCols  = nCols  * nRows;
		nRows = 1;
	}
	// 图像指针操作
	uchar *pSrcMat;
	uchar *pResultMat;
	cv::Mat resultImage = srcImage.clone();
	int pixMax = 0, pixMin = 0;
	for(int n = 1; n <= 8; n ++)
	{
		// 比特平面分层像素构成
		pixMin = pow(2, n - 1);
		pixMax = pow(2, n);
		for(int j = 0; j < nRows; j ++)
		{
			// 获取图像数据指针
			pSrcMat    = srcImage.ptr<uchar>(j);
			pResultMat = resultImage.ptr<uchar>(j);
			for(int i = 0; i < nCols; i ++)
			{
				// 相应比特平面层二值化
				if(pSrcMat[i] >= pixMin && pSrcMat[i] < pixMax)
					pResultMat[i] = 255;
				else
					pResultMat[i] = 0;
			}
		}
		// 比特平面层输出	
		char windowsName[20];
	    sprintf(windowsName, "BitPlane %d", n); 
	    imshow(windowsName, resultImage);	
	}
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
	if(!srcImage.data)
		return 0;	
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	imshow("srcGray", srcGray);
	showMBitPlan(srcGray);
	cv::waitKey(0);	 
	return 0;
}
