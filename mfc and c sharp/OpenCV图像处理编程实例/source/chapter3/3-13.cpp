// 功能：代码 3-13 直方图变换——累计
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
    // 计算图像的直方图
    const int channels[1]={0};
    const int histSize[1]={256};
    float hranges[2]={0,255};
    const float* ranges[1]={hranges};
    cv::MatND hist;
    calcHist(&srcGray, 1, channels, cv::Mat(),
    	      hist, 1, histSize, ranges);
	float table[256];
	int nPix = srcGray.cols * srcGray.rows;
	// 建立映射表
	for (int i = 0; i < 256; i++) {	
		float temp[256];
		// 像素变换
		temp[i] = hist.at<float>(i) / nPix * 255;
		if (i != 0) {
			// 像素累计
			table[i] = table[i -1] + temp[i];
		} else {
			table[i] = temp[i];
		}
	}
	// 通过映射进行表查找
	cv::Mat lookUpTable(cv::Size(1, 256), CV_8U);
	for (int i =0; i <256; i++) {
		lookUpTable.at<uchar>(i) = 
		    static_cast<uchar>(table[i]);
	}
	cv::Mat histTransResult;
	cv::LUT(srcGray, lookUpTable, histTransResult);
       // 显示图像
	cv::imshow("srcGray",srcGray);
	cv::imshow("histTransResult",histTransResult);
	cv::waitKey(0);
	return 0;
}
