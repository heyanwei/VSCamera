#pragma once

#include "../interface/YPerson.h"

namespace person
{
	class YBody : public YPerson
	{
	public:
		// ͨ�� YPerson �̳�
		virtual bool Init() override;

		// ͨ�� YPerson �̳�
		virtual bool Train() override;
	};
}


