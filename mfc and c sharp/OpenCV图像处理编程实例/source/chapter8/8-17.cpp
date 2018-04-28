// 功能：代码 8-17 字符特征训练
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
// 字符的特征向量训练
// 特征提取函数: 输入图像，输出特征*向量*
typedef cv::Mat (*FEATURE_EXTRACTOR)(cv::Mat);
// Label 生成函数: 输入子文件夹名称，输出label
typedef double (*LABEL_MAKER)(std::string);
// 生成训练文件
void make_train_file(std::string src_dir, std::string dst,
	FEATURE_EXTRACTOR fea_extractor, LABEL_MAKER label_maker,
	int maxnum_per_class, bool shuffle)
{
	std::ofstream fs(dst.c_str());
	std::vector<std::string> sub_dirs;
	// 读入多个待训练图像源
	src_dir = TrimPath(src_dir);
	FindSubDirs(src_dir, sub_dirs);
	for (size_t i = 0; i != sub_dirs.size(); ++i) 
	{
		std::string sub = src_dir + "/" + sub_dirs[i];
		std::vector<std::string> img_paths;
		FindImages(sub, img_paths);
		// 随机选取
		if (shuffle) 
		{
			std::random_shuffle(img_paths.begin(), 
				img_paths.end());
		}
		if (img_paths.size() > maxnum_per_class) 
		{
			img_paths.erase(img_paths.begin() + 
				maxnum_per_class, img_paths.end());
		}
		for (size_t j = 0; j != img_paths.size(); ++j) 
		{
			// 训练文件每行的结构 
			// 实数的类标签——维数:该维数据
			fs << label_maker(sub_dirs[i]) << " ";
			// std::cout << sub_dirs[i] << "\n";
			cv::Mat pic = cv::imread(img_paths[j]);
			// 特征提取
			cv::Mat fea = fea_extractor(pic);
			float* dptr = (float*)fea.data;
			for (size_t k = 0; k != fea.total(); ++k, ++dptr) 
			{
				fs << (k + 1) << ":" << *dptr << " ";
			}
			fs << "\n";
		}
	}
	fs.close();
}
