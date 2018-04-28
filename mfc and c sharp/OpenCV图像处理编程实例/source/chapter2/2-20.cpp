// 功能：代码 2-20 Rect 选择感兴趣区域
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
// 全局变量源图像
cv::Mat srcImage;
// 方法1 利用Rect选择区域(100, 180, 150, 50)
void regionExtraction(int xRoi, int yRoi, 
	int widthRoi, int heightRoi )
{
	// 指定坐标区域提取
    cv::Mat roiImage(srcImage.rows,srcImage.cols,CV_8UC3);
    std::cout << srcImage.rows  << " " << 
         srcImage.cols << std::endl;
    // 将兴趣区域拷贝到目标图像
    srcImage(cv::Rect(xRoi,yRoi,widthRoi,
    	heightRoi)).copyTo(roiImage);
    cv::imshow("roiImage",roiImage);
    cv::waitKey(0);
}
int main()
{
	// 源图像载入及判断
    srcImage = cv::imread("..\\images\\flower3.jpg");
    if( !srcImage.data ) 
       return 1;
	cv::imshow("ROIing", srcImage);
	cv::waitKey(0);
	// 方法1 利用Rect选择区域(100, 180, 150, 50)
	int xRoi = 80;
	int yRoi = 180;
	int widthRoi = 150;
	int heightRoi = 100;
    regionExtraction(xRoi,yRoi,widthRoi,heightRoi);	
	return 0;
}
