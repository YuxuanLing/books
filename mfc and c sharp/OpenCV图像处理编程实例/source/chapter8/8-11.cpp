// 功能：代码 8-11 圆形 LBP 特征
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
template <typename _Tp> static
	inline void elbp_(InputArray _src, OutputArray _dst,
		int radius, int neighbors) {
		// 得到数据矩阵
		Mat src = _src.getMat();
		// 输出矩阵
		_dst.create(src.rows-2*radius, 
           src.cols-2*radius, CV_32SC1);
		Mat dst = _dst.getMat();
		// 初始化
		dst.setTo(0);
		for(int n=0; n<neighbors; n++) {
			// 相同点
			float x = static_cast<float>(-radius * sin(2.0
				*CV_PI*n/static_cast<float>(neighbors)));
			float y = static_cast<float>(radius * cos(2.0
				*CV_PI*n/static_cast<float>(neighbors)));
			// 相关索引
			int fx = static_cast<int>(floor(x));
			int fy = static_cast<int>(floor(y));
			int cx = static_cast<int>(ceil(x));
			int cy = static_cast<int>(ceil(y));
			// 小数部分
			float ty = y - fy;
			float tx = x - fx;
			// 集插值权重
			float w1 = (1 - tx) * (1 - ty);
			float w2 =      tx  * (1 - ty);
			float w3 = (1 - tx) *      ty;
			float w4 =      tx  *      ty;
			// 遍历数据
			for(int i=radius; i < src.rows-radius;i++) {
				for(int j=radius;j < src.cols-radius;j++) {
					// 插值计算值
					float t = static_cast<float>(
                      w1*src.at<_Tp>(i+fy,j+fx) 
						+ w2*src.at<_Tp>(i+fy,j+cx) + 
                     w3*src.at<_Tp>(i+cy,j+fx)
						+ w4*src.at<_Tp>(i+cy,j+cx));
					// 限定浮点精度，生成输出图像
					dst.at<int>(i-radius,j-radius) += ((t > 
                   src.at<_Tp>(i,j)) || 
                   (std::abs(t-src.at<_Tp>(i,j)) < 
                   std::numeric_limits<float>::epsilon())) << n;
				}
			}
		}
}
