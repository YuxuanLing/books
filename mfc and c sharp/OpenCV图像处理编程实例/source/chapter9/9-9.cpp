// 功能：代码 9-9 级联分类器人脸检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>   
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
CascadeClassifier face_cascade, eyes_cascade;
String window_name = "Face Detection";
void detectFaces(Mat frame) {
  std::vector<Rect> faces;
  Mat frame_gray;
  // 灰度变换
  cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
  // 直方图均衡
  equalizeHist(frame_gray, frame_gray);
  // 多尺度人脸检测
  face_cascade.detectMultiScale(frame_gray, faces,
     1.1, 3,0|CASCADE_SCALE_IMAGE, Size(30, 30));
  // 人脸检测结果判定
  for(size_t i = 0; i < faces.size(); i++)
  {
    // 检测到人脸中心
    Point center(faces[i].x + faces[i].width/2, 
      faces[i].y + faces[i].height/2);
    Mat face = frame_gray(faces[i]);
    std::vector<Rect> eyes;
    // 在人脸区域检测人眼
    eyes_cascade.detectMultiScale(face, eyes, 1.1, 2,
				  0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
    if(eyes.size() > 0)
      // 绘制人脸
      ellipse(frame, center, Size(faces[i].width/2, 
        faces[i].height/2),
	      0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
  }
  imshow( window_name, frame );
}
int main() 
{
  // 摄像头读取
  VideoCapture cap(0); 
  Mat frame;
  // 初始化haar级联人脸分类器XML
  face_cascade.load("haarcascade_frontalface_alt.xml"); 
  // 初始化haar级联人眼分类器XML
  eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml"); 

  if (face_cascade.empty() || eye_cascade.empty() 
     || !cap.isOpened())
    return 1;
  
  while(cap.read(frame)) 
  {
    // 人脸检测
    detectFaces(frame); 
    if( waitKey(30) >= 0)    
      break;
  }
  return 0;
}
