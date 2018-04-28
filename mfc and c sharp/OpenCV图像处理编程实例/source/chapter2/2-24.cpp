// 功能：代码 2-24 M.at<float>(i,j)反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat inverseColor1(cv::Mat srcImage)
{
	cv::Mat tempImage = srcImage.clone();
	int row = tempImage.rows;
	int col = tempImage.cols;
	// 对各个像素点遍历进行取反
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
           // 分别对各个通道进行反色处理
		    tempImage.at<cv::Vec3b>(i, j)[0] = 255 – 
                tempImage.at<cv::Vec3b>(i, j)[0];
		    tempImage.at<cv::Vec3b>(i, j)[1] = 255 – 
                tempImage.at<cv::Vec3b>(i, j)[1];
		    tempImage.at<cv::Vec3b>(i, j)[2] = 255 – 
                tempImage.at<cv::Vec3b>(i, j)[2];
		}
	}
	return tempImage;
}
