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
        std::cout << "================== ͼ������� ==================" << std::endl << std::endl;
        std::cout << "1. ͼ����ʾ��" << std::endl;
        std::cout << "2. ����ͷʾ��" << std::endl;
        std::cout << "3. �������ʾ��" << std::endl;
        std::cout << "4. ����Ԥ��ʾ��" << std::endl;
        std::cout << "b. �˳�" << std::endl;
        std::cout << std::endl << std::endl << "��������Ҫִ�еĲ�����ţ�" << std::endl;

        std::string return_str = "";
        std::cin >> return_str;
        return return_str;
	}

    bool YConsole::IfContinue()
    {
        std::cout << std::endl << std::endl << "�Ƿ����ִ�У�(y/n)";
        std::string return_str = "";
        std::cin >> return_str;
        if (return_str == "y")
        {
            return true;
        }
        return false;
    }
}