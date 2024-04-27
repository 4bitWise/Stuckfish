#pragma once

#include <memory.h>

namespace Stuckfish
{
	class Page
	{
	public:
		virtual ~Page() = default;
		virtual void OnUpdate() {};
		virtual void OnUIRender() = 0;
	};
}