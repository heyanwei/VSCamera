#include "YFace.h"

#include "utils/log/easylogging++.h"

namespace person
{
    namespace face
    {
        bool YFace::Init()
        {
            if (!_faceCascaClassifier.load("D:\\img\\dataset\\haarcascades\\haarcascade_frontalface_alt.xml"))
            {
                LOG(ERROR) << "load face model failed...";
                return false;
            }
            return true;
        }

        bool YFace::HasFace(cv::Mat mat, cv::Mat& retMat, std::vector<cv::Mat>& faces)
        {
            try
            {
                if (mat.empty())
                {
                    LOG(ERROR) << "HCamera frame is empty...";
                    return false;
                }
                cv::Mat tmpMat = mat;
                cv::cvtColor(tmpMat, tmpMat, CV_BGR2GRAY);
                cv::equalizeHist(tmpMat, tmpMat); //直方图均衡化

                std::vector<cv::Rect> rect;
                _faceCascaClassifier.detectMultiScale(tmpMat, rect, 1.1, 3, 0, cv::Size(50, 50));

                for (int i = 0; i < int(rect.size()); i++)
                {
                    cv::Rect roi = rect[i];

                    //在原图像中绘制矩形
                    cv::rectangle(mat, roi, cv::Scalar(0, 0, 255), 2, 8, 0);

                    //生成新的图片并添加到集合中
                    cv::Mat faceMat = mat(roi);
                    faces.push_back(faceMat);
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
}
