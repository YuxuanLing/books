// 功能：代码 4-17-21 旋转文本图像矫正
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
int main( )
{
  cv::Mat srcImage = cv::imread("..\\images\\text.jpg",0);
  if( !srcImage.data ) 
	      return 1;
  srcImage = srcImage.rowRange(0,365);
  cv::imshow("srcImage", srcImage);
  // 图像尺寸转换
  int nRows = srcImage.rows;
  int nCols = srcImage.cols;
  std::cout << "srcImage row:" << nRows << std::endl;
  std::cout << "srcImage col:" << nCols << std::endl;
  // 获取DFT尺寸
  int cRows = cv::getOptimalDFTSize(nRows);
  int cCols = cv::getOptimalDFTSize(nCols);
  std::cout << "DFTImage row:" << cRows << std::endl;
  std::cout << "DFTImage col:" << cCols << std::endl;
  // 图像拷贝，超过边界区域填充为0
  cv::Mat sizeConvMat;
  copyMakeBorder(srcImage, sizeConvMat, 0, cRows -nRows, 0,
     cCols-nCols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); 
  cv::imshow("sizeConvMat", sizeConvMat);

  //  通道组建立，
  cv::Mat groupMats[] = {cv::Mat_<float>(sizeConvMat),
       cv::Mat::zeros(sizeConvMat.size(), CV_32F)};
  cv::Mat mergeMat;
  // 通道合并
  merge(groupMats,2,mergeMat);
  // DFT变换
  dft(mergeMat, mergeMat);
  // 分离通道
  split(mergeMat, groupMats);
  // 计算幅值
  magnitude(groupMats[0], groupMats[1], groupMats[0]);
  cv::Mat magnitudeMat = groupMats[0].clone();
  // 归一化操作
  magnitudeMat += Scalar::all(1);
  log(magnitudeMat, magnitudeMat);
  normalize(magnitudeMat, magnitudeMat, 0, 1, CV_MINMAX);
  magnitudeMat.convertTo(magnitudeMat,CV_8UC1,255,0);
  cv::imshow("magnitudeMat", magnitudeMat);

  // 中心平移
  int cx = magnitudeMat.cols/2;
  int cy = magnitudeMat.rows/2; 
  Mat tmp;
  // Top-Left - 为每一个象限创建ROI
  Mat q0(magnitudeMat,Rect(0,0,cx,cy));
  // Top-Right
  Mat q1(magnitudeMat,Rect(cx,0,cx,cy));
  // Bottom-Left
  Mat q2(magnitudeMat,Rect(0,cy,cx,cy));
  // Bottom-Right
  Mat q3(magnitudeMat,Rect(cx,cy,cx,cy)); 
  // 交换象限 (Top-Left with Bottom-Right)    
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  // 交换象限 (Top-Right with Bottom-Left)
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
  cv::imshow("magnitudeMat2", magnitudeMat);

  // 固定阈值二值化处理
  cv::Mat binaryMagnMat;
  threshold(magnitudeMat,binaryMagnMat,132,255,CV_THRESH_BINARY);
  cv::imshow("binaryMagnMat", binaryMagnMat);
  // 霍夫变换
  vector<Vec2f> lines;
  binaryMagnMat.convertTo(binaryMagnMat,CV_8UC1,255,0);
  HoughLines(binaryMagnMat, lines, 1, CV_PI/180, 100, 0, 0 );
  // 检测线个数
  std::cout << "lines.size:"<< lines.size() << std::endl;
  cv::Mat houghMat(binaryMagnMat.size(),CV_8UC3);
  for( size_t i = 0; i < lines.size(); i++ )
  // 绘制检测线
  {
      float rho = lines[i][0], theta = lines[i][1];
      Point pt1, pt2;
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y = cvRound(y0 + 1000*(a));
      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      line( houghMat, pt1, pt2, Scalar(0,255,0), 3, CV_AA);
  }
  cv::imshow("houghMat", houghMat);
  float theta = 0;
  // 检测线角度判断
  for( size_t i = 0; i < lines.size(); i++ )
  {
    float  thetaTemp = lines[i][1]*180/CV_PI;
    if(thetaTemp > 0 && thetaTemp < 90)
    {
        theta = thetaTemp;
        break;
    }
  }
  // 角度转换
  float angelT = nRows* tan(theta/180*CV_PI)/nCols;
  theta = atan(angelT)*180/CV_PI;
  std::cout << "theta:" << theta << std::endl;

// 取图像中心
cv::Point2f centerPoint = cv::Point2f(nCols/2, nRows/2);
double scale = 1;
// 计算旋转矩阵
cv::Mat warpMat = getRotationMatrix2D(centerPoint, theta, scale);
// 仿射变换
cv::Mat resultImage(srcImage.size(), srcImage.type());
cv::warpAffine(srcImage, resultImage, 
  warpMat, resultImage.size());
imshow("resultImage",resultImage);

cv::waitKey(0);
return 0;
}
