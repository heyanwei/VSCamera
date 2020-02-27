#include "HCamera.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include "utils/log/easylogging++.h"

namespace camera
{
    HCamera::HCamera()
    {
        LOG(INFO) << "HCamera init..." << el::base::consts::kPerformanceLoggerId;
    }

    HCamera::~HCamera()
    {
        LOG(INFO) << "HCamera end...";
    }

    bool HCamera::LoadXml()
    {
        if (!_faceCascaClassifier.load("/home/wilson/software/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"))
        {
            LOG(ERROR) << "load face model failed...";
            return false;
        }
        return true;
    }

    bool HCamera::Open()
    {
        LOG(INFO) << "HCamera start to open ...";

        _capture.open(0);
        if (!_capture.isOpened())
        {
            LOG(INFO) << "HCamera start failed ...";
            return false;
        }
        LOG(INFO) << "HCamera start succeeded ...";

        return true;
    }

    bool HCamera::Show()
    {
        cv::Mat frame;
        _capture >> frame;
        if (frame.empty())
        {
            LOG(ERROR) << "HCamera frame is empty...";
            return false;
        }
        imshow("HCamera", frame);

        return true;
    }

    bool HCamera::SaveFace(std::string name)
    {
        try
        {
            cv::Mat frame;
            _capture >> frame;
            if (frame.empty())
            {
                LOG(ERROR) << "HCamera frame is empty...";
                return false;
            }
            cv::Mat tmpMat = frame;
            cv::cvtColor(tmpMat, tmpMat, CV_BGR2GRAY);
            cv::equalizeHist(tmpMat, tmpMat); //直方图均衡化

            std::vector<cv::Rect> rect;
            _faceCascaClassifier.detectMultiScale(tmpMat, rect, 1.1, 3, 0, cv::Size(120, 120));
            if (rect.size() != 1)
            {
                LOG(ERROR) << "HCamera catch not 1 face..." << rect.size();
                imshow("HCamera", frame);
                return false;
            }

            LOG(INFO) << "HCamera catch one face";

            cv::rectangle(frame, rect[0], cv::Scalar(0, 0, 255), 2, 8, 0);

            std::string path = "/home/wilson/code/img/hyw/face" + name + ".png";
            cv::Rect roi = rect[0];
            if (!cv::imwrite(path, frame(roi)))
            {
                LOG(ERROR) << "HCamera write failed...";
                return false;
            }

            imshow("HCamera", frame);
            imshow("face", frame(roi));

            return true;
        }
        catch (const std::exception & e)
        {
            LOG(ERROR) << e.what();
        }
        return false;
    }

    bool HCamera::Train()
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

    bool HCamera::Predict()
    {
        try
        {
            cv::Mat frame;
            _capture >> frame;
            if (frame.empty())
            {
                LOG(ERROR) << "HCamera frame is empty...";
                return false;
            }
            cv::Mat tmpMat = frame;
            cv::cvtColor(tmpMat, tmpMat, CV_BGR2GRAY);
            cv::equalizeHist(tmpMat, tmpMat); //直方图均衡化

            std::vector<cv::Rect> rect;
            _faceCascaClassifier.detectMultiScale(tmpMat, rect, 1.1, 3, 0, cv::Size(25, 25));
            if (rect.size() != 1)
            {
                LOG(ERROR) << "HCamera catch not 1 face..." << rect.size();
                imshow("HCamera", frame);
                return false;
            }

            return true;
        }
        catch (const std::exception & e)
        {
            LOG(ERROR) << e.what();
        }
        return false;
    }

} // namespace camera