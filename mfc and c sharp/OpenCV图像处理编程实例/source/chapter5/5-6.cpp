// 功能：5-6 OpenCV 自带库图像边缘计算
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
int main()
{
    cv::Mat srcImage = imread("..\\images\\building.jpg");
    if (!srcImage.data)
        return -1;
    cv::Mat srcGray;
    cvtColor(srcImage, srcGray, CV_RGB2GRAY);
    imshow("srcGray", srcGray);
    // 定义边缘图，水平及垂直
    cv::Mat edgeMat, edgeXMat, edgeYMat;
    // 求x方向Sobel边缘
    Sobel(srcGray, edgeXMat, CV_16S, 1, 0, 3, 1,
        0, BORDER_DEFAULT);
    // 求y方向Sobel边缘
    Sobel(srcGray, edgeYMat, CV_16S, 0, 1, 3, 1,
        0, BORDER_DEFAULT);
    // 线性变换转换输入数组元素成8位无符号整型
    convertScaleAbs(edgeXMat, edgeXMat);
    convertScaleAbs(edgeYMat, edgeYMat);
    // x与y方向边缘叠加
    addWeighted(edgeXMat, 0.5, edgeYMat, 0.5, 0, edgeMat);
    cv::imshow("edgeYMat", edgeYMat);
    imshow("edgeMat", edgeMat);
    // 定义Scharr边缘图像
    cv::Mat edgeMatS, edgeXMatS, edgeYMatS;
    // 计算x方向Scharr边缘
    Scharr(srcGray, edgeXMatS, CV_16S, 1, 0, 1,
        0, BORDER_DEFAULT);
    convertScaleAbs(edgeXMatS, edgeXMatS);
    // 计算y方向Scharr边缘
    Scharr(srcGray, edgeYMatS, CV_16S, 0, 1, 1,
        0, BORDER_DEFAULT);
    // 线性变换转换输入数组元素成8位无符号整型
    convertScaleAbs(edgeYMatS, edgeYMatS);
    // x与y方向边缘叠加
    addWeighted(edgeXMatS, 0.5, edgeYMatS, 0.5, 0, edgeMatS);
    cv::imshow("edgeMatS", edgeMatS);
    cv::waitKey(0);
    return 0;
}
