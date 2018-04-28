// 功能：代码 2-26 MatIterator_迭代器反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat inverseColor4(cv::Mat srcImage)
{
	cv::Mat tempImage = srcImage.clone();
	// 初始化源图像迭代器
	cv::MatConstIterator_<cv::Vec3b> srcIterStart  = 
         srcImage.begin<cv::Vec3b>();
	cv::MatConstIterator_<cv::Vec3b> srcIterEnd = 
         srcImage.end<cv::Vec3b>();
    // 初始化输出图像迭代器
	cv::MatIterator_<cv::Vec3b> resIterStart = 
            tempImage.begin<cv::Vec3b>();
	cv::MatIterator_<cv::Vec3b> resIterEnd = 
            tempImage.end<cv::Vec3b>();
	// 遍历图像反色处理
	while( srcIterStart != srcIterEnd )
	{
		 (*resIterStart)[0] = 255 - (*srcIterStart)[0];
		 (*resIterStart)[1] = 255 - (*srcIterStart)[1];
		 (*resIterStart)[2] = 255 - (*srcIterStart)[2];
		 // 迭代器递增
		 srcIterStart++;
		 resIterStart++;
	}
	return tempImage;
}
