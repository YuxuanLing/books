// 功能：代码 5-3 图像直接卷积 Sobel 边缘实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 图像直接卷积实现sobel
bool sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage,
     uchar threshold)
{
    CV_Assert(srcImage.channels() == 1);
    // 初始化水平核因子
    Mat sobelx =  (Mat_<double>(3, 3) << 1, 0,
          -1, 2, 0, -2, 1, 0, -1);
    // 初始化垂直核因子
    Mat sobely =  (Mat_<double>(3, 3) << 1, 2, 1,
           0, 0, 0, -1, -2, -1);
    resultImage = Mat::zeros(srcImage.rows - 2, 
        srcImage.cols - 2, srcImage.type());
    double edgeX  = 0;
    double edgeY  = 0;
    double graMag = 0;
    for(int k = 1; k < srcImage.rows - 1; ++k){
        for(int n = 1; n < srcImage.cols - 1; ++n){
            edgeX = 0;
            edgeY = 0;
            // 遍历计算水平与垂直梯度
            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
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
               ((graMag > threshold)? 255 : 0 );
        }
    }
    return true;
}
