// 功能：代码 2-28 LUT 查表反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat inverseColor6(cv::Mat srcImage)
{
	int row = srcImage.rows;
	int col = srcImage.cols;
	cv::Mat tempImage = srcImage.clone();
	// 建立LUT 反色table
	uchar LutTable[256];
    for (int i = 0; i < 256; ++i)
       LutTable[i] = 255 - i;
	cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* pData = lookUpTable.data; 
    // 建立映射表
    for( int i = 0; i < 256; ++i)
        pData[i] = LutTable[i];
    // 应用索引表进行查找
    cv::LUT(srcImage, lookUpTable, tempImage);
	return tempImage;
}
