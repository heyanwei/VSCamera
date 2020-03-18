#include "YBody.h"

#include "utils/log/easylogging++.h"

namespace person
{
	bool YBody::Init()
	{
		return LoadModel("D:\\img\\dataset\\haarcascades\\haarcascade_eye.xml");
	}
	bool YBody::Train()
	{
		return false;
	}
}