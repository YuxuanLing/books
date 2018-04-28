// 功能：代码 // 5-11 计算梯度幅值与方向
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 使用sobel计算相应的梯度幅值及方向
Mat magX = Mat(src.rows, src.cols, CV_32F);
Mat magY = Mat(src.rows, src.cols, CV_32F);
Sobel(image, magX, CV_32F, 1, 0, 3);
Sobel(image, magY, CV_32F, 0, 1, 3);  
// 计算斜率
Mat slopes = Mat(image.rows, image.cols, CV_32F); 
divide(magY, magX, slopes);
// 计算每个点的梯度
Mat sum = Mat(image.rows, image.cols, CV_64F);
Mat prodX = Mat(image.rows, image.cols, CV_64F);
Mat prodY = Mat(image.rows, image.cols, CV_64F);
multiply(magX, magX, prodX);
multiply(magY, magY, prodY);
sum = prodX + prodY;
sqrt(sum, sum);