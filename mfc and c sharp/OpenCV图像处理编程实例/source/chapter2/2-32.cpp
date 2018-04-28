// 功能：代码 2-33 文件名无规则情况读取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 代码 2-32 文件名连续情况下
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
	// 定义相关参数
	const int num = 4;
	char fileName[50];
	char windowName[50];
	cv::Mat srcImage;
	for (int i = 1; i <= num; i++)
	{
		// sprintf读入指定路径下图片序列
		sprintf_s(fileName, "..\\images\\test\\1 (%d).jpg", i);
		sprintf_s(windowName, "NO%d", i);
		// 按照图像文件名读取
		srcImage = cv::imread(fileName);
		if (!srcImage.data)
		{
			std::cout << "No data!" << std::endl;
			return -1;
		}
		cv::namedWindow(windowName);
		cv::imshow(windowName, srcImage);
		std::cout << "NO: " << i << std::endl;
		//cv::waitKey(0);
		/* 该处可以添加处理步骤 */
	}
	cv::waitKey(0);
	return 0;
}
