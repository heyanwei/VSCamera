#include "DahuaCamera.h"

#include "utils/log/easylogging++.h"

namespace camera
{
	bool DahuaCamera::Open(std::string ip, std::string user, std::string password)
	{
		//http://user:pass@cam_address:8081/cgi/mjpg/mjpg.cgi?.mjpg
		std::string url = "rtsp://" + user + ":" + password + "@" + ip + "/cam/realmonitor?channel=1&subtype=0";
		LOG(INFO) << "Open url: " << url;
		if (!_capture.open(url))
		{
			LOG(INFO) << "DahuaCamera open failed...";
			return false;
		}
		return true;
	}
}
