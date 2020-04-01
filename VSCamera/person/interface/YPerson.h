#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>
#include <opencv2/dnn.hpp>

namespace person
{
	class YPerson
	{
	public:
		virtual bool Init() = 0;
		virtual bool Train() = 0;

		bool LoadModel(std::string modelPath);

		bool LoadNetwork(std::string ageProtoPath, std::string ageModelPath, 
			std::string genderProtoPath, std::string genderModelPath,
			std::string faceProtoPath, std::string faceModelPath);

		//bool:是否有该事物
		//cv::Mat mat 初始图片
		//cv::Mat &retMat 事物添加矩形的图片
		//std::vector<cv::Mat> &faces 截取的事物图片集合
		bool HasObject(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& objects);

		bool HasObjectExtra(cv::Mat mat, cv::Mat& retMat);

	protected:
		cv::CascadeClassifier _objectCascaClassifier;

		cv::dnn::Net _ageNet;
		cv::dnn::Net _genderNet;
		cv::dnn::Net _faceNet;

		const cv::Scalar MODEL_MEAN_VALUES = cv::Scalar(78.4263377603, 87.7689143744, 114.895847746);

		const std::vector<std::string> ageList = { "(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)",
		  "(38-43)", "(48-53)", "(60-100)" };

		const std::vector<std::string> genderList = { "Male", "Female" };

	private:
		std::tuple<cv::Mat, std::vector<std::vector<int>>> getBox(cv::dnn::Net net, cv::Mat& frame, double conf_threshold);

		
	};
}


