// 功能：代码 4-7 图像卷积操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
// 图像卷积操作
void convolution(cv::Mat src, cv::Mat kernel, cv::Mat& dst)
{
    // 输出图像定义
    dst.create(abs(src.rows - kernel.rows)+1, 
        abs(src.cols - kernel.cols)+1, src.type());
    cv::Size dftSize;
    // 计算傅里叶变换尺寸
    dftSize.width = getOptimalDFTSize(src.cols + 
           kernel.cols - 1);
    dftSize.height = getOptimalDFTSize(src.rows +
            kernel.rows - 1);
    // 创建临时图像初始化为0
    cv::Mat tempA(dftSize, src.type(), Scalar::all(0));
    cv::Mat tempB(dftSize, kernel.type(), Scalar::all(0));
    // 对于区域拷贝
    cv::Mat roiA(tempA, Rect(0,0,src.cols,src.rows));
    src.copyTo(roiA);
    cv::Mat roiB(tempB, Rect(0,0,kernel.cols,kernel.rows));
    kernel.copyTo(roiB);
    // 傅里叶变换
    dft(tempA, tempA, 0, src.rows);
    dft(tempB, tempB, 0, kernel.rows);
    // 对于两张频谱图中每一个元素的乘法
    mulSpectrums(tempA, tempB, tempA, DFT_COMPLEX_OUTPUT);
    // 变换结果所有行非零
    dft(tempA, tempA, DFT_INVERSE + DFT_SCALE, dst.rows);
    // 拷贝结果到输出图像
    tempA(Rect(0, 0, dst.cols,dst.rows)).copyTo(dst);
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg", 0);
    if( srcImage.empty())
        return -1;
    // 定义卷积核算子
    cv::Mat kernel = (cv::Mat_<float>(3,3) << 1, 1, 1, 
                                      1, 1, 1, 
                                      1, 1, 1);
    imshow("srcImage", srcImage);
    srcImage.convertTo(srcImage, CV_32F);
    cv::Mat resultImage;
    // 卷积操作
    convolution(srcImage, kernel, resultImage);
    // 归一化结果输出
    normalize(resultImage, resultImage, 0, 1, CV_MINMAX);  
    cv::imshow("resultImage", resultImage);
    cv::waitKey(0);
    return 0;
}
