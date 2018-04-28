// 功能：代码 8-9 HOG 特征计算实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 获取HOG直方图
cv::Mat getHog(Point pt,std::vector<Mat> &integrals)
{
    // 判断当前点的位置是否符合条件 
	if( pt.x - R < 0 ||pt.y - R < 0 ||
		pt.x + R >= integrals[0].cols ||
		pt.y + R >= integrals[0].rows )
	{
		return Mat();
	}
	// 直方图
	Mat hist(Size(NBINS*BLOCKSIZE*BLOCKSIZE,1),CV_32F);
	Point tl(0,pt.y-R);
	int c = 0;
	// 遍历块
	for(int i = 0; i < BLOCKSIZE;i++)
	{
		tl.x = pt.x - R;
		for(int j = 0; j < BLOCKSIZE; j++)
		{
			// 获取当前窗口，计算局部直方图
			Rect roi(tl,tl+Point(CELLSIZE,CELLSIZE));
          // 计算当前bins下直方图
			Mat hist_temp = hist.colRange(c,c+NBINS);
			cacHOGinCell(hist_temp,roi,integrals);
           // cell步长尺寸
			tl.x += CELLSIZE;
			c += NBINS;
		}
		tl.y = CELLSIZE;
	}
   // 归一化L2范数
	normalize(hist,hist,1,0,NORM_L2);
	return hist;
}
// 计算HOG特征
std::vector<Mat> cacHOGFeature(cv::Mat srcImage)
{
	Mat grayImage;
	std::vector<Mat> HOGMatVector;
	cv::cvtColor(srcImage,grayImage,CV_RGB2GRAY);
	grayImage.convertTo(grayImage,CV_8UC1);
	// 生成积分图像
	std::vector<Mat> integrals = 
             CalculateIntegralHOG(grayImage);
	Mat image = grayImage.clone();
   // 灰度值缩小
	image *= 0.5;
	// HOG特征矩阵
	cv::Mat HOGBlockMat(Size(NBINS,1),CV_32F);
    // cell遍历
	for(int y = CELLSIZE/2; y < grayImage.rows; y += CELLSIZE)
	{
		for(int x = CELLSIZE / 2; x < grayImage.cols; x += CELLSIZE)
		{
			// 获取当前窗口HOG
			cv::Mat hist = getHog(Point(x,y),integrals);
			if (hist.empty()) 
				continue;
			HOGBlockMat = Scalar(0);
			for(int i = 0; i < NBINS; i++)
			{
				for(int j = 0; j < BLOCKSIZE; j++)
				{
					HOGBlockMat.at<float>(0,i) += 
                       hist.at<float>(0,i+j*NBINS);
				}
			}
			// L2范数归一化
			normalize(HOGBlockMat,HOGBlockMat,1,0,CV_L2);
			HOGMatVector.push_back(HOGBlockMat);	
			Point center(x, y);
			// 绘制HOG特征图
			for (int i = 0; i < NBINS; i++)
			{
              // 角度获取
			    double theta = (i * THETA + 90.0 ) * CV_PI / 180.0;
			    Point rd(CELLSIZE*0.5*cos(theta), 
               CELLSIZE*0.5*sin(theta));
              // 获取绘制中心
			    Point rp = center -  rd;
			    Point lp = center -  -rd;
              // 绘制HOG特征块
			    line(image, rp, lp, Scalar(255*
                  HOGBlockMat.at<float>(0, i), 255, 255));
			}
		}
	}
	imshow("out",image);
	return HOGMatVector;
}
