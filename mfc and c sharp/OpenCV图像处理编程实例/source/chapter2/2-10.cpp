// 功能：代码 2-10 图像缩放操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace cv;
// 基于等间隔提取图像缩放
cv::Mat imageReduction1(cv::Mat &srcImage, float kx, float ky)
{
    // 获取输出图像分辨率
    int nRows = cvRound(srcImage.rows * kx);
    int nCols = cvRound(srcImage.cols * ky);
    cv::Mat resultImage(nRows, nCols, srcImage.type());
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            // 根据水平因子计算坐标
            int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
            // 根据垂直因子计算坐标
            int y = static_cast<int>((j + 1) / ky+ 0.5) - 1;
            resultImage.at<cv::Vec3b>(i, j) = 
                srcImage.at<cv::Vec3b>(x, y);
        }
    }
    return resultImage;
}
cv::Vec3b areaAverage(const cv::Mat &srcImage,
     Point_<int> leftPoint, Point_<int> rightPoint)
{  
    int temp1 = 0,temp2 = 0,temp3 = 0;
    // 计算区域子块像素点个数
    int nPix = (rightPoint.x - leftPoint.x + 1)*
        (rightPoint.y - leftPoint.y + 1);
    // 区域子块各个通道对像素值求和
    for (int i = leftPoint.x; i <= rightPoint.x; i++){
        for (int j = leftPoint.y; j <= rightPoint.y; j++){ 
            temp1 += srcImage.at<cv::Vec3b>(i, j)[0];
            temp2 += srcImage.at<cv::Vec3b>(i, j)[1];
            temp3 += srcImage.at<cv::Vec3b>(i, j)[2];
        }
    }
    // 对每个通道求均值
    Vec3b vecTemp;
    vecTemp[0] = temp1 / nPix;
    vecTemp[1] = temp2 / nPix;
    vecTemp[2] = temp3 / nPix;
    return vecTemp;
}
cv::Mat  imageReduction2(const Mat &srcImage, double kx, 
    double ky)
{
    // 获取输出图像分辨率
    int nRows = cvRound(srcImage.rows * kx);
    int nCols = cvRound(srcImage.cols * ky);
    cv::Mat resultImage(nRows, nCols, srcImage.type());
    // 区域子块的左上角行列坐标
    int leftRowCoordinate = 0;
    int leftColCoordinate = 0;
    for (int i = 0; i < nRows; ++i)
    {   
        // 根据水平因子计算坐标
        int x = static_cast<int>((i + 1) / kx + 0.5) - 1;          
        for (int j = 0; j < nCols; ++j) {          
            // 根据垂直因子计算坐标
            int y = static_cast<int>((j + 1) / ky + 0.5) - 1; 
            // 求解区域子块的均值       
            resultImage.at<Vec3b>(i,j) = 
                areaAverage(srcImage, 
                Point_<int>(leftRowCoordinate, 
                leftColCoordinate), Point_<int>(x, y));
            // 更新下子块左上角的列坐标，行坐标不变
            leftColCoordinate = y + 1; 
        }
        leftColCoordinate = 0; 
        // 更新下子块左上角的行坐标
        leftRowCoordinate = x + 1; 
    }
    return resultImage;
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
    if(!srcImage.data) 
       return -1;
    cv::imshow("srcImage", srcImage);
    cv::Mat resultImage1 = 
        imageReduction1(srcImage, 0.5,0.5);
    cv::imshow("res1", resultImage1);
    cv::Mat resultImage2 = 
        imageReduction2(srcImage, 0.5, 0.5);
    cv::imshow("res2", resultImage2);
    cv::waitKey(0);
    return 0;
}
