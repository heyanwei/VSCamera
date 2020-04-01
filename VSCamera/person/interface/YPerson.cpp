#include "YPerson.h"

#include "utils/log/easylogging++.h"

namespace person
{
	bool YPerson::LoadModel(std::string modelPath)
	{
		if (!_objectCascaClassifier.load(modelPath))
		{
			LOG(ERROR) << "load model failed...";
			return false;
		}
		return true;
	}
	bool YPerson::LoadNetwork(std::string ageProtoPath, std::string ageModelPath,
        std::string genderProtoPath, std::string genderModelPath,
        std::string faceProtoPath, std::string faceModelPath)
	{
        _ageNet = cv::dnn::readNet(ageModelPath, ageProtoPath);
        _genderNet = cv::dnn::readNet(genderModelPath, genderProtoPath);
        _faceNet = cv::dnn::readNet(faceModelPath, faceProtoPath);
        if (_ageNet.empty() || _genderNet.empty() || _faceNet.empty())
        {
            LOG(ERROR) << "LoadNetwork failed...";
            return false;
        }

		return true;
	}
	bool YPerson::HasObject(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& objects)
	{
        try
        {
            if (mat.empty())
            {
                LOG(ERROR) << "mat is empty...";
                return false;
            }
            cv::Mat tmpMat = mat;
            cv::cvtColor(tmpMat, tmpMat, CV_BGR2GRAY);
            cv::equalizeHist(tmpMat, tmpMat); //直方图均衡化

            std::vector<cv::Rect> rect;
            _objectCascaClassifier.detectMultiScale(tmpMat, rect, 1.1, 3, 0, cv::Size(50, 50));

            for (int i = 0; i < int(rect.size()); i++)
            {
                cv::Rect roi = rect[i];

                //在原图像中绘制矩形
                cv::rectangle(mat, roi, cv::Scalar(0, 0, 255), 2, 8, 0);

                //生成新的图片并添加到集合中
                cv::Mat objMat = mat(roi);
                objects.push_back(objMat);
            }
            retMat = mat;

            return true;
        }
        catch (const std::exception & e)
        {
            LOG(ERROR) << e.what();
        }
        return false;
	}

	bool YPerson::HasObjectExtra(cv::Mat mat, cv::Mat& retMat)
	{
        std::vector<std::vector<int>> bboxes;
        cv::Mat frameFace;
        tie(frameFace, bboxes) = getBox(_faceNet, mat, 0.7);
        if (bboxes.size() == 0) 
        {
            LOG(ERROR) << "No face detection...";
            return false;
        }
        int padding = 5;
        for (auto it = begin(bboxes); it != end(bboxes); ++it) {
            cv::Rect rec(it->at(0) - padding, it->at(1) - padding, it->at(2) - it->at(0) + 2 * padding, it->at(3) - it->at(1) + 2 * padding);
            cv::Mat face = mat(rec);

            cv::Mat blob;
            blob = cv::dnn::blobFromImage(face, 1, cv::Size(227, 227), MODEL_MEAN_VALUES, false);
            _genderNet.setInput(blob);

            std::vector<float> genderPreds = _genderNet.forward();

            int max_index_gender = std::distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
            std::string gender = genderList[max_index_gender];
            LOG(INFO) << "Gender: " << gender;

            _ageNet.setInput(blob);
            std::vector<float> agePreds = _ageNet.forward();

            int max_indice_age = std::distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
            std::string age = ageList[max_indice_age];
            LOG(INFO) << "Age: " << age;

            std::string label = gender + ", " + age;
            cv::putText(frameFace, label, cv::Point(it->at(0), it->at(1) - 15), 
                cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
        }

        retMat = frameFace;
        return true;
	}

    std::tuple<cv::Mat, std::vector<std::vector<int>>> YPerson::getBox(cv::dnn::Net net, cv::Mat& frame, double conf_threshold)
    {
        cv::Mat frameOpenCVDNN = frame.clone();

        int frameHeight = frameOpenCVDNN.rows;
        int frameWidth = frameOpenCVDNN.cols;

        double inScaleFactor = 1.0;
        cv::Size size = cv::Size(300, 300);

        cv::Scalar meanVal = cv::Scalar(104, 117, 123);

        cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, size, meanVal, true, false);

        net.setInput(inputBlob, "data");
        cv::Mat detection = net.forward("detection_out");
        cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        std::vector<std::vector<int>> bboxes;
        for (int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);

            if (confidence > conf_threshold)
            {
                int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
                int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
                int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
                int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);

                std::vector<int> box = { x1, y1, x2, y2 };
                bboxes.push_back(box);
                cv::rectangle(frameOpenCVDNN, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2, 4);
            }
        }
        return make_tuple(frameOpenCVDNN, bboxes);
    }
}

