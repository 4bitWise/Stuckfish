/******************************************************************************
 * File:        UserInfosPage.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the required methods to render the 1st page
 *****************************************************************************/

#include "Page.hpp"
#include "../Imgui.hpp"

#define CHESSBOARD_SIZE 8
#define TILE_SIZE 70.0f
#define LABEL_SIZE 20.0f

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

		static inline ImU32 whiteTileColor = IM_COL32(240, 217, 181, 255);
		static inline ImU32 blackTileColor = IM_COL32(181, 136, 99, 255);
		static inline ImU32 coordinatetextColor = IM_COL32(0, 0, 0, 255);
	private:
		Core& _app;
		HomePageEvent _event;
		std::shared_ptr<GamesData> _selectedGameData;
		std::vector<GamesData> _gamesData;
		std::shared_ptr<UserData> _userData;

		bool _hasRetrievedGames = false;
	};
}

