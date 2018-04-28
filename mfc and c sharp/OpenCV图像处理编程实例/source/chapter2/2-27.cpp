// 功能：代码 2-27 isContinuous 反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat inverseColor5(cv::Mat srcImage)
{
	int row = srcImage.rows;
	int col = srcImage.cols;
	cv::Mat tempImage = srcImage.clone();
	// 判断是否是连续图像，即是否有像素填充
	if( srcImage.isContinuous() && tempImage.isContinuous() )
	{
		row = 1;
       // 按照行展开
		col = col * srcImage.rows * srcImage.channels();
	}
	// 遍历图像的每个像素
	for(int i = 0; i < row; i++)
	{
       // 设定图像数据源指针及输出图像数据指针
		const uchar* pSrcData = srcImage.ptr<uchar>(i);
		uchar* pResultData = tempImage.ptr<uchar>(i);
		for(int j = 0; j < col; j++)
		{
		    *pResultData++ = 255 - *pSrcData++;
		}
	}
	return tempImage;
}
