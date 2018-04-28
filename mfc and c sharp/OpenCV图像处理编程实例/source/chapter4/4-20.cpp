// 功能：代码 4-20 倾斜角检测
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。  // 
  // 固定阈值二值化处理
  cv::Mat binaryMagnMat;
  threshold(magnitudeMat,binaryMagnMat,
     132,255,CV_THRESH_BINARY);
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
      // 坐标变换生成线表达式
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y = cvRound(y0 + 1000*(a));
      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      line( houghMat, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
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
