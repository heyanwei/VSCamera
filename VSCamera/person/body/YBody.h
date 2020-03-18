#pragma once

#include "../interface/YPerson.h"

namespace person
{
	class YBody : public YPerson
	{
	public:
		// 通过 YPerson 继承
		virtual bool Init() override;

		// 通过 YPerson 继承
		virtual bool Train() override;
	};
}


