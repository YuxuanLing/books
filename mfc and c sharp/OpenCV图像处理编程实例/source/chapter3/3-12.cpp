// 功能：代码 3-12 直方图变换——查找
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
int main()
{
   	// 图像获取及验证
 	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
  	if( !srcImage.data ) 
    	return 1;
    // 转化为灰度图像
    cv::Mat srcGray;
    cvtColor(srcImage, srcGray, CV_BGR2GRAY);
    // 第一步：计算图像的直方图
    const int channels[1]={0};
    const int histSize[1]={256};
    float hranges[2]={0,255};
    const float* ranges[1]={hranges};
    cv::MatND hist;
    calcHist(&srcGray,1,channels,cv::Mat(),
               hist,1,histSize,ranges);
    // 第二步：根据预设参数统计灰度级变换
    int segThreshold = 50;
    // 由低到高进行查找
	int iLow =0;
	for (; iLow < histSize[0]; iLow++) {
		if (hist.at<float>(iLow) > segThreshold) {
			break;
		}
	}
	// 由高到低进行查找
	int iHigh = histSize[0] -1;
	for (; iHigh >=0; iHigh--) {
		if (hist.at<float>(iHigh) > segThreshold) {
			break;
		}
	}
	// 第三步：建立查找表
	cv::Mat lookUpTable(cv::Size(1, 256), CV_8U);
	for (int i =0; i <256; i++) {
		if (i < iLow ){
			lookUpTable.at<uchar>(i) =0;
		} else if (i > iHigh) {
			lookUpTable.at<uchar>(i) = 255;
		} else {
			lookUpTable.at<uchar>(i) = static_cast<uchar>(
           255.0 * (i - iLow) / (iHigh - iLow + 0.5));
		}
	}
	// 第四步：通过查找表进行映射变换
	cv::Mat histTransResult;
	cv::LUT(srcGray, lookUpTable, histTransResult);
    // 显示图像
	cv::imshow("srcGray",srcGray);
	cv::imshow("histTransResult",histTransResult);
	cv::waitKey(0);
	return 0;
}
