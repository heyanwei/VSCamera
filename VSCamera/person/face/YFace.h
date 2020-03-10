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
			//��ʼ�����������ظ���xml�ļ�//
			bool Init();

			//bool:�Ƿ�������
			//cv::Mat mat ��ʼͼƬ
			//cv::Mat &retMat ������Ӿ��ε�ͼƬ
			//std::vector<cv::Mat> &faces ��ȡ������ͼƬ����		
			bool HasFace(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& faces);

			//ѵ����������ʱֻ�����ڴ����ʱ����
			bool Train();

		private:
			cv::CascadeClassifier _faceCascaClassifier;
		};
	}

}

