#include <memory>
#include <iostream>

#include "utils/log/easylogging++.h"
#include "console/YConsole.h"
#include "devices/camera/HCamera.h"
#include "devices/vedio/YVedio.h"
#include "person/face/YFace.h"

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

    camera::HCamera came;
    vedio::YVedio ved;
    cv::Mat imat;

    person::face::YFace pFace;
    if (!pFace.Init())
    {
        LOG(ERROR) << "pFace初始化失败...";
        return 0;
    }

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

        switch (code)
        {
        case (int)console::MainConsoleCode::Image:
            imat = cv::imread("D:\\img\\1.jpg");
            if (!imat.empty())
            {
                std::vector<cv::Mat> faces;
                pFace.HasFace(imat, imat, faces);
                cv::imshow("camera", imat);
                cv::waitKey();
            }
            break;
        case (int)console::MainConsoleCode::Camera:
            if (came.Open())
            {
                while (1)
                {
                    cv::Mat p;
                    if (came.Show(p) && (!p.empty()))
                    {
                        std::vector<cv::Mat> faces;
                        pFace.HasFace(p, p, faces);
                        cv::imshow("camera", p);
                    }
                    cv::waitKey(20);                  
                }
            }
            break;
        case (int)console::MainConsoleCode::Vedio:
            if (ved.Open(""))
            {
                while (1)
                {
                    cv::Mat p;
                    if (ved.Show(p) && (!p.empty()))
                    {
                        std::vector<cv::Mat> faces;
                        pFace.HasFace(p, p, faces);
                        cv::imshow("camera", p);
                    }
                    cv::waitKey(20);
                }
            }
            break;
        case (int)console::MainConsoleCode::Train:     
            pFace.Train();
            break;
        default:
            break;
        }
        
    }

    return HExit();
}
