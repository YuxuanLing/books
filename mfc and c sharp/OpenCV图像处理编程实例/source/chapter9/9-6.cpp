// 功能：代码 9-6 MOG2 成员函数参数设定
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 阴影去除 默认打开
pMOG2->setDetectShadows(true);
// 背景模型影响帧数 默认为500
pMOG2->setHistory(1000);
// 模型匹配阈值
pMOG2->setVarThreshold(50);
// 阴影阈值
pMOG2->setShadowThreshold(0.7);
//// 前景中模型参数，设置为0表示背景，255为前景，默认值127
pMOG2->setShadowValue(127);
//// 背景阈值设定 backgroundRatio*history
pMOG2->setBackgroundRatio(2);
//// 设置阈值的降低的复杂性
pMOG2->setComplexityReductionThreshold(0.02);
//// 高斯混合模型组件数量
pMOG2->setNMixtures(100);
//// 设置每个高斯组件的初始方差
pMOG2->setVarInit(0.5);
//// 新模型匹配阈值
pMOG2->setVarThresholdGen(9);
