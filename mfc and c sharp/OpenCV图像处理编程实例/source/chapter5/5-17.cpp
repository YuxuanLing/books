// 功能：代码 5-17 LSD 快速线检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
int main()
{
	
	cv::Mat srcImage = 
      cv::imread("..\\images\\building.jpg", 0);
  	if (!srcImage.data)   
       return -1;
	// canny边缘检测
	Canny(srcImage, srcImage, 50, 200, 3);
	// 创建LSD检测类
#if 1
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
#else
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_NONE);
#endif
	double start = double(getTickCount());
	vector<Vec4f> lines_std;
	// 线检测
	ls->detect(srcImage, lines_std);
	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();
	std::cout << "It took " << duration_ms << " ms." << std::endl;
	// 绘图线检测结果
	Mat drawnLines(srcImage);
	ls->drawSegments(drawnLines, lines_std);
	cv::imshow("Standard refinement", drawnLines);
	cv::waitKey();
	return 0;
}
