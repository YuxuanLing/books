// 功能：代码  5-31 车牌疑似区域点提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
	// hsv 限定范围元素提取
	cv::Mat bw_blue = ((img_h>0.45) &
		(img_h<0.75) &
		(img_s>0.15) &
		(img_v>0.25));
	int height = bw_blue.rows;
	int width = bw_blue.cols;
	cv::Mat bw_blue_edge = cv::Mat::zeros(bw_blue.size(), bw_blue.type());
	cv::imshow("bw_blue", bw_blue);
	cv::waitKey(0);
	// 车牌疑似区域提取
	for (int k = 1; k != height - 2; ++k)
	{
		for (int l = 1; l != width - 2; ++l)
		{
			cv::Rect rct;
			rct.x = l - 1;
			rct.y = k - 1;
			rct.height = 3;
			rct.width = 3;
			if ((sobelMat.at<uchar>(k, l) == 255) && (cv::countNonZero(bw_blue(rct)) >= 1))
				bw_blue_edge.at<uchar>(k, l) = 255;
		}
	}
	