// 功能：代码 3-24 灰度级分层
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream>  
cv::Mat grayLayered(cv::Mat srcImage)
{
	cv::Mat resultImage = srcImage.clone();
	int nRows = resultImage.rows;
	int nCols = resultImage.cols;
	// 图像连续性判断
	if(resultImage.isContinuous())
	{
		nCols  = nCols  * nRows;
		nRows = 1;
	}
	// 图像指针操作
	uchar *pDataMat;
	int controlMin = 100;
	int controlMax = 200;
	// 计算图像的灰度级分层
	for(int j = 0; j <nRows; j ++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for(int i = 0; i < nCols; i ++)
		{
			// 第一种方法 二值映射
			if(pDataMat[i] > controlMin)       
				pDataMat[i] = 255;
			else
			    pDataMat[i] = 0;
			// // 第二种方法 区域映射
			// if(pDataMat[i] > controlMin && 
			// 	pDataMat[i] < controlMax)       
			// 	pDataMat[i] = controlMax;
		}
	}	
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
	if(!srcImage.data)
		return 0;	
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);	 
	imshow("srcGray", srcGray);
	cv::Mat resultImage = grayLayered(srcGray);
	cv::imshow("resultImage", resultImage);	 
	cv::waitKey(0);	 
	return 0;
}
