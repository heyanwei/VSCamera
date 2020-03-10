#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>

namespace person
{
	namespace face
	{
		class YFace
		{
		public:
			//初始化函数，加载各种xml文件//
			bool Init();

			//bool:是否有人脸
			//cv::Mat mat 初始图片
			//cv::Mat &retMat 脸部添加矩形的图片
			//std::vector<cv::Mat> &faces 截取的脸部图片集合		
			bool HasFace(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& faces);

			//训练人脸，暂时只是用于存放临时代码
			bool Train();

		private:
			cv::CascadeClassifier _faceCascaClassifier;
		};
	}

}

