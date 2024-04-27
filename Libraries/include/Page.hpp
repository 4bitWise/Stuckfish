#pragma once

#include <memory.h>

namespace Stuckfish
{
	class Page
	{
	public:
		virtual ~Page() = default;
		virtual void OnUpdate() = 0;
		virtual void OnUIRender() = 0;

	public:
		bool _errorOccured = false;
		std::string _errorMessage = "";
	};
}