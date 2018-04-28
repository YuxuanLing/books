// 功能：代码 2-17 图像质量评价
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
// PSNR 峰值信噪比计算 返回数值为30-50dB 值越大越好
double PSNR(const Mat& I1, const Mat& I2)
{
    cv::Mat s1;
    // 计算图像差|I1 - I2|
    absdiff(I1, I2, s1);
    // 转成32浮点数进行平方
    s1.convertTo(s1, CV_32F);
    // s1*s1，即|I1 - I2|^2
    s1 = s1.mul(s1);
    // 分别叠加每个通道的元素，存于s中
    cv::Scalar s = sum(s1);
    // 计算所有通道元素和
    double sse = s.val[0] + s.val[1] + s.val[2];
    // 当元素很小时返回0值
    if (sse <= 1e-10)
        return 0;
    else
    {
        // 根据公式计算当前I1与I2的均方误差
        double mse = sse / (double)(I1.channels() * I1.total());
        // 计算峰值信噪比
        double psnr = 10.0*log10((255 * 255) / mse);
        return psnr;
    }
}
// MSSIM 结构相似性计算 返回值为0到1 值越大越好
cv::Scalar MSSIM(const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    cv::Mat I1, I2;
    // 转换成32浮点数进行平方操作
    i1.convertTo(I1, CV_32F);
    i2.convertTo(I2, CV_32F);
    // I2^2
    cv::Mat I2_2 = I2.mul(I2);
    cv::Mat I1_2 = I1.mul(I1);
    cv::Mat I1_I2 = I1.mul(I2);
    cv::Mat mu1, mu2;
    // 高斯加权计算每一窗口的均值、方差以及协方差
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    // 高斯平滑，具体原理见4.4节
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    // 根据计算公式相应参数
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t3 = t1.mul(t2);
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    t1 = t1.mul(t2);
    Mat ssim_map;
    // ssim_map =  t3./t1;
    divide(t3, t1, ssim_map);
    // 将平均值作为两图像的结构相似性度量    
    cv::Scalar mssim = mean(ssim_map);
    return mssim;
}

int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\flower.jpg");
    cv::imshow("srcImage", srcImage);
    cv::Mat pyrDownImage, pyrUpImage;
    // 下采样过程
    pyrDown(srcImage, pyrDownImage,
        cv::Size(srcImage.cols / 2, srcImage.rows / 2));
    cv::imshow("pyrDown", pyrDownImage);
    // 上采样过程
    pyrUp(srcImage, pyrUpImage,
        cv::Size(srcImage.cols * 2, srcImage.rows * 2));
    cv::imshow("pyrUp", pyrUpImage);
    // 对下采样过程重构
    cv::Mat pyrBuildImage;
    pyrUp(pyrDownImage, pyrBuildImage,
        cv::Size(pyrDownImage.cols * 2, pyrDownImage.rows * 2));
    cv::imshow("pyrBuildImage", pyrBuildImage);
    double dPNSR = PSNR(srcImage, pyrBuildImage);
    std::cout << "dPNSR: " << dPNSR << std::endl;

    cv::Scalar sMSSIM = MSSIM(srcImage, pyrBuildImage);

    std::cout << "sMSSIM: " << sMSSIM.val[0] << " "  << sMSSIM.val[1] << " " <<  sMSSIM.val[2]  << std::endl;
    cv::waitKey(0);
    return 0;
}
