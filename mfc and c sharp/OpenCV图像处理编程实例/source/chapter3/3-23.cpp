// 功能：代码 3-23 对比度拉伸
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream>  
cv::Mat contrastStretch(cv::Mat srcImage)
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
	int pixMax = 0, pixMin = 255;
	// 计算图像的最大最小值
	for(int j = 0; j <nRows; j ++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for(int i = 0; i < nCols; i ++)
		{
			if(pDataMat[i] > pixMax)       
				pixMax = pDataMat[i];
			if(pDataMat[i] < pixMin)      
				pixMin = pDataMat[i];
		}
	}
    // 对比度拉伸映射
	for(int j = 0; j < nRows; j ++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for(int i = 0; i < nCols; i ++)
		{
			pDataMat[i] = (pDataMat[i] - pixMin) * 
			    255 / (pixMax - pixMin);
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
	cv::Mat resultImage = contrastStretch(srcGray);
	cv::imshow("resultImage", resultImage);	 
	cv::waitKey(0);	 
	return 0;
}
