// 功能：代码 4-19 频域中心移动
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。  // 
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
