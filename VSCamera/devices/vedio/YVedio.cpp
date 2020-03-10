#include "YVedio.h"

#include "utils/log/easylogging++.h"

namespace vedio
{
    bool YVedio::Open(std::string filename)
    {
        LOG(INFO) << "YVedio start to open ..."<< filename;

        _capture.open(filename);
        if (!_capture.isOpened())
        {
            LOG(INFO) << "YVedio start failed ...";
            return false;
        }
        LOG(INFO) << "YVedio start succeeded ...";

        return true;
    }

    bool YVedio::Show(cv::Mat& frame)
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
}