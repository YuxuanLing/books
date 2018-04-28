// 功能：代码 5-23 计算轮廓矩
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
using namespace std;
// 计算图像矩
void cacMoments(cv::Mat src)
{
    Mat srcGray;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    // 高斯滤波
    GaussianBlur( src, src, Size(3,3), 0.1, 0, BORDER_DEFAULT );
    // 灰度转换
    cvtColor(src, srcGray, CV_RGB2GRAY);
    // 轮廓边界检测
    findContours(srcGray, contours, hierarchy,
        CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    // 绘制边界
    // drawContours(src, contours, -1, cvScalar(0,0,255));
    printf("Number of contours: %d\n", (int)contours.size());
    // 计算轮廓矩
    vector<Moments> mu(contours.size());
    for(int i = 0; i < (int)contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    // 分析矩计算图像相关特征
    for(int i = 0; i < (int)contours.size(); i++)
    {
        // 面积 重心 边界轮廓长度
        int area = mu[i].m00;
        int cx = mu[i].m10/mu[i].m00;
        int cy = mu[i].m01/mu[i].m00;
        int perimeter = arcLength(contours.at(i), true);
        // 椭圆
        if (int(contours.at(i).size()) <= 5)
        {
            continue;
        }else
        {
            RotatedRect rRect = fitEllipse(contours.at(i));
            double orientation = rRect.angle;
            double orientation_rads = orientation*3.1416/180;
            double majorAxis = rRect.size.height > rRect.size.width ? rRect.size.height : rRect.size.width;
            double minorAxis = rRect.size.height > rRect.size.width ? rRect.size.width : rRect.size.height;
            // 圆形度 离心率 周长 直径
            double roundness = pow(perimeter, 2)/(2*3.1416*area);
            double eccentricity = sqrt(1-pow(minorAxis/majorAxis,2));
            double ratio = (minorAxis / majorAxis) * 100;
            double diameter = sqrt((4*area)/3.1416);
            // 输出相关特征信息
            printf("Area: %d\n", area);
            printf("Perimeter: %d\n", perimeter);
            printf("Major Axis: %.1f\n", majorAxis);
            printf("Minor Axis: %.1f\n", minorAxis);
            printf("Orientation: %.1f\n", orientation);
            printf("Roundness: %.1f\n", roundness);
            printf("Eccentricity: %.1f\n", eccentricity);
            printf("Ratio: %.1f\n", ratio);
            printf("Diameter: %.1f\n", diameter);
            printf("\n");
            // 绘制矩形及椭圆
            ellipse(src, rRect, cvScalar(0,255,0));
            rectangle(src, boundingRect(contours.at(i)), cvScalar(0,0,255));
            // 绘制相关坐标
            //line(src, Point(cx-30, cy), Point(cx+30, cy), cvScalar(0,0,255));
            //line(src, Point(cx, cy-30), Point(cx, cy+30), cvScalar(0,0,255));
            // 绘制起始线
            line(src, Point(cx, cy), Point((int)(cx+30*cos(orientation_rads)),
                (int)(cy+30*sin(orientation_rads))), cvScalar(255,0,0), 1);
            // 输出图像起始
            char pChar[100];
            sprintf(pChar, "Ori: %.0f", orientation);
            putText(src, pChar, Point(cx, cy), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255));
        }
    }
    cv::imshow( "result", src);
}
int main(){
    cv::Mat srcImage = imread("..\\images\\test.jpg");
    if( !srcImage.data )
        return -1; 
    cv::imshow( "srcImage", srcImage );
    // 计算轮廓矩
    cacMoments(srcImage);  
    cv::waitKey(0);
    return(0);
}