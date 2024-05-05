/******************************************************************************
 * File:        GamesPlayedPage.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../../include/UI/GamesPlayedPage.hpp"

namespace Stuckfish
{
//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnUIRender()
{
	float windowPosX = 20;
	float windowPosY = 20;

	ImVec2 windowPos(windowPosX, windowPosY);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_app._specs.width - windowPosX*2), static_cast<float>(_app._specs.height - windowPosY*2)), ImGuiCond_Always);

	ImGui::Begin(WindowTitlesToString(WindowTitle::GAMESPLAYED_PAGE), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

	// page title
	ImGui::PushFont(_app._robotoFontHeader);
	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y - 340));
	ImGui::Text("Games played: April 2024"); // TODO: get the current month using a C++ library
	ImGui::PopFont();

	// list of all games played in the specified month from which we can extract:
	// the player and his ELO and same for the opponent, the game status for the player (win/lose/draw)
	// the game time control (rapid, blitz, bullet)
	ImVec2 buttonSize(confirmButtonSizeX*5, confirmButtonSizeY);
	if (!_hasRetrievedGames)
	{
		_res = _logic.GamesPlayedWithinPeriod(_userdata.username, "2024", "05");

		// handle every errors here
		if (_res.errorCode == EXIT_FAILURE)
		{
			_errorOccured = true;
			_errorMessage = _res.errorMessage;
		}
		_hasRetrievedGames = true;
	}
	
	// Begin a scrollable region
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	for (auto& game : _res.gamesData) {
		std::string buttonLabel = game.whiteUsername + "(" + game.whiteRating + ") vs " +
								  game.blackUsername + "(" + game.blackRating + ") - "  +
								  game.result + " - " + game.timeClass;

		ImVec2 buttonPos = ImVec2((ImGui::GetWindowSize().x - buttonSize.x) / 2.0f, ImGui::GetCursorPosY());
		ImGui::SetCursorPos(buttonPos);
		if (ImGui::Button(buttonLabel.c_str(), buttonSize)) {
			// link to the next page maybe ?
			std::cout << game.pgn;
		}
	}
	ImGui::EndChild();
	ImGui::End();
}

//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnUpdate()
{}

//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnAttach()
{}

//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnDetach()
{}

}