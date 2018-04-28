// 功能： 代码 2-29 算法计时
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
double tTime;
tTime = (double)getTickCount();
const int nTimes = 100;
for(int i  = 0;  i < nTimes; i++)
{
  	// 待测试算法code
}
tTime = 1000*((double)getTickCount() - tTime)/
getTickFrequency();
tTime /= nTimes;
std::cout << tTime << std::endl;
