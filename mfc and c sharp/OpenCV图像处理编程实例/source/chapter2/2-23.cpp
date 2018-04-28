// 功能：代码 2-23 初始化 Hilbert 矩阵
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
Mat H( 100, 100, CV_64F );
for( int i = 0; i < H.rows; i++ )
	for( int j = 0; j < H.cols; j ++ )
		H.at<double>(i,j) = 1. /(i+j +1);
