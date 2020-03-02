#include <memory>
#include <iostream>

#include "utils/log/easylogging++.h"
#include "console/YConsole.h"
#include "image/HImage.h"
#include "camera/HCamera.h"

INITIALIZE_EASYLOGGINGPP

void RollbackHandle(const char* filename, std::size_t size) {}
void initlog()
{
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
        "%datetime|%level: %msg [%fbase %line]");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "D:\\log\\%datetime{%Y%M%d}.log");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::MaxLogFileSize, "2097152");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::PerformanceTracking, "false");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");

    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);

    el::Helpers::installPreRollOutCallback(RollbackHandle);
}

int HExit()
{
    LOG(INFO) << "程序结束 =============";
    return 0;
}

int main(int argc, char const* argv[])
{
    initlog();

    LOG(INFO) << "======================";
    LOG(INFO) << "程序启动 =============";

    console::YConsole& cons = console::YConsole::Instance();
    std::string str = "";
    while (1)
    {
        if (!cons.IfContinue())
        {
            break;
        }

        str = cons.Show();
        LOG(INFO) << "执行命令：" << str;
        if (str == "bye" || str == "b")
        {
            break;
        }
        int code = atoi(str.c_str());
        image::HImage img;
        camera::HCamera came;
        switch (code)
        {
        case (int)console::MainConsoleCode::Image:
            if (img.LoadMat("smile", "D:\\img\\1.jpg"))
            {
                img.Show();
                img.MResize(0.2, 0.2);
                img.Show();
            }
            break;
        case (int)console::MainConsoleCode::Camera:

            break;
        case (int)console::MainConsoleCode::FaceDetection:
            came.Train();
            break;
        case (int)console::MainConsoleCode::FacePredict:     
            if (came.Open() && came.LoadXml())
            {
                while (1)
                {
                    came.Predict();
                    cv::waitKey(20);
                }
                
            }           
            break;
        default:
            break;
        }
        
    }

    return HExit();
}
