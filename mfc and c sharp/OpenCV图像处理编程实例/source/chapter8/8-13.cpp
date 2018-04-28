// 功能：代码 8-13 Haar 特征提取
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 计算Haar特征
double HaarExtract(double const ** image ,
	 int type_, cv::Rect roi)
{
    double value;
    double wh1, wh2;
    double bk1, bk2;
    int x = roi.x;
    int y = roi.y;
    int width = roi.width;
    int height = roi.height;
    switch (type_)
    {
    // Haar水平边缘
    case 0:	// HaarHEdge
	wh1 = calcIntegral(image, x, y, width, height);
	bk1 = calcIntegral(image, x + width, y, width, height);
	value = (wh1 - bk1) / static_cast<double>(width * height);
	break; 
	// Haar竖直边缘 
    case 1:	
	wh1 = calcIntegral(image, x, y, width, height);
	bk1 = calcIntegral(image, x, y + height, width, height);
	value = (wh1 - bk1) / static_cast<double>(width * height);
	break; 
	// Haar水平线型
    case 2:	
	wh1 = calcIntegral(image, x, y, width * 3, height);
	bk1 = calcIntegral(image, x + width, y, width, height);
	value = (wh1 - 3.0 * bk1) / 
		static_cast<double>(2 * width * height);
	break;
	// Haar垂直线型 
    case 3:	
	wh1 = calcIntegral(image, x, y, width, height * 3);
	bk1 = calcIntegral(image, x, y + height, width, height);
	value = (wh1 - 3.0 * bk1) / 
		static_cast<double>(2 * width * height);
	break;
    // Haar棋盘型
    case 4:	
	wh1 = calcIntegral(image, x, y, width * 2, height * 2);
	bk1 = calcIntegral(image, x + width, y, width, height);
	bk2 = calcIntegral(image, x, y + height, width, height);
	value = (wh1 - 2.0 * (bk1 + bk2)) / 
		static_cast<double>(2 * width * height);
	break;
    // Haar中心包围型
    case 5:	
	wh1 = calcIntegral(image, x, y, width * 3, height * 3);
	bk1 = calcIntegral(image, x + width,
		 y + height, width, height);
	value = (wh1 - 9.0 * bk1) / 
		static_cast<double>(8 * width * height);
	break;
    } 
    return value;
}
// 计算单窗口的积分图
double calcIntegral(double const  ** image, 
	int x, int y, int width, int height)
{
    double term_1 = image[y - 1 + height][x - 1 + width];
    double term_2 = image[y - 1][x - 1];
    double term_3 = image[y - 1 + height][x - 1];
    double term_4 = image[y - 1][x - 1 + width];
    return (term_1 + term_2) - (term_3 + term_4);
}
