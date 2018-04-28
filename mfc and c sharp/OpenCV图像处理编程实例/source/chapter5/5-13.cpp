// 功能：代码 5-13 滞后阈值边缘连接
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 边缘连接
void followEdges(int x, int y, Mat &magnitude, int tUpper,
 int tLower, Mat &edges) 
{   
    edges.at<float>(y, x) = 255;   
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // 边界限制
            if((i != 0) && (j != 0) && (x + i >= 0) &&
             (y + j >= 0) && (x + i <= magnitude.cols) &&
              (y + j <= magnitude.rows))
            {
                // 梯度幅值边缘判断及连接
                if((magnitude.at<float>(y + j, x + i) > tLower) 
                  && (edges.at<float>(y + j, x + i) !=255))
                 {
                    followEdges(x + i, y + j, magnitude,
                      tUpper, tLower, edges);
                 }
            }
        }
    }
}
// 边缘检测
void edgeDetect(Mat &magnitude, int tUpper, int tLower, 
 Mat &edges) 
{    
    int rows = magnitude.rows;
    int cols = magnitude.cols;    
    edges = Mat(magnitude.size(), CV_32F, 0.0);    
    for (int x = 0; x < cols; x++) 
    {
        for (int y = 0; y < rows; y++) 
        {
            // 梯度幅值判断
            if (magnitude.at<float>(y, x) >= tUpper)
            {
                followEdges(x, y, magnitude, tUpper, 
                 tLower, edges);
            }
        }
    }   
}