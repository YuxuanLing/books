// 功能：代码 5-15 Marr-Hildreth 边缘检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void marrEdge(const Mat src, Mat& result, int kerValue,
  double delta)
{
    // 计算LOG算子
    Mat kernel;
    // 半径
    int kerLen = kerValue / 2;
    kernel = Mat_<double>(kerValue, kerValue); 
    // 滑窗
    for(int i = - kerLen; i <= kerLen; i++)
    {
        for(int j = - kerLen; j <= kerLen; j++)
        {
            // 核因子生成
            kernel.at<double>(i + kerLen, j + kerLen) =
                    exp(-( ( pow(j, 2)  + pow( i, 2 )  ) /
                     ( pow(delta, 2) * 2) ))
                    * ( ( ( pow(j, 2)  + pow( i, 2 ) - 2 *
                     pow(delta, 2) ) /  (2 * pow(delta, 4) ) ));
        }
    }
    // 输出参数设置
    int kerOffset = kerValue / 2;
    Mat laplacian =  (Mat_<double>(src.rows - kerOffset * 2, 
        src.cols - kerOffset*2));
    result = Mat::zeros(src.rows - kerOffset*2, 
        src.cols - kerOffset*2, src.type());
    double sumLaplacian;
    // 遍历计算卷积图像的Lapace算子
    for(int i = kerOffset; i < src.rows - kerOffset; ++i)
    {
        for(int j = kerOffset; j < src.cols - kerOffset; ++j)
        {
            sumLaplacian = 0;
            for(int k = -kerOffset; k <= kerOffset; ++k)
            {
                for(int m = -kerOffset; m <= kerOffset; ++m)
                {
                    // 计算图像卷积
                    sumLaplacian += src.at<uchar>(i + k, j + m) *
                     kernel.at<double>(kerOffset + k,
                     kerOffset + m);
                }
            }
            // 生成Lapace结果
            laplacian.at<double>(i - kerOffset,
               j - kerOffset) = sumLaplacian;
        }
    }
    // 过零点交叉 寻找边缘像素
    for(int y = 1; y < result.rows - 1; ++y)
    {
        for(int x = 1; x < result.cols - 1; ++x)
        {
            result.at<uchar>(y,x) = 0;
            // 邻域判定
            if(laplacian.at<double>(y - 1,x) * 
                laplacian.at<double>(y + 1,x) < 0)
            {
                result.at<uchar>(y,x) = 255;
            }
            if(laplacian.at<double>(y, x - 1) * 
                laplacian.at<double>(y, x + 1) < 0)
            {
                result.at<uchar>(y,x) = 255;
            }
            if(laplacian.at<double>(y + 1, x - 1) * 
                laplacian.at<double>(y - 1, x + 1) < 0)
            {
                result.at<uchar>(y,x) = 255;
            }
            if(laplacian.at<double>(y - 1, x - 1) *
             laplacian.at<double>(y + 1, x + 1) < 0)
            {
                result.at<uchar>(y,x) = 255;
            }
        }
    }
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\building.jpg", 0);
    if (!srcImage.data)   
       return -1;
    cv::Mat edge;
    marrEdge(srcImage, edge, 9, 1.6);
    cv::imshow("srcImage", srcImage);
    cv::imshow("edge", edge);
    cv::waitKey(0);
    return 0;
}
