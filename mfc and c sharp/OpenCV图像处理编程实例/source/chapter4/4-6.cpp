// 功能：代码 4-6 图像傅里叶变换
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
cv::Mat DFT(cv::Mat srcImage)
{
       cv::Mat srcGray;
       cvtColor(srcImage,srcGray,CV_RGB2GRAY);
       // 将输入图像延扩到最佳的尺寸
       int nRows = getOptimalDFTSize(srcGray.rows);
       int nCols = getOptimalDFTSize(srcGray.cols);
       cv::Mat resultImage;
       // 把灰度图像放在左上角,在右边和下边扩展图像,
       // 添加的像素初始化为0
       copyMakeBorder(srcGray, resultImage, 0,
            nRows - srcGray.rows, 
            0, nCols - srcGray.cols, 
            BORDER_CONSTANT, Scalar::all(0));
       // 为傅立叶变换的结果(实部和虚部)分配存储空间
       cv::Mat planes[] = { cv::Mat_<float>(resultImage), 
            cv::Mat::zeros(resultImage.size(), CV_32F)};
       Mat completeI;
       // 为延扩后的图像增添一个初始化为0的通道
       merge(planes,2,completeI);
       // 进行离散傅立叶变换
       dft(completeI,completeI);
       // 将复数转换为幅度
       split(completeI,planes);
       magnitude(planes[0],planes[1],planes[0]);
       cv::Mat dftResultImage = planes[0]; 
       // 对数尺度(logarithmic scale)缩放
       dftResultImage += 1;
       log(dftResultImage,dftResultImage);
       // 剪切和重分布幅度图象限
       dftResultImage= dftResultImage(Rect(0,
            0,srcGray.cols,srcGray.rows));
       // 归一化图像
       normalize(dftResultImage,dftResultImage,
            0,1,CV_MINMAX);
       int cx = dftResultImage.cols/2;
       int cy = dftResultImage.rows/2; 
       Mat tmp;
       // Top-Left - 为每一个象限创建ROI
       Mat q0(dftResultImage,Rect(0,0,cx,cy));
       // Top-Right
       Mat q1(dftResultImage,Rect(cx,0,cx,cy));
       // Bottom-Left
       Mat q2(dftResultImage,Rect(0,cy,cx,cy));
       // Bottom-Right
       Mat q3(dftResultImage,Rect(cx,cy,cx,cy)); 
       // 交换象限 (Top-Left with Bottom-Right)    
       q0.copyTo(tmp);
       q3.copyTo(q0);
       tmp.copyTo(q3);
       // 交换象限 (Top-Right with Bottom-Left)
       q1.copyTo(tmp);
       q2.copyTo(q1);
       tmp.copyTo(q2);
       return dftResultImage;
}
int main()
{
      cv::Mat srcImage = imread("..\\images\\flower3.jpg");
      if(srcImage.empty())
      return-1;
      imshow("srcImage", srcImage);
      cv::Mat resultImage = DFT(srcImage);
      imshow("resultImage", resultImage);
      cv::waitKey(0);
      return 0;
}
