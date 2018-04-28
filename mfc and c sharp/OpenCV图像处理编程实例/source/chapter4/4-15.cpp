// 功能：代码 4-15 图像导向滤波操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <iostream>  
#include "opencv2/core/core.hpp"    
#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/imgproc/imgproc.hpp"      
using namespace std;  
using namespace cv;   
// 导向滤波器 
cv::Mat guidedfilter( Mat &srcImage, Mat &srcClone, int r, double eps )   
{  
  // 转换源图像信息
  srcImage.convertTo(srcImage, CV_64FC1);      
  srcClone.convertTo(srcClone, CV_64FC1);   
  int nRows = srcImage.rows;  
  int nCols = srcImage.cols;   
  cv::Mat boxResult; 
  // 步骤一: 计算均值
  cv::boxFilter(cv::Mat::ones(nRows, nCols, srcImage.type()),
      boxResult, CV_64FC1, cv::Size(r, r));  
  // 生成导向均值mean_I    
  cv::Mat mean_I;  
  cv::boxFilter(srcImage, mean_I, CV_64FC1, cv::Size(r, r));   
  // 生成原始均值mean_p   
  cv::Mat mean_p;  
  cv::boxFilter(srcClone, mean_p, CV_64FC1, cv::Size(r, r)); 
  // 生成互相关均值mean_Ip 
  cv::Mat mean_Ip;  
  cv::boxFilter(srcImage.mul(srcClone), mean_Ip, 
      CV_64FC1, cv::Size(r, r));   
  cv::Mat cov_Ip = mean_Ip - mean_I.mul(mean_p); 
  // 生成自相关均值mean_II 
  cv::Mat mean_II;  
  cv::boxFilter(srcImage.mul(srcImage), mean_II, CV_64FC1, cv::Size(r, r)); 
  // 步骤二：计算相关系数   
  cv::Mat var_I = mean_II - mean_I.mul(mean_I); 
  cv::Mat var_Ip = mean_Ip - mean_I.mul(mean_p); 
  // 步骤三：计算参数系数a，b 
  cv::Mat a = cov_Ip/(var_I + eps);    
  cv::Mat b = mean_p - a.mul(mean_I);  
  // 步骤四：计算系数a，b均值    
  cv::Mat mean_a;  
  cv::boxFilter(a, mean_a, CV_64FC1, cv::Size(r, r));  
  mean_a = mean_a / boxResult;     
  cv::Mat mean_b;  
  cv::boxFilter(b, mean_b, CV_64FC1, cv::Size(r, r));  
  mean_b = mean_b / boxResult;   
  //步骤五：生成输出矩阵 
  cv::Mat resultMat = mean_a.mul(srcImage) + mean_b;  
  return resultMat;  
}    
int main()  
{    
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
    if(srcImage.empty())
          return-1;
    cv::Mat srcGray(srcImage.size(),CV_8UC1);  
    cvtColor(srcImage,srcGray,CV_BGR2GRAY); 
    // 通道分离 
    vector<Mat> vSrcImage, vResultImage;  
    split(srcImage,vSrcImage);
    Mat resultMat;      
    for(int i=0; i < 3; i++)    
    {    
        // 分通道转换成浮点型数据
        Mat tempImage ; 
        vSrcImage[i].convertTo(tempImage, CV_64FC1,1.0/255.0);  
        Mat p = tempImage.clone();
        // 分别进行导向滤波       
        Mat resultImage = guidedfilter(tempImage, p, 4, 0.01);  
        vResultImage.push_back(resultImage);        
    } 
    // 通道结果合并   
    merge(vResultImage,resultMat);  
    cv::imshow("srcImage", srcImage);  
    cv::imshow("resultMat", resultMat);  
    cv::waitKey(0);    
    return 0;  
} 
