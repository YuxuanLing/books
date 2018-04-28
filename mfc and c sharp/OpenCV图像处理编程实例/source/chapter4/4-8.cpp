// 功能：代码 4-8 图像添加椒盐噪声
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
// 图像添加椒盐噪声
cv::Mat addSaltNoise(const cv::Mat srcImage, int n)
{
    cv::Mat resultIamge =srcImage.clone() ;
    for(int k=0; k<n; k++)
    {
        // 随机取值行列
        int i = rand() % resultIamge.cols;
        int j = rand() % resultIamge.rows;
        // 图像通道判定
        if(resultIamge.channels() == 1)
        {
            resultIamge.at<uchar>(j,i) = 255;
        }else
        {
            resultIamge.at<cv::Vec3b>(j,i)[0] = 255;
            resultIamge.at<cv::Vec3b>(j,i)[1] = 255;
            resultIamge.at<cv::Vec3b>(j,i)[2] = 255;
        }
    }
    return resultIamge;
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
    if( srcImage.empty())
        return -1;
    cv::Mat resultImage = addSaltNoise(srcImage, 5000);
    cv::imshow("srcImage",srcImage);
    cv::imshow("resultImage",resultImage);
    cv::waitKey(0);
}
