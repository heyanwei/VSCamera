#pragma once

#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc/types_c.h>

namespace vedio
{
	class YVedio
	{
    public:
        bool Open(std::string filename);
        bool Show(cv::Mat& frame);

    private:
        cv::VideoCapture _capture;
	};
}


