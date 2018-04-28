// 功能：代码 2-25 指针 ptr 反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat inverseColor3(cv::Mat srcImage)
{
	cv::Mat tempImage = srcImage.clone();
    int row = tempImage.rows;
    // 将3通道转换为单通道
    int nStep = tempImage.cols * tempImage.channels();
    for(int i = 0; i < row; i++) 
    {
        // 取源图像的指针
        const uchar* pSrcData = srcImage.ptr<uchar>(i);
        // 将输出数据指针存放输出图像
        uchar* pResultData = tempImage.ptr<uchar>(i);
        for(int j=0; j < nStep; j++)
         {
            pResultData[j]= cv::saturate_cast<uchar>(255 –
                 pSrcData[j]);
         }
     }
	return tempImage;
}
