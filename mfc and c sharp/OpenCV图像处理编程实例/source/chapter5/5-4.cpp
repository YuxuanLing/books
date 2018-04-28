// 功能：5-4 图像卷积下非极大值抑制 Sobel 的实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 图像卷积实现sobel 非极大值抑制
bool sobelOptaEdge(const cv::Mat& srcImage, 
      cv::Mat& resultImage, int flag)
{
     CV_Assert(srcImage.channels() == 1);
     // 初始化sobel水平核因子
     cv::Mat sobelX =  (cv::Mat_<double>(3, 3) << 1, 0, -1,
         2, 0, -2, 
         1, 0, -1);
     // 初始化sebel垂直核因子
     cv::Mat sobelY =  (cv::Mat_<double>(3, 3) << 1, 2, 1, 
         0, 0, 0, 
         -1, -2, -1);
     // 计算水平与垂直卷积
     cv::Mat edgeX, edgeY;
     filter2D(srcImage, edgeX, CV_32F, sobelX);
     filter2D(srcImage, edgeY, CV_32F, sobelY);  
     // 根据传入参数确定计算水平或垂直边缘
     int paraX = 0;
     int paraY = 0;
     switch(flag)
     {
        case 0 : paraX = 1;
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
     cv::Mat graMagMat = paraX * edgeX.mul(edgeX) +
          paraY * edgeY.mul(edgeY);
     // 计算阈值 
    int scaleVal = 4;
    double thresh = scaleVal * cv::mean(graMagMat).val[0];
    resultImage = cv::Mat::zeros(srcImage.size(),
         srcImage.type());
    for(int i = 1; i < srcImage.rows - 1; i++)
    {
         float* pDataEdgeX  = edgeX.ptr<float>(i);
         float* pDataEdgeY  = edgeY.ptr<float>(i);
         float* pDataGraMag = graMagMat.ptr<float>(i);
         // 阈值化和极大值抑制
         for(int j = 1; j < srcImage.cols-1; j++)
         {
             if( pDataGraMag[j] > thresh && (
                 (pDataEdgeX[j] > paraX * pDataEdgeY[j] && 
                  pDataGraMag[j] >
                  pDataGraMag[j-1] && pDataGraMag[j] > 
                  pDataGraMag[j+1]) ||
                 (pDataEdgeY[j] > paraY * pDataEdgeX[j] && 
                 pDataGraMag[j] >
                  pDataGraMag[j-1] && pDataGraMag[j] > 
                  pDataGraMag[j+1]) ) )
                 resultImage.at<uchar>(i, j) = 255;
         }
     }
     return true;
}
