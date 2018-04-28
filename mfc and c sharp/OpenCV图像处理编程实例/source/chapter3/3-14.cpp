// 功能：代码 3-14 直方图匹配
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	 // 加载源图像并显示
	 cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	 cv::Mat dstImage = cv::imread("..\\images\\sea.jpg");
	 if( !srcImage.data || !dstImage.data ) 
	   return 1;
	 cv::resize(dstImage, dstImage,cv::Size(srcImage.rows,srcImage.cols),0,0,CV_INTER_LINEAR);
	 cv::imshow("srcImage", srcImage);
	 cv::imshow("dstImage", dstImage);
	 cv::waitKey(0);
	 //初始化累计分布参数
	 float srcCdfArr[256];
	 float dstCdfArr[256];
	 int srcAddTemp[256];
	 int dstAddTemp[256];
	 int histMatchMap[256];
	 for (int i = 0;  i < 256; i++){
		 srcAddTemp[i] = 0;
		 dstAddTemp[i] = 0;
		 srcCdfArr[i]= 0;
		 dstCdfArr[i] = 0;
		 histMatchMap[i]=0;
	 }
	 float sumSrcTemp = 0;
	 float sumDstTemp = 0;
	 int nSrcPix = srcImage.cols * srcImage.rows;
	 int nDstPix = dstImage.cols * dstImage.rows; 
	 int matchFlag = 0;
	 // 求解源图像与目标图像的累积直方图
	 for(size_t nrow = 0; nrow < srcImage.rows; nrow++)  
	    for(size_t ncol = 0; ncol < srcImage.cols; ncol++)
	    {	  
	 	    srcAddTemp[(int)srcImage.at<uchar>(nrow, ncol)]++;
			dstAddTemp[(int)dstImage.at<uchar>(nrow, ncol)]++;
	    }
	// 求解源图像与目标图像的累积概率分布
	 for(int i=0; i<256; i++)
	 {
	 	sumSrcTemp  +=  srcAddTemp[i];
	 	srcCdfArr[i] = sumSrcTemp  / nSrcPix;
		sumDstTemp += dstAddTemp[i];
		dstCdfArr[i] = sumDstTemp / nDstPix;
	 }
	 // 直方图匹配实现
	 for(int i=0; i< 256; i++)
	 {	
		float minMatchPara = 20;
	 	for(int j=0; j< 256; j++)
	 	{	
			// 判断当前直方图累计差异
	 		if (minMatchPara > abs(srcCdfArr[i] - dstCdfArr[j]))
	 		{
	 			minMatchPara = abs(srcCdfArr[i] - dstCdfArr[j]);
	 			matchFlag = j;
	 		}
	 	}
	 	histMatchMap[i] = matchFlag;
	 }
	 // 初始化匹配图像
	 cv::Mat HistMatchImage = 
		 cv::Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	 cv::cvtColor(srcImage, HistMatchImage, CV_BGR2GRAY);
	 // 通过map映射成匹配图像
	 for(int i = 0; i < HistMatchImage.rows; i++)  
	    for(int j = 0; j < HistMatchImage.cols; j++)
	    {
	 	   HistMatchImage.at<uchar>(i, j) = 
	 	       histMatchMap[(int)HistMatchImage.at<uchar>(i, j)];
	    }

    cv::imshow("resultImage", HistMatchImage);
    cv::waitKey(0);
	return 0;
}
