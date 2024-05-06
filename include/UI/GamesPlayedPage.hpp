/******************************************************************************
 * File:		GamesPlayedPage.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the required method to render the 2nd Page
 *****************************************************************************/

#pragma once

#include "../App/Stuckfish.hpp"
#include <ctime>

namespace Stuckfish
{
	class GamesPlayedPage : public Page
	{
	public:
		GamesPlayedPage(Core& app, Logic& logic, UserData& userData) : _app(app), _logic(logic), _userdata(userData)
		{};

		void OnUpdate() override;
		void OnUIRender() override;
		void OnAttach() override;
		void OnDetach() override;

	private:
		Core& _app;
		Logic& _logic;
		UserData& _userdata;
		Response _res;
		GamesData _selectedGameData;

		bool _hasRetrievedGames = false;
		bool _isFirstElement = true;
	};
}
