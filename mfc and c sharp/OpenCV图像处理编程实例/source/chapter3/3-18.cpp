// 功能：代码 3-18 距离变换扫描实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
// 计算欧式距离
float calcEuclideanDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(float((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}
// 计算棋盘距离
int calcChessboardDistance(int x1, int y1, int x2,int y2)
{
	return cv::max(abs(x1-x2), abs(y1-y2));
}
// 计算街区距离
int calcBlockDistance(int x1, int y1, int x2,int y2)
{
	return abs(x1-x2) + abs(y1-y2);  
}
// 距离变换函数实现
void distanceTrans(cv::Mat &srcImage, cv::Mat &resultIamge)
{
    CV_Assert(srcImage.data != NULL);
    cv::Mat srcGray, srcBinary; 
    // 转换成灰度图像
    cv::cvtColor( srcImage, srcGray, CV_RGB2GRAY );
    // 转换成二值图像
    threshold(srcGray, srcBinary, 100, 255,cv::THRESH_BINARY);
    cv::imshow("srcBinary", srcBinary);
    int rows = srcBinary.rows;
    int cols = srcBinary.cols; 
    uchar* pDataOne;
    uchar* pDataTwo;
    float disPara = 0;
    float fDisMin = 0;
    // 第一遍遍历图像用左模板更新像素值
    for(int i = 1 ; i < rows - 1; i++)
    {
    	// 图像指针获取
        pDataOne = srcBinary.ptr<uchar>(i);
    	for(int j = 1; j < cols; j++)
    	{
    		// 分别计算其左模板掩码相关距离
    		//   pL  pL
    		//   pL  p
    		//   pL
            pDataTwo = srcBinary.ptr<uchar>(i-1); 
			disPara  = calcEuclideanDistance(i, j, i-1, j-1);
			fDisMin  = cv::min( (float)pDataOne[j],
			    disPara+pDataTwo[j-1] );
			disPara  = calcEuclideanDistance(i, j, i-1, j);
			fDisMin  = cv::min( fDisMin, 
				disPara+pDataTwo[j] );
			pDataTwo = srcBinary.ptr<uchar>(i);
			disPara  = calcEuclideanDistance(i, j, i, j-1);
			fDisMin  = cv::min( fDisMin, 
				disPara+pDataTwo[j-1] );
			pDataTwo = srcBinary.ptr<uchar>(i+1);
			disPara  = calcEuclideanDistance(i, j, i+1, j-1);
			fDisMin  = cv::min( fDisMin, 
				disPara+pDataTwo[j-1] );
			pDataOne[j] = (uchar)cvRound(fDisMin);
    	}
    }
    // 第二遍遍历图像用右模板更新像素值
    for( int i = rows-2; i > 0; i-- )  
    {  
        pDataOne = srcBinary.ptr<uchar>(i);  
        for( int  j = cols-1; j >= 0; j-- )  
        {     
            // 分别计算其右模板掩码相关距离 
            //   pR  pR
    		//   pR  p
    		//   pR     
            pDataTwo = srcBinary.ptr<uchar>(i+1);  
            disPara  = calcEuclideanDistance(i, j, i+1, j);  
            fDisMin  = cv::min( (float)pDataOne[j],
            	disPara + pDataTwo[j] );  
            disPara = calcEuclideanDistance(i, j, i+1, j+1);  
            fDisMin = cv::min( fDisMin, 
            	disPara + pDataTwo[j+1] );    
            pDataTwo = srcBinary.ptr<uchar>(i);   
            disPara = calcEuclideanDistance(i, j, i, j+1);  
            fDisMin = cv::min( fDisMin,
                disPara + pDataTwo[j+1] );   
            pDataTwo = srcBinary.ptr<uchar>(i-1); 
            disPara = calcEuclideanDistance(i, j, i-1, j+1);  
            fDisMin = cv::min( fDisMin,
                disPara + pDataTwo[j+1] );    
            pDataOne[j] = (uchar)cvRound(fDisMin);  
        }  
    }  
    resultIamge = srcBinary.clone();
}
int main()
{
	cv::Mat srcImage =  cv::imread("..\\images\\sea.jpg");
     if( !srcImage.data ) 
	   return -1;
	cv::Mat resultIamge;
	distanceTrans(srcImage, resultIamge);
	cv::imshow("resultIamge", resultIamge);
	cv::waitKey(0);
	return 0;    
}
