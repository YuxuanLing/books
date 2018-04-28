// 功能：代码 3-27 计算图像波峰点
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
// 计算图像的波峰
void findPeak(cv::Mat srcImage, vector<int>& resultVec)
{
	cv::Mat verMat;
	cv::Mat resMat = srcImage.clone();
	// 阈值化操作
	int thresh = 130; 
	int threshType = 0; 
	// 预设最大值
	const int maxVal = 255;
	// 固定阈值化操作
	cv::threshold( srcImage, srcImage, thresh, 
	      maxVal , threshType );
	srcImage.convertTo(srcImage, CV_32FC1);
	// 计算垂直投影
	cv::reduce(srcImage, verMat, 0, CV_REDUCE_SUM);
	// std::cout << verMat << std::endl;
	// 遍历求差分符号函数
	float* iptr = ((float*)verMat.data) + 1;
	vector<int> tempVec(verMat.cols - 1, 0);
	for (int i = 1; i < verMat.cols - 1; ++i, ++iptr)
	{
		if (*(iptr + 1) - *iptr >0)
			tempVec[i] = 1;
		else if (*(iptr + 1) - *iptr < 0)
			tempVec[i] = -1;
		else
			tempVec[i] = 0;
	}
	// 对符号函数进行遍历
	for (int i = tempVec.size() - 1; i >= 0; i--)
	{
		if (tempVec[i] == 0 && i == tempVec.size() - 1)
		{
			tempVec[i] = 1;
		}
		else if (tempVec[i] == 0)
		{
			if (tempVec[i + 1] >= 0)
				tempVec[i] = 1;
			else
				tempVec[i] = -1;
		}
	}
	// 波峰判断输出
	for (vector<int>::size_type i = 0; i != tempVec.size() - 1;i++)
	{
		if (tempVec[i + 1] - tempVec[i] == -2)
			resultVec.push_back(i + 1);
	} 
    // 输出波峰位置
    for(int i = 0; i< resultVec.size(); i++)
    {
    	std::cout << resultVec[i] << " ";
        //resMat.at(resultVec[i], resultVec[i]) = 255;
        for (int ii = 0; ii < resMat.rows; ++ii)
		{
		     resMat.at<uchar>(ii,resultVec[i])=255;
		}
    }
    imshow("resMat", resMat);
}
int main()
{
	cv::Mat image = imread("..\\images\\test.jpg",0);
	if(!image.data)
		return 0;
	imshow("Image", image);
	vector<int> resultVec;
	findPeak(image, resultVec);
	cv::waitKey(0);
	return 0;
}
