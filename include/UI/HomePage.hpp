/******************************************************************************
 * File:        UserInfosPage.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the required methods to render the 1st page
 *****************************************************************************/

#include "Page.hpp"
#include "../Imgui.hpp"
#include "../App/ChessBoard.hpp"
#include "../Utils.h"

namespace Stuckfish
{
	class Core;
}

namespace Stuckfish
{

	enum HomePageEvent
	{
		NONE = 0,
		ON_USERNAME_SUBMITTED,
		ON_GAME_SELECTION,
	};

	class HomePage
	{
	public:
		HomePage(Core& app) : _app(app), _userData(std::make_shared<UserData>())
		{
			_event = HomePageEvent::NONE;
			_selectedGameData = nullptr;
		}

		void Render(void);
		void Update(void);

		void RenderPopup(void);
		void RenderChessBoard(void);
		void RenderUsernameInputBox(bool isDisabled);
		void RenderGameReview(void);

	private:
		Core& _app;
		HomePageEvent _event;
		ChessBoard _board;

		std::shared_ptr<GamesData> _selectedGameData;
		std::vector<GamesData> _gamesData;
		std::shared_ptr<UserData> _userData;

		bool _hasDisplayedGames = false;
		bool _hasRetrievedGames = false;
	};
}

