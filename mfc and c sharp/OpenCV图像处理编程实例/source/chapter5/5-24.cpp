// 功能：代码 5-24 点多边形测试
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
vector<vector<Point> > closed_contours;
vector<Vec4i> heirarchy;
cv::Mat contoursAllMat;
// 函数多边形近似
vector<vector<Point> > cacContoursClosed(
	vector<vector<Point> > contours)
{
	vector<vector<Point> > vContours;
	vContours.resize(contours.size());
	for (int i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], vContours[i], 0.1, true);
	return vContours;
}
// 最小点集边界轮廓
int cacContoursSmall(Point p, vector<vector<Point> > contours,
	 vector<Vec4i> heirarchy)
{
	int idx = 0, prev_idx = -1;
	while (idx >= 0)
	{
		vector<Point> c = contours[idx];
		// 点多边形测试
		double d = pointPolygonTest(c, p, false);
		// 判断点集是否在多边形内
		if (d > 0)
		{
			prev_idx = idx;
			idx = heirarchy[idx][2];
		}
		// 不在内，将继续遍历下一
		else
			idx = heirarchy[idx][0];
	}
	return prev_idx;
}
// 鼠标点击动作响应
void on_mouse(int event, int x, int y, int, void *) 
{
	// 事件左键确认
	if (event != EVENT_LBUTTONDOWN)
		return;
	Point p(x, y);
	// 寻找最小封闭外界轮廓
	int idxContour = cacContoursSmall(p, closed_contours, 
		heirarchy);
	// 如果不存在轮廓，显示将返回
	if (idxContour < 0)
	{
		imshow("Contours", contoursAllMat);
		return;
	}
	// 绘图所有最小的外界轮廓
	vector<vector<Point> > viewContour;
	viewContour.push_back(closed_contours[idxContour]);
	if (!viewContour.empty()) 
	{
		Mat result = contoursAllMat.clone();
		// 绘制所有轮廓
		drawContours(result, viewContour, -1,
		  Scalar(0, 0, 255), 3);
		imshow("Contours", result);
	}
}
int main()
{
	cv::Mat srcImage = imread("..\\images\\circle.jpg");
	if (!srcImage.data)
		return -1;
	cv:imshow("srcImage", srcImage);
	contoursAllMat = srcImage.clone();
	cv::Mat srcGray, edges;
	// 边缘检测
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	Canny(srcGray, edges, 50, 100);
	// 寻找外界轮廓
	vector<vector<Point> > contours;
	findContours(edges, contours, heirarchy, 
		CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	// 确认检测轮廓点的封闭性
	closed_contours = cacContoursClosed(contours);
	// 绘制所有轮廓
	drawContours(srcImage, closed_contours, -1, 
		Scalar(0, 255, 0));
	imshow("Contours", srcImage);
	// 鼠标回调事件
	setMouseCallback("Contours", on_mouse);
	while (char(waitKey(1)) != 'q') {}
	return 0;
}
