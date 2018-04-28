// 功能：代码 3-26 最大熵阈值分割
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace std;
using namespace cv;
// 计算当前的位置的能量熵
float caculateCurrentEntropy(cv::Mat hist, int threshold)
{
    float BackgroundSum = 0, targetSum = 0;
	const float* pDataHist = (float*) hist.ptr<float>(0);
	for (int i = 0; i < 256; i++)
	{
		// 累计背景值
		if( i < threshold )
		{
			BackgroundSum += pDataHist[i];
		}else // 累计目标值
	    {
            targetSum += pDataHist[i];
	    }
	}
	//std::cout << BackgroundSum << " "<< targetSum << std::endl;
    float BackgroundEntropy = 0, targetEntropy = 0;
	for (int i = 0; i < 256; i++)
	{
		// 计算背景熵
		if( i < threshold )
        {
        	if( pDataHist[i] == 0 )
				continue;
			float ratio1 = pDataHist[i] / BackgroundSum;
			// 计算当前能量熵
			BackgroundEntropy += - ratio1 * logf(ratio1); 
        }else // 计算目标熵
        {
         	if( pDataHist[i] == 0 )
			 	continue;
			float ratio2 = pDataHist[i] / targetSum;
			targetEntropy += -ratio2 * logf(ratio2); 
        }
	}
	return ( targetEntropy + BackgroundEntropy );
}
// 寻找最大熵阈值并分割
cv::Mat maxEntropySegMentation(cv::Mat inputImage)
{
    // 初始化直方图参数
    const int channels[1]={0};
    const int histSize[1]={256};
	float pranges[2]={0, 256};
	const float* ranges[1]={pranges};
	cv::MatND hist;
	// 计算直方图
	cv::calcHist(&inputImage,1,channels,
		cv::Mat(),hist,1,histSize,ranges);
	float maxentropy = 0;
	int    max_index  = 0;
	cv::Mat result; 
	// 遍历得到最大熵阈值分割的最佳阈值
	for(int i = 0; i < 256; i++)	
	{
		float cur_entropy = 
			caculateCurrentEntropy(hist,i);
		// 计算当前最大值的位置
		if(cur_entropy > maxentropy)
		{
			maxentropy = cur_entropy;
			max_index = i;
		}
	}
	//  二值化分割
	threshold(inputImage, result, max_index, 255,
           CV_THRESH_BINARY);
	return result;
}
int main()
{
	cv::Mat srcImage=cv::imread("..\\images\\hand1.jpg");
	if(!srcImage.data)
		return 0;
	cv::Mat grayImage;
	cv::cvtColor(srcImage, grayImage, CV_BGR2GRAY); 
    // 最大熵阈值分割实现    
    cv::Mat result = maxEntropySegMentation(grayImage);
    cv::imshow("grayImage", grayImage);
    cv::imshow("result" , result);
    cv::waitKey(0);
	return 0;
}
