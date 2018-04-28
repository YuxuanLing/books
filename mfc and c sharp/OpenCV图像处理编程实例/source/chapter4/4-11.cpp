// 功能：代码 4-11 均值滤波器实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
void cv::blur( InputArray src, OutputArray dst,
      Size ksize, Point anchor, int borderType )
{
    // 调用盒滤波器
    boxFilter( src, dst, -1, ksize, anchor, true, borderType );
}
