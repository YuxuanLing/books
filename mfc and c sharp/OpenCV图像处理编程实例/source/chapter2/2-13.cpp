// 功能：代码 2-13 getRotationMatrix2D 函数
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
cv::Mat cv::getRotationMatrix2D( Point2f center, double angle, double scale )
{
	// 角度转换
	angle *= CV_PI/180;
	// 计算旋转矩阵角度
	double alpha = cos(angle)*scale;
	double beta = sin(angle)*scale;
	Mat M(2, 3, CV_64F);
	double* m = (double*)M.data;
	// 构建旋转矩阵
	m[0] = alpha;
	m[1] = beta;
	m[2] = (1-alpha)*center.x - beta*center.y;
	m[3] = -beta;
	m[4] = alpha;
	m[5] = beta*center.x + (1-alpha)*center.y;
	return M;
}
