// 功能：代码 4-13 高斯平滑
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// 高斯平滑
void myGaussianBlur(const Mat& src, Mat& result, 
    int besarKernel, double delta)
{
    // 高斯核半径
    int kerR = besarKernel / 2;
    // 定义高斯核因子
    cv::Mat kernel = Mat_<double>(besarKernel, besarKernel);
    // 归一化参数
    double alpha = 1 / (2 * (22 / 7) * delta * delta);
    // 核函数生成
    for(int i = - kerR; i <= kerR; i++)
    {
        for(int j = - kerR; j <= kerR; j++)
        {
            kernel.at<double>(i + kerR, j + kerR) 
            = exp(-( ( ( j * j ) + ( i * i )  ) /
            (delta * delta * 2) )) * alpha;

        }
    }
    result = src.clone();
    double pix;
    // 遍历图像
    for(int i = kerR; i < src.rows - kerR; ++i)
    {
        for(int j = kerR; j < src.cols - kerR; ++j)
        {
            // 窗搜索完成高斯核平滑
            pix = 0;
            for(int k = -kerR; k <= kerR; ++k)
            {
                for(int n = -kerR; n <= kerR; ++n)
                {
                    pix += src.at<uchar>(i + k, j + n) * 
                          kernel.at<double>(kerR + k, kerR + n);
                }
            }
            result.at<uchar>(i - kerR, j - kerR) = pix;
        }
    }
}
int main(int argc, char *argv[])
{
    cv::Mat src = imread("..\\images\\flower3.jpg",0);  
    if(!src.data)   
      return -1;
    cv::Mat resMat;
    myGaussianBlur(src, resMat, 3, 1);
    cv::imshow("src", src);
    cv::imshow("resMat", resMat);
    cv::waitKey(0);
}


