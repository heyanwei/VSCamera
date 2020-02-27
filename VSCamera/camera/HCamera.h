#pragma once

#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc/types_c.h>

namespace camera
{
    class HCamera
    {

    public:
        HCamera();
        ~HCamera();

        bool LoadXml();
        bool Open();
        bool Show();
        bool SaveFace(std::string name);
        bool Train();
        bool Predict();

    private:
        cv::VideoCapture _capture;
        cv::CascadeClassifier _faceCascaClassifier;
    };

} // namespace camera