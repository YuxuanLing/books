// 功能：代码 2-5 IplImage 类型和 CvMat 类型转换为 Mat 类型
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
IplImage *IplImg = cvLoadImage("fruits.jpg");
Mat img(IplImg, true);
