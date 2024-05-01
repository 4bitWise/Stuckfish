#pragma once

#include "Stuckfish.hpp"

namespace Stuckfish
{
	class GamesPlayedPage : public Page
	{
	public:
		GamesPlayedPage(Core& app, Logic& logic) : _app(app), Page(logic)
		{}
		void OnUpdate() override;
		void OnUIRender() override;
		void OnAttach() override;
		void OnDetach() override;

	private:
		Core& _app;
		std::string _username = "";
		bool		_textChanged = false;
	};

}
