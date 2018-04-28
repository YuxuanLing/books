// 功能：代码 4-18 图像 DFT 变换
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
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
  // 归一化操作幅值加1
  magnitudeMat += Scalar::all(1);
  // 对数变换
  log(magnitudeMat, magnitudeMat);
  // 归一化
  normalize(magnitudeMat, magnitudeMat, 0, 1, CV_MINMAX);
  // 图像类型转换
  magnitudeMat.convertTo(magnitudeMat,CV_8UC1,255,0);
  cv::imshow("magnitudeMat", magnitudeMat);

