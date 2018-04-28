// 功能：代码 4-1 最近邻插值实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace cv;
using namespace std;
// 实现最近邻插值图像缩放
cv::Mat nNeighbourInterpolation(cv::Mat srcImage)
{
    // 判断输入有效性
	CV_Assert(srcImage.data != NULL);
    int rows = srcImage.rows;
	int cols = srcImage.cols;
	// 构建目标图像
	cv::Mat dstImage = cv::Mat(
		cv::Size(150, 150), srcImage.type(), 
       cv::Scalar::all(0));
	int dstRows = dstImage.rows;
	int dstCols = dstImage.cols;
	// 坐标转换 求取缩放倍数
	float cx = (float)cols / dstCols;
	float ry = (float)rows / dstRows; 
	std::cout << "cx: " << cx << "ry:" << ry << std::endl;
	// 遍历图像完成缩放操作
    for(int i = 0 ; i < dstCols; i++)
    {
    	// 取整获取目标图像在源图像对应坐标
    	int ix = cvFloor(i * cx);  
    	for(int j = 0; j < dstRows; j++)
    	{
            int jy = cvFloor(j * ry);
            // 边界处理 防止指针越界
            if(ix > cols - 1)
        		ix = cols - 1;
         	if(jy > rows - 1)
        		jy = rows - 1;
        	// 映射矩阵
           dstImage.at<cv::Vec3b>(j, i) = 
                srcImage.at<cv::Vec3b>(jy, ix);
    	}   	 
    }
    return  dstImage;
}
int main()
{
    // 图像源获取及验证
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
     if( !srcImage.data ) 
	   return -1;
    // 最近邻插值缩放操作
	cv::Mat dstImage = nNeighbourInterpolation(srcImage);
    cv::imshow("srcImage", srcImage);
    cv::imshow("dstImage", dstImage);
    cv::waitKey(0);
	return 0;
}
