// 功能：代码 8-10 经典 LBP 特征
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
template <typename _Tp> static
	void olbp_(InputArray _src, OutputArray _dst) 
{
		// 得到矩阵信息
		Mat src = _src.getMat();
		// 输出结果矩阵
		_dst.create(src.rows-2, src.cols-2, CV_8UC1);
		Mat dst = _dst.getMat();
		// 初始化矩阵
		dst.setTo(0);
		// 遍历计算局部特征
		for(int i=1;i<src.rows-1;i++) {
			for(int j=1;j<src.cols-1;j++) {
              // 获取当前图像处理的中心点
				_Tp center = src.at<_Tp>(i,j);
				unsigned char code = 0;
              // 比较图像编码形成
				code |= (src.at<_Tp>(i-1,j-1) >= center) << 7;
				code |= (src.at<_Tp>(i-1,j) >= center) << 6;
				code |= (src.at<_Tp>(i-1,j+1) >= center) << 5;
				code |= (src.at<_Tp>(i,j+1) >= center) << 4;
				code |= (src.at<_Tp>(i+1,j+1) >= center) << 3;
				code |= (src.at<_Tp>(i+1,j) >= center) << 2;
				code |= (src.at<_Tp>(i+1,j-1) >= center) << 1;
				code |= (src.at<_Tp>(i,j-1) >= center) << 0;
				dst.at<unsigned char>(i-1,j-1) = code;
			}
}
