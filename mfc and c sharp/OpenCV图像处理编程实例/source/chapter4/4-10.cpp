// 功能：代码 4-10 boxFilter 滤波器实现
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。//
cv::Ptr<cv::FilterEngine> cv::createBoxFilter( int srcType, 
    int dstType, Size ksize,Point anchor, 
    bool normalize, int borderType )
{
    // 基础参数设置 图像深度
    int sdepth = CV_MAT_DEPTH(srcType);
    int cn = CV_MAT_CN(srcType), sumType = CV_64F;
    if( sdepth <= CV_32S && (!normalize ||
        ksize.width*ksize.height <= (sdepth == CV_8U ? (1<<23) :
        sdepth == CV_16U ? (1 << 15) : (1 << 16))) )
        sumType = CV_32S;
    sumType = CV_MAKETYPE( sumType, cn );
    // 获取滤波类中行滤波器信息
    Ptr<BaseRowFilter> rowFilter = getRowSumFilter(srcType,
     sumType, ksize.width, anchor.x );
    // 获取滤波类中列滤波器信息
    Ptr<BaseColumnFilter> columnFilter = getColumnSumFilter(sumType,
        dstType, ksize.height, anchor.y, normalize ? 
        1./(ksize.width*ksize.height) : 1);
    // 返回滤波器基类生成
    return Ptr<FilterEngine>(new FilterEngine(Ptr<BaseFilter>(0),
       rowFilter, columnFilter,
       srcType, dstType, sumType, borderType ));
}
// 盒子滤波器实现
void cv::boxFilter( InputArray _src, OutputArray _dst, int ddepth,
                Size ksize, Point anchor,
                bool normalize, int borderType )
{
    // 获取矩阵相关信息
    Mat src = _src.getMat();
    int sdepth = src.depth(), cn = src.channels();
    if( ddepth < 0 )
        ddepth = sdepth;
    _dst.create( src.size(), CV_MAKETYPE(ddepth, cn) );
    Mat dst = _dst.getMat();
    // 边界因子设定
    if( borderType != BORDER_CONSTANT && normalize )
    {
        if( src.rows == 1 )
            ksize.height = 1;
        if( src.cols == 1 )
            ksize.width = 1;
    }
    // 盒子滤波基类生成
    Ptr<FilterEngine> f = createBoxFilter( src.type(), dst.type(),
                        ksize, anchor, normalize, borderType );
    // apply方法实现相关滤波操作
    f->apply( src, dst );
}