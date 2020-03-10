#include "HCamera.h"

#include "utils/log/easylogging++.h"

namespace camera
{
    HCamera::HCamera()
    {
        LOG(INFO) << "HCamera init...";
    }

    HCamera::~HCamera()
    {
        LOG(INFO) << "HCamera end...";
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

    bool HCamera::Show(cv::Mat& frame)
    {
        try
        {
            _capture >> frame;
            return true;
        }
        catch (const std::exception & e)
        {
            LOG(ERROR) << e.what();
        }
        return false;
    }

} // namespace camera