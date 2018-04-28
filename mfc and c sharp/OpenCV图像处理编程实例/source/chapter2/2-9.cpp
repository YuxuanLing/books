// 功能：代码 2-9 图像平移操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
// 平移操作 图像大小不变
cv::Mat imageTranslation1(cv::Mat & srcImage, int xOffset,
     int yOffset)
{
    int nRows = srcImage.rows;
    int nCols = srcImage.cols;
    cv::Mat resultImage(srcImage.size(),
        srcImage.type());
    // 遍历图像
    for (int i = 0; i < nRows; ++i)
    {
        for (int j = 0; j < nCols; ++j)
        {
            // 映射变换
            int x = j - xOffset;
            int y = i - yOffset;
            // 边界判断
            if (x >= 0 && y >= 0 && x < nCols && y < nRows)
                resultImage.at<cv::Vec3b>(i,j) = 
                        srcImage.ptr<cv::Vec3b>(y)[x];
        }
    }
    return resultImage;
}
// 平移操作 图像大小改变 
cv::Mat imageTranslation2(cv::Mat & srcImage, int xOffset, 
    int yOffset)
{
    // 设置平移尺寸
    int nRows = srcImage.rows + abs(yOffset); 
    int nCols = srcImage.cols + abs(xOffset);
    cv::Mat resultImage(nRows, nCols,
        srcImage.type());
    for (int i = 0; i < nRows; ++i)
    {
        for (int j = 0; j < nCols; ++j)
        {
            // 映射变换
            int x = j - xOffset;
            int y = i - yOffset;
            // 边界判断
            if (x >= 0 && y >= 0 && x < nCols && y < nRows)
               resultImage.at<cv::Vec3b>(i,j) = 
                        srcImage.ptr<cv::Vec3b>(y)[x];
        }
    }
    return resultImage;
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg"); 
    if(!srcImage.data) 
       return -1;
    cv::imshow("srcImage", srcImage);
    int xOffset = 50, yOffset = 80;
    // 图像左平移不改变大小
    cv::Mat resultImage1 = 
        imageTranslation1(srcImage, xOffset, yOffset);
    cv::imshow("resultImage1", resultImage1);
    // 图像左平移改变大小
    cv::Mat resultImage2 = 
        imageTranslation2(srcImage, xOffset, yOffset);
    cv::imshow("resultImage2", resultImage2);
    // 图像右平移不改变大小
    xOffset = -50, yOffset = -80;
    cv::Mat resultImage3 = 
        imageTranslation1(srcImage, xOffset, yOffset);
    cv::imshow("resultImage3", resultImage3);
    cv::waitKey(0);
    return 0;
}
