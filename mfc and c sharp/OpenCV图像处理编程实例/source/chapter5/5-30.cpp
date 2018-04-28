// 功能：代码 5-30 细化 Sobel 边缘提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 提取竖直的sobel边缘
bool SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
	CV_Assert(srcImage.channels() == 1);
	srcImage.convertTo(srcImage, CV_32FC1);
	// 水平方向的 Sobel 算子
	cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
		-0.25, 0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat ConResMat;
	// 卷积运算
	cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
	// 计算梯度的幅度
	cv::Mat graMagMat;
	cv::multiply(ConResMat, ConResMat, graMagMat);
	// 根据梯度幅度及参数设置阈值
	int scaleVal = 4;
	double thresh = scaleVal * cv::mean(graMagMat).val[0];
	cv::Mat resultTempMat = cv::Mat::zeros(
		graMagMat.size(), graMagMat.type());
	float* pDataMag = (float*)graMagMat.data;
	float* pDataRes = (float*)resultTempMat.data;
	const int nRows = ConResMat.rows;
	const int nCols = ConResMat.cols;
	for (int i = 1; i != nRows - 1; ++i) {
		for (int j = 1; j != nCols - 1; ++j) {
			// 计算该点梯度与水平或垂直梯度值大小比较结果
			bool b1 = (pDataMag[i * nCols + j] > pDataMag[i *
				nCols + j - 1]);
			bool b2 = (pDataMag[i * nCols + j] > pDataMag[i *
				nCols + j + 1]);
			bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1)
				* nCols + j]);
			bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1)
				* nCols + j]);
			// 判断邻域梯度是否满足大于水平或垂直梯度
			// 并根据自适应阈值参数进行二值化
			pDataRes[i * nCols + j] = 255 * ((pDataMag[i *
				nCols + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resultTempMat.convertTo(resultTempMat, CV_8UC1);
	resultImage = resultTempMat.clone();
	return true;
}