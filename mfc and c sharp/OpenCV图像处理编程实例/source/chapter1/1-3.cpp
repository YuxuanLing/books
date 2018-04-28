// 功能：代码1-3  测试OpenCV示例1
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 头文件
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main( )
{
	// 读取源图像并转化为灰度图像
	cv::Mat srcImage = cv::imread("..\\images\\flower.jpg");
	// 判断文件是否读入正确
	if( !srcImage.data ) 
		return 1;
	// 图像显示
	cv::imshow("srcImage", srcImage);
	// 等待键盘键入
	cv::waitKey(0);
	return 0;
}
