// 功能：代码 2-15 VideoCapture 读取文件操作
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
    // 定义相关VideoCapture对象
	VideoCapture capture;
    // 读取视频文件
	capture.open("..\\images\\car.avi");
    //  判断视频流读取是否正确
	if(!capture.isOpened())
	{
		std::cout << "fail to open video!" << std::endl;
		return -1;
	}
	// 获取视频相关信息-帧数
	long nTotalFrame = capture.get(CV_CAP_PROP_FRAME_COUNT);
	std:: cout << "nTotalFrame = " << nTotalFrame << std::endl; 
	// 获取视频相关信息-帧像素宽高 
	int  frameHeight= capture.get(CV_CAP_PROP_FRAME_HEIGHT);  
    int  frameWidth  = capture.get(CV_CAP_PROP_FRAME_WIDTH); 
    std::cout << "frameHeight = " << frameHeight << std::endl;
    std::cout << "frameWidth = " << frameWidth << std::endl;
    // 获取视频相关信息-帧率
    double FrameRate = capture.get(CV_CAP_PROP_FPS);  
    std::cout<< "FrameRate = " << FrameRate << std::endl;  
    cv::Mat frameImg;   
    // read方法获取显示帧
    long nCount = 1;
    while (true)
    {
        std::cout << " Current frame: " << nCount << std::endl;
        capture >> frameImg;
        // 判断当前读取文件   
        if (!frameImg.empty())
        {
            imshow("frameImg", frameImg);
        }else
        {
            break;
        }
        // 按下键盘上q键退出
        if (char(waitKey(1)) == 'q')
        {
            break;
        }
        nCount++;
    }
    // 视频释放
    capture.release();  
	return 0;
}
