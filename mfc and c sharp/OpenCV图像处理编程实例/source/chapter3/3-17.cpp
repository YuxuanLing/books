// 功能：代码 3-17 mixChannels 应用
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h> 
using namespace std;
using namespace cv;
int main()
{
	cv::Mat rgba( 10, 10, CV_8UC4, cv::Scalar(1,2,3,4) );
	cv::Mat bgr( rgba.rows, rgba.cols, CV_8UC3 );
	cv::Mat alpha( rgba.rows, rgba.cols, CV_8UC1 );
		//对数据头进行复制
	cv::Mat out[] = { bgr, alpha };
	// 通道转换rgba[0] -> bgr[2], rgba[1]-> bgr[1],
	// rgba[2] -> bgr[0], rgba[3] -> alpha[0]
	int from_to[] = { 0,2, 1,1, 2,0, 3,3 };
	mixChannels( &rgba, 1, out, 2, from_to, 4 );
	std::cout << out[0] << std::endl;
	std::cout << out[1] << std::endl;
	return 0;
}
