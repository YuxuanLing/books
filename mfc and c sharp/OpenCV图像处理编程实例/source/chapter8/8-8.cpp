// 功能：代码 8-8 快速区域积分直方图实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 计算单个cell HOG特征
void cacHOGinCell(Mat& HOGCellMat,Rect roi,
	std::vector<Mat>& integrals)
{
	// 实现快速积分HOG
	int x0 = roi.x,y0 = roi.y;
	int x1 = x0 + roi.width；
    int y1 = y0 + roi.height;
	for(int i = 0; i < NBINS; i++)
	{
		// 根据矩阵的上下左右坐标计算
		Mat integral = integrals[i];
		float a = integral.at<double>(y0, x0);
       float b = integral.at<double>(y1, x1);
       float c = integral.at<double>(y0, x1);
       float d = integral.at<double>(y1, x0);
		HOGCellMat.at<float>(0,i) = (a + b) - (c + d);
	}
}
