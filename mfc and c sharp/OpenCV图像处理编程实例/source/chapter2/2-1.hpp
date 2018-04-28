// 功能：代码 2-1 Mat 类
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。

class CV_EXPORTS Mat
{
public：
// 标志位
int flags; 
// 数组的维数，>= 2
int dims ;  
// 行和列的数量或 (-1，-1) 此时数组已超过 2 维
int rows,cols; 
// 指向数据的指针
uchar *data ;
// 指针的引用计数器 阵列指向用户分配的数据时，当指针为 NULL
int * refcount ;
};
