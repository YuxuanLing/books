// 功能：代码 5-8 Roberts 边缘检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
// roberts算子实现
cv::Mat roberts(cv::Mat srcImage)
{
  cv::Mat dstImage = srcImage.clone();
  int nRows = dstImage.rows;
  int nCols = dstImage.cols;
  for (int i = 0; i < nRows - 1; i++)
  {
    for (int j = 0; j < nCols - 1; j++)
    {
      // 根据公式计算
      int t1 = (srcImage.at<uchar>(i, j) -
        srcImage.at<uchar>(i + 1, j + 1)) *
        (srcImage.at<uchar>(i, j) -
          srcImage.at<uchar>(i + 1, j + 1));
      int t2 = (srcImage.at<uchar>(i + 1, j) -
        srcImage.at<uchar>(i, j + 1)) *
        (srcImage.at<uchar>(i + 1, j) -
          srcImage.at<uchar>(i, j + 1));
      // 计算对角线像素差
      dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
    }
  }
  return dstImage;
}
int main()
{
  cv::Mat srcImage =
    cv::imread("..\\images\\building.jpg", 0);
  if (!srcImage.data)
    return -1;
  cv::imshow("srcImage", srcImage);
  cv::Mat dstImage = roberts(srcImage);
  cv::imshow("dstImage", dstImage);
  cv::waitKey(0);
  return 0;
}
