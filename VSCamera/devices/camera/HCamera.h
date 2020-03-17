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

        bool Open();
        bool Show(cv::Mat &frame);

        cv::VideoCapture _capture;       
    };

} // namespace camera