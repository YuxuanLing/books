// 功能：代码 7-1 分水岭图像分割
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 分水岭分割
Mat watershedSegment(Mat & srcImage, int & noOfSegments)
{
	Mat grayMat;
	Mat otsuMat;
	cvtColor(srcImage, grayMat, CV_BGR2GRAY);
	imshow("grayMat", grayMat);
	// 阈值操作
	threshold(grayMat, otsuMat, 0, 255, 
		CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
	imshow("otsuMat", otsuMat);
	// 形态学开操作
	morphologyEx(otsuMat, otsuMat, MORPH_OPEN, 
		Mat::ones(9, 9, CV_8SC1), Point(4, 4), 2);
	imshow("Mor-openMat", otsuMat);
	// 距离变换
	Mat disTranMat(otsuMat.rows, otsuMat.cols, CV_32FC1);
	distanceTransform(otsuMat, disTranMat, CV_DIST_L2, 3);
	// 归一化
	normalize(disTranMat, disTranMat, 0.0, 1, NORM_MINMAX);
	imshow("DisTranMat", disTranMat);
	// 阈值化分割图像
	threshold(disTranMat, disTranMat, 0.1, 1, CV_THRESH_BINARY);
	//归一化统计图像到0-255
	normalize(disTranMat, disTranMat, 0.0, 255.0, NORM_MINMAX);
	disTranMat.convertTo(disTranMat, CV_8UC1);
	imshow("TDisTranMat", disTranMat);
	//计算标记的分割块
	int i, j, compCount = 0;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(disTranMat, contours, hierarchy, 
		CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if (contours.empty())
		return Mat();
	Mat markers(disTranMat.size(), CV_32S);
	markers = Scalar::all(0);
	int idx = 0;
	// 绘制区域块
	for (; idx >= 0; idx = hierarchy[idx][0], compCount++)
		drawContours(markers, contours, idx, 
			Scalar::all(compCount + 1), -1, 8, 
           hierarchy, INT_MAX);
	if (compCount == 0)
		return Mat();
	//计算算法的时间复杂度
	double t = (double)getTickCount();
	watershed(srcImage, markers);
	t = (double)getTickCount() - t;
	printf("execution time = %gms\n", t*1000. / 
          getTickFrequency());
	Mat wshed = displaySegResult(markers, compCount);
	imshow("watershed transform", wshed);
	noOfSegments = compCount;
	return markers;
}
