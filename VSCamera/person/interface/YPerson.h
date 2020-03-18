#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>

namespace person
{
	class YPerson
	{
	public:
		virtual bool Init() = 0;
		virtual bool Train() = 0;

		bool LoadModel(std::string modelPath);

		//bool:是否有该事物
		//cv::Mat mat 初始图片
		//cv::Mat &retMat 事物添加矩形的图片
		//std::vector<cv::Mat> &faces 截取的事物图片集合
		bool HasObject(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& objects);

	protected:
		cv::CascadeClassifier _objectCascaClassifier;
	};
}


