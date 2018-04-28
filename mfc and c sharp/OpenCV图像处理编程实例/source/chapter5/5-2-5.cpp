// 功能：代码 5-2-5 Sobel 边缘实现
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
// 非极大值抑制实现sobel竖直细化边缘
bool SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
    CV_Assert(srcImage.channels() == 1);
    srcImage.convertTo(srcImage, CV_32FC1);
    // 水平方向的 Sobel 算子
    cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
        -0.25, 0, 0.25,
        -0.125, 0, 0.125);
    cv::Mat ConResMat;
    // 卷积运算
    cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
    // 计算梯度的幅度
    cv::Mat graMagMat;
    cv::multiply(ConResMat, ConResMat, graMagMat);
    // 根据梯度幅度及参数设置阈值
    int scaleVal = 4;
    double thresh = scaleVal * cv::mean(graMagMat).val[0];
    cv::Mat resultTempMat = cv::Mat::zeros(
        graMagMat.size(), graMagMat.type());
    float* pDataMag = (float*)graMagMat.data;
    float* pDataRes = (float*)resultTempMat.data;
    const int nRows = ConResMat.rows;
    const int nCols = ConResMat.cols;
    for (int i = 1; i != nRows - 1; ++i) {
        for (int j = 1; j != nCols - 1; ++j) {
            // 计算该点梯度与水平或垂直梯度值大小比较结果
            bool b1 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j - 1]);
            bool b2 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j + 1]);
            bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1) * nCols + j]);
            bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1) * nCols + j]);
            // 判断邻域梯度是否满足大于水平或垂直梯度
            // 并根据自适应阈值参数进行二值化
            pDataRes[i * nCols + j] = 255 * ((pDataMag[i * nCols + j] > thresh) &&
                ((b1 && b2) || (b3 && b4)));
        }
    }
    resultTempMat.convertTo(resultTempMat, CV_8UC1);
    resultImage = resultTempMat.clone();
    return true;
}

// 图像直接卷积实现sobel
bool sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage, uchar threshold)
{
    CV_Assert(srcImage.channels() == 1);
    // 初始化水平核因子
    Mat sobelx = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
    // 初始化垂直核因子
    Mat sobely = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
    resultImage = Mat::zeros(srcImage.rows - 2,
        srcImage.cols - 2, srcImage.type());
    double edgeX = 0;
    double edgeY = 0;
    double graMag = 0;
    for (int k = 1; k < srcImage.rows - 1; ++k) {
        for (int n = 1; n < srcImage.cols - 1; ++n) {
            edgeX = 0;
            edgeY = 0;
            // 遍历计算水平与垂直梯度
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    edgeX += srcImage.at<uchar>(k + i, n + j) *
                        sobelx.at<double>(1 + i, 1 + j);
                    edgeY += srcImage.at<uchar>(k + i, n + j) *
                        sobely.at<double>(1 + i, 1 + j);
                }
            }
            // 计算梯度模长
            graMag = sqrt(pow(edgeY, 2) + pow(edgeX, 2));
            // 二值化
            resultImage.at<uchar>(k - 1, n - 1) =
                ((graMag > threshold) ? 255 : 0);
        }
    }
    return true;
}
// 图像卷积实现sobel 非极大值抑制
bool sobelOptaEdge(const cv::Mat& srcImage, cv::Mat& resultImage, int flag)
{
    CV_Assert(srcImage.channels() == 1);
    // 初始化sobel水平核因子
    cv::Mat sobelX = (cv::Mat_<double>(3, 3) << 1, 0, -1,
        2, 0, -2,
        1, 0, -1);
    // 初始化sebel垂直核因子
    cv::Mat sobelY = (cv::Mat_<double>(3, 3) << 1, 2, 1,
        0, 0, 0,
        -1, -2, -1);
    // 计算水平与垂直卷积
    cv::Mat edgeX, edgeY;
    filter2D(srcImage, edgeX, CV_32F, sobelX);
    filter2D(srcImage, edgeY, CV_32F, sobelY);
    // 根据传入参数确定计算水平或垂直边缘
    int paraX = 0;
    int paraY = 0;
    switch (flag)
    {
    case 0: paraX = 1;
        paraY = 0;
        break;
    case 1:  paraX = 0;
        paraY = 1;
        break;
    case 2:  paraX = 1;
        paraY = 1;
        break;
    default: break;
    }
    edgeX = abs(edgeX);
    edgeY = abs(edgeY);
    cv::Mat graMagMat = paraX * edgeX.mul(edgeX) + paraY * edgeY.mul(edgeY);
    // 计算阈值 
    int scaleVal = 4;
    double thresh = scaleVal * cv::mean(graMagMat).val[0];
    resultImage = cv::Mat::zeros(srcImage.size(), srcImage.type());
    for (int i = 1; i < srcImage.rows - 1; i++)
    {
        float* pDataEdgeX = edgeX.ptr<float>(i);
        float* pDataEdgeY = edgeY.ptr<float>(i);
        float* pDataGraMag = graMagMat.ptr<float>(i);
        // 阈值化和极大值抑制
        for (int j = 1; j < srcImage.cols - 1; j++)
        {
            if (pDataGraMag[j] > thresh && (
                (pDataEdgeX[j] > paraX * pDataEdgeY[j] && pDataGraMag[j] >
                    pDataGraMag[j - 1] && pDataGraMag[j] > pDataGraMag[j + 1]) ||
                (pDataEdgeY[j] > paraY * pDataEdgeX[j] && pDataGraMag[j] >
                    pDataGraMag[j - 1] && pDataGraMag[j] > pDataGraMag[j + 1])))
                resultImage.at<uchar>(i, j) = 255;
        }
    }
    return true;
}
int main()
{
    cv::Mat srcImage = cv::imread("..\\images\\building.jpg", 0);
    if (!srcImage.data)
        return -1;
    cv::imshow("srcImage", srcImage);
    cv::Mat resultImage;
    // 非极大值抑制细化竖直sobel检测
    SobelVerEdge(srcImage, resultImage);
    cv::imshow("resultImage", resultImage);
    cv::Mat resultImage2;
    // 图像直接卷积实现sobel检测
    sobelEdge(srcImage, resultImage2, 100);
    cv::imshow("resultImage2", resultImage2);
    cv::Mat resultImage3;
    int flag = 2;
    // 图像卷积下非极大值抑制
    sobelOptaEdge(srcImage, resultImage3, 2);
    cv::imshow("resultImage3", resultImage3);
    cv::waitKey(0);
    return 0;
}