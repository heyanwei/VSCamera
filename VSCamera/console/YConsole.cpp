#include "YConsole.h"

namespace console
{
    YConsole& YConsole::Instance()
    {
        static YConsole theCT;
        return theCT;
    }

    YConsole::YConsole()
    {

    }

    YConsole::~YConsole()
    {

    }

    std::string YConsole::Show()
	{
        system("cls");
        std::cout << "================== 图像处理程序 ==================" << std::endl << std::endl;
        std::cout << (int)MainConsoleCode::Image <<". 图像处理示例" << std::endl;
        std::cout << (int)MainConsoleCode::Camera << ". 摄像头示例" << std::endl;
        std::cout << (int)MainConsoleCode::Vedio << ". 播放示例" << std::endl;
        std::cout << (int)MainConsoleCode::Train << ". 训练示例" << std::endl;
        std::cout << "b. 退出" << std::endl;
        std::cout << std::endl << std::endl << "请输入需要执行的操作编号：" << std::endl;

        std::string return_str = "";
        std::cin >> return_str;
        return return_str;
	}

    bool YConsole::IfContinue()
    {
        std::cout << std::endl << std::endl << "是否继续执行？(y/n)";
        std::string return_str = "";
        std::cin >> return_str;
        if (return_str == "y")
        {
            return true;
        }
        return false;
    }
}