// 功能：代码 7-6 SimpleBlobDetector 类
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
class SimpleBlobDetector : public FeatureDetector
{
public:
struct Params
{
Params();
float thresholdStep;
float minThreshold;
float maxThreshold;
size_t minRepeatability;
float minDistBetweenBlobs;
bool filterByColor;
uchar blobColor;
bool filterByArea;
float minArea, maxArea;
bool filterByCircularity;
float minCircularity, maxCircularity;
bool filterByInertia;
float minInertiaRatio, maxInertiaRatio;
bool filterByConvexity;
float minConvexity, maxConvexity;
};
SimpleBlobDetector( const SimpleBlobDetector: : Params &parameters = SimpleBlobDetector: : Params());
protected:
...
};
