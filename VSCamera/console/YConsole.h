#pragma once

#include <string>
#include <iostream>

namespace console
{
	enum class MainConsoleCode
	{
		Image = 1,
		Camera,
		DahuaCamera,
		Vedio,
		Train,
	};

	class YConsole
	{
	public:
		static YConsole& Instance();
		std::string Show();

		std::string Ask(std::string str);
		bool IfContinue();

	private:
		YConsole();
		~YConsole();
	};

}

