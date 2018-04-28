// 功能：代码 4-12 中值滤波实现 
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <cmath>
using namespace cv;  
using namespace std;
// 中值滤波实现   
void myMedianBlur(Mat& src, Mat& dst,const int kSize)  
{    
  // 
  dst = src.clone(); 
  std::vector<uchar> vList;
  const int nPix = (kSize*2+1) * (kSize*2+1);
  // 图像源遍历
  for( int i = kSize; i < dst.rows-kSize; ++i )  
  {  
      for ( int j = kSize; j < dst.cols-kSize; ++j )  
      {   
          //  滑窗进行搜索遍历
          for( int pi = i-kSize; pi <= i+kSize; pi++ )  
          {  
              for( int pj = j-kSize; pj <= j+kSize; pj++ )  
              {
                // 将窗内的元素放到向量内  
                vList.push_back(src.at<uchar>(pi,pj));
              }  
          } 
          // 窗内元素排序
          sort(vList.begin(),vList.end());
          // 提取中间元素作为当前元素
          dst.at<uchar>(i,j) = vList[nPix/2]; 
          vList.clear();
      }
  }  
}
int main( int argc, char** argv )  
{  
  cv::Mat image = imread("..\\images\\flower3.jpg",0);  
  if(!image.data)   
      return -1;  
  cv::imshow("image", image);  
  cv::Mat dst;  
  myMedianBlur(image, dst, 3);    
  cv::imshow("out_image", dst); 
  cv::waitKey(0);  
  return 0;  
}  
  
