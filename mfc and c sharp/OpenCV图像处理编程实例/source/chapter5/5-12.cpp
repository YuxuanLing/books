// 功能：代码 5-12 非极大值抑制
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 非极大值抑制
void nonMaximumSuppression(Mat &magnitudeImage, 
  Mat &directionImage) 
{ 
    Mat checkImage = Mat(magnitudeImage.rows, 
        magnitudeImage.cols, CV_8U);  
    // 迭代器初始化
    MatIterator_<float>itMag = magnitudeImage.begin<float>();
    MatIterator_<float>itDirection = 
         directionImage.begin <float>();  
    MatIterator_<unsigned char>itRet = 
         checkImage.begin<unsigned char>();  
    MatIterator_<float>itEnd = magnitudeImage.end<float>(); 
    // 计算对应方向
    for (; itMag != itEnd; ++itDirection, ++itRet, ++itMag) 
    {
        // 将方向进行划分， 对每个方向进行幅值判断
        const Point pos = itRet.pos();   
        float currentDirection = atan(*itDirection) *
         (180 / 3.142);  
        while(currentDirection < 0) 
            currentDirection += 180;
        *itDirection = currentDirection;
        // 边界限定,对相应方向进行判断
        if (currentDirection>22.5&&currentDirection <= 67.5) 
        {
            // 邻域位置极值判断
            if(pos.y > 0 && pos.x > 0 && *itMag <=
               magnitudeImage.at<float>(pos.y - 1, pos.x - 1))
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
            if(pos.y < magnitudeImage.rows-1 && pos.x <
             magnitudeImage.cols-1 && *itMag <=
              magnitudeImage.at<float>(pos.y + 1, pos.x + 1))
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
        }else if(currentDirection>67.5&&currentDirection<= 112.5)
        {
             // 邻域位置极值判断
            if(pos.y > 0 && *itMag <= 
              magnitudeImage.at<float>(pos.y-1, pos.x)) 
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
            if(pos.y<magnitudeImage.rows-1 && 
              *itMag<=magnitudeImage.at<float>(pos.y+1, pos.x)) 
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
        }else if(currentDirection>112.5&&currentDirection<=157.5)
         {
             // 邻域位置极值判断
            if(pos.y>0 && pos.x<magnitudeImage.cols-1 && 
             *itMag<=magnitudeImage.at<float>(pos.y-1, 
              pos.x+1)) {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;;
            }
            if(pos.y < magnitudeImage.rows-1 && pos.x>0 && 
             *itMag<=magnitudeImage.at<float>(pos.y+1, 
             pos.x-1)) {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
        }else 
        {
             // 邻域位置极值判断
            if(pos.x > 0 && *itMag <= 
             magnitudeImage.at<float>(pos.y, pos.x-1)) 
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
            if(pos.x < magnitudeImage.cols-1 && *itMag <= 
              magnitudeImage.at<float>(pos.y, pos.x+1)) 
            {
                magnitudeImage.at<float>(pos.y, pos.x) = 0;
            }
        }       
    }    
}