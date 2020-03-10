#pragma once

#include <string>
#include <iostream>

namespace console
{
	enum class MainConsoleCode
	{
		Image = 1,
		Camera,
		Vedio,
		Train,
	};

	class YConsole
	{
	public:
		static YConsole& Instance();
		std::string Show();
		bool IfContinue();

	private:
		YConsole();
		~YConsole();
	};

}

