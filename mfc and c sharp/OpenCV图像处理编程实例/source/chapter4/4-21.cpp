// 功能：代码 4-21 仿射变换矫正
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// // 
// 取图像中心
cv::Point2f centerPoint = cv::Point2f(nCols/2, nRows/2);
double scale = 1;
// 计算旋转矩阵
cv::Mat warpMat = getRotationMatrix2D(centerPoint, 
     theta, scale);
// 仿射变换
cv::Mat resultImage(srcImage.size(), srcImage.type());
cv::warpAffine(srcImage, resultImage, 
  warpMat, resultImage.size());
imshow("resultImage",resultImage);
