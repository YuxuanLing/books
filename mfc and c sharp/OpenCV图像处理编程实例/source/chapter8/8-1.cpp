// 功能：代码 8-1 特征尺度变换实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 特征点尺寸变换
void CreateScaleSpace(cv::Mat srcImage,
    std::vector< std::vector<Mat> > &ScaleSpace,
    std::vector< std::vector<Mat> > &DoG)
{
    cv::Size ksize(5, 5);
    double sigma; Mat srcBlurMat, up, down;
    // 高斯平滑
    GaussianBlur(srcImage, srcBlurMat, ksize, 0.5);
    // 金字塔
    pyrUp(srcBlurMat, up);
    up.copyTo(ScaleSpace[0][0]);
    // 高斯平滑
    GaussianBlur(ScaleSpace[0][0], ScaleSpace[0][0], ksize, 1.0);
    // 图像遍历
    for (int i = 0; i < 4; i++)
    {
        // 平滑因子
        double sigma = 1.4142135;  
        for (int j = 0; j < 5+2; j++)
        {
            sigma = sigma * pow(2.0,j/2.0) ;
            // 对下一尺度进行进行高斯操作
            GaussianBlur(ScaleSpace[i][j], 
                ScaleSpace[i][j+1], ksize, sigma);
            // 多尺度空间生成
            DoG[i][j] = ScaleSpace[i][j] - ScaleSpace[i][j+1];
            // cout<<"iave:"<<i<<" Scale:"<<j<<"size:"<< 
            // ScaleSpace[i][j].rows<<"x"<<ScaleSpace[i][j].cols<<endl;
        }
        // 如果不能完成，继续进行金字塔操作
        if (i < 3)
        {
            pyrDown(ScaleSpace[i][0], down);
            down.copyTo(ScaleSpace[i+1][0]);
        }
    }
}
