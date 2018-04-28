// 功能：代码 2-30 单窗口显示多幅图像
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
void showManyImages( const std::vector<cv::Mat> &srcImages, 
	cv::Size imgSize )
{
	int nNumImages = srcImages.size();
	cv::Size nSizeWindows;
	if(nNumImages > 12)
	{
		    std::cout << " Not more than 12 images!" << std::endl;
			return ;
	}
	// 根据图片序列数量来确定分割小窗口形态
	switch(nNumImages)
	{
		case 1: nSizeWindows = cv::Size(1,1);break;
		case 2: nSizeWindows = cv::Size(2,1);break;
		case 3: 
		case 4: nSizeWindows = cv::Size(2,2);break;
		case 5: 
		case 6: nSizeWindows = cv::Size(3,2);break;
		case 7: 
		case 8: nSizeWindows = cv::Size(4,2);break;
		case 9: nSizeWindows = cv::Size(3,3);break;
		default:nSizeWindows = cv::Size(4,3);break;
	}
	// 设置小图像尺寸，间隙，边界
	int nShowImageSize  = 200;
	int nSplitLineSize  = 15;
	int nAroundLineSize = 50;
	// 创建输出图像，图像大小根据输入源确定
	const int imagesHeight = nShowImageSize * nSizeWindows.width+ 
        nAroundLineSize + (nSizeWindows.width - 1) *
        nSplitLineSize;
	const int imagesWidth = nShowImageSize*nSizeWindows.height + 
        nAroundLineSize + (nSizeWindows.height - 1) * 
        nSplitLineSize;
	std::cout << imagesWidth << " " << imagesHeight << std::endl;
	cv::Mat showWindowImages(imagesWidth, imagesHeight, 
         CV_8UC3,cv::Scalar(0,0,0));
	// 提取对应小图像的左上角坐标X，Y
	int posX = (showWindowImages.cols-(nShowImageSize*
		nSizeWindows.width+(nSizeWindows.width-1)*
		nSplitLineSize))/2;
	int posY = (showWindowImages.rows-(nShowImageSize*
		nSizeWindows.height+(nSizeWindows.height-1)*
		nSplitLineSize))/2;
	std::cout << posX << " " << posY  << std::endl;
	int tempPosX = posX;
	int tempPosY = posY;
	// 将每一小幅图像整合大图像
	for(int i=0; i < nNumImages; i++)
	{
		// 小图像坐标转换
		if(( i % nSizeWindows.width == 0) && ( tempPosX != posX ))
		{
			tempPosX = posX;
			tempPosY  += (nSplitLineSize + nShowImageSize);
		}
		// 利用Rect区域将小图像置于大图像相应区域
		cv::Mat tempImage = showWindowImages(cv::Rect(tempPosX, 
               tempPosY , nShowImageSize, nShowImageSize));
        // 利用resize函数实现图像缩放
		resize(srcImages[i], tempImage,
               cv::Size( nShowImageSize ,   nShowImageSize));
		tempPosX += (nSplitLineSize + nShowImageSize);
	}
	cv::imshow("showWindowImages", showWindowImages);
}
int main()
{
	// 图像源输入
	std::vector<cv::Mat> srcImages(9);
	srcImages[0] = cv::imread("..\\images\\flower.jpg");
	srcImages[1] = cv::imread("..\\images\\flower.jpg");
	srcImages[2] = cv::imread("..\\images\\flower.jpg");
	srcImages[3] = cv::imread("..\\images\\flower2.jpg");
	srcImages[4] = cv::imread("..\\images\\flower2.jpg");
	srcImages[5] = cv::imread("..\\images\\flower2.jpg");
	srcImages[6] = cv::imread("..\\images\\flower3.jpg");
	srcImages[7] = cv::imread("..\\images\\flower3.jpg");
	srcImages[8] = cv::imread("..\\images\\flower3.jpg");
	// 判断当前vector读入的正确性
	for(int i = 0; i < srcImages.size(); i++)
	{
		if (!srcImages[i].data)
		{   
			std::cout << "read error!" << std::endl;
       		return -1;
       	}
	}
	// 调用单窗口显示图像
	showManyImages(srcImages, cv::Size(512, 400));
	cv::waitKey(0);
	return 0;
}
