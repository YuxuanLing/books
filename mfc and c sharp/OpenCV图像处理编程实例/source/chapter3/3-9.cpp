// 功能：代码 3-9 自定义直方图实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include <opencv2/opencv.hpp>
int main()
{
	// 图像获取及判断
    cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
    if( !srcImage.data ) 
      return 1;
    cv::imshow("srcImage",srcImage);
    // 灰度转换  
    cv::Mat srcGray;
    cv::cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    // 初始化直方图计算参数
    const int channels[1]={0};
    const int histSize[1]={256};
    // 设定区间[0 60],[61 120],[121 160],[161 220],[221 255]
    float hranges[6]={0, 60, 120, 160, 220, 255};
    const float* ranges[1] = {hranges};
    cv::MatND hist;
    // 计算直方图
    cv::calcHist( &srcGray, 1, 
    	          channels, cv::Mat(),
    	          hist, 1, histSize, 
    	          ranges );
    // 求直方图中最大值
    double maxHist=0;
    cv::minMaxLoc(hist, 0, &maxHist, 0 ,0);
    // 设置直方图绘图参数
    int hist_Size = hist.rows;
    cv::Mat histImg(hist_Size, hist_Size, 
                      CV_8U, cv::Scalar(255));
    // 直方图绘制
    for(int h = 0; h < hist_Size; h++)
    {
        float binVal = hist.at<float>(h);
        //归一化 根据最大值计算变换范围 
        int intensity = static_cast<int>(binVal * 
            hist_Size / maxHist);
        // 绘图直方图信息
        cv::line(histImg, cv::Point(h, hist_Size), 
        	     cv::Point(h, hist_Size - intensity),
        	     cv::Scalar::all(0));
    }
    cv::imshow("histImg", histImg);
    cv::waitKey(0);
    return 0;
}
