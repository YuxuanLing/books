// 功能：代码 8-7 积分图实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 计算积分图
std::vector<Mat> CalculateIntegralHOG(Mat& srcMat)
{
	// Sobel边缘检测
	Mat sobelMatX,sobelMatY;
	Sobel(srcMat,sobelMatX,CV_32F,1,0); 
	Sobel(srcMat,sobelMatY,CV_32F,0,1);
	std::vector<Mat> bins(NBINS);
	for(int i = 0; i < NBINS; i++)
	{
		bins[i] = Mat::zeros(srcMat.size(),CV_32F);
	}
	Mat magnMat,angleMat;
	// 坐标转换
	cartToPolar(sobelMatX,sobelMatY,magnMat,angleMat,true);
	// 角度变换
	add(angleMat,Scalar(180),angleMat,angleMat<0);
	add(angleMat,Scalar(-180),angleMat,angleMat>=180);
	angleMat /= THETA;
	for(int y = 0; y < srcMat.rows;y++)
	{
		for(int x = 0; x < srcMat.cols;x++)
		{
			// 计算bins下幅值
			int ind = angleMat.at<float>(y,x);
			bins[ind].at<float>(y,x) += 
			magnMat.at<float>(y,x);
		}
	}
	// 生成积分图像
	std::vector<Mat> integrals(NBINS);
	for(int i = 0; i < NBINS; i++)
	{
		integral(bins[i],integrals[i]);
	}
	return integrals;
}
