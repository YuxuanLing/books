// 功能：代码 9-4 HDR 图像生成
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
void loadExposureSeq(String path, vector<Mat>& images, vector<float>& times)
{
	// 获取当前路径
	path = path + std::string("/");
	// 获取图像相机曝光信息
	ifstream list_file((path + "list.txt").c_str());
	string name;
	float val;
	//  遍历完成图像源信息输入
	while (list_file >> name >> val) {
		Mat img = imread(path + name);
		images.push_back(img);
		times.push_back(1 / val);
	}
	list_file.close();
}
int main(int, char**argv)
{
	vector<Mat> images;
	vector<float> times;
	// 获取图像序列
	string strPath = "../images/HDR";
	loadExposureSeq(strPath, images, times);
	// 创建Calibrate对象
	Mat response;
	Ptr<CalibrateDebevec> calibrate = createCalibrateDebevec();
	// 估计相机响应，校准算法来估计逆CRF所有256像素值
	calibrate->process(images, response, times);
	// 构建HDR图像
	Mat hdr;
	Ptr<MergeDebevec> merge_debevec = createMergeDebevec();
	merge_debevec->process(images, hdr, times, response);
	// 图像映射 利用双边滤波 Gamma变换
	Mat ldr;
	Ptr<TonemapDurand> tonemap = createTonemapDurand(2.2f);
	tonemap->process(hdr, ldr);
	// 执行曝光融合
	Mat fusion;
	Ptr<MergeMertens> merge_mertens = createMergeMertens();
	merge_mertens->process(images, fusion);
	cv::imshow("hdr", hdr);
	// 结果输出
	imwrite("fusion.png", fusion * 255);
	imwrite("ldr.png", ldr * 255);
	imwrite("hdr.hdr", hdr);
	cv::waitKey(0);
	return 0;
}

