#pragma once

#include "HCamera.h"

namespace camera
{
	class DahuaCamera : public HCamera
	{
	public:
		bool Open(std::string ip, std::string user, std::string password);
	};

}
