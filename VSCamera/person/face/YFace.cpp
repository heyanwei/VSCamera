#include "YFace.h"

#include "utils/log/easylogging++.h"

namespace person
{
	bool YFace::Init()
	{
		return LoadModel("D:\\img\\dataset\\haarcascades\\haarcascade_frontalface_alt.xml");
	}

	bool YFace::Train()
	{
        std::vector<cv::Mat> images;
        std::vector<int> labels;

        std::string names[2] = { "lijingru", "wilson" };

        for (int n = 0; n < 2; n++)
        {
            for (int i = 1; i < 11; i++)
            {
                std::string path = "D:\\img\\" + names[n] + "\\face" + std::to_string(i) + ".png";
                cv::Mat img = cv::imread(path, 0);
                if (!img.data)
                {
                    continue;
                }
                cv::resize(img, img, cv::Size(200, 200));
                images.push_back(img);
                labels.push_back(n);
            }
        }
        LOG(INFO) << "face images number " << images.size();
        LOG(INFO) << "face labels number " << labels.size();

        cv::Ptr<cv::face::FaceRecognizer> trainModel = cv::face::FisherFaceRecognizer::create();

        try
        {
            trainModel->train(images, labels);
            trainModel->save("face_record.xml");

            std::string path = "D:\\img\\lijingru\\face1.png";
            cv::Mat img = cv::imread(path, 0);
            if (!img.data)
            {
                return false;
            }
            cv::resize(img, img, cv::Size(200, 200));
            int val = trainModel->predict(img);
            LOG(INFO) << "predict value: " << val;
        }
        catch (std::exception e)
        {
            LOG(ERROR) << "Train error: " << e.what();
        }

        return true;
	}
}
