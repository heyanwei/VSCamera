#pragma once

#include "../interface/YPerson.h"

namespace person
{
	class YFace : public YPerson
	{
	public:
		// ͨ�� YPerson �̳�
		virtual bool Init() override;

		// ͨ�� YPerson �̳�
		virtual bool Train() override;

	};

}

