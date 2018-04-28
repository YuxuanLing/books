// 功能：代码 4-17 图像 DFT 尺寸转换
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。 // 
  // 图像尺寸转换
  const int nRows = srcImage.rows;
  const int nCols = srcImage.cols;
  std::cout << "srcImage row:" << nRows << std::endl;
  std::cout << "srcImage col:" << nCols << std::endl;
  // 获取DFT尺寸
  int cRows = cv::getOptimalDFTSize(nRows);
  int cCols = cv::getOptimalDFTSize(nCols);
  std::cout << "DFT srcImage row:" << cRows << std::endl;
  std::cout << "DFT srcImage col:" << cCols << std::endl;
  // 图像拷贝，超过边界区域填充为0
  cv::Mat sizeConvMat;
  copyMakeBorder(srcImage, sizeConvMat, 0, cRows -nRows,
     0, cCols-nCols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); 
  cv::imshow("sizeConvMat", sizeConvMat);
