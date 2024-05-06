/******************************************************************************
 * File:        GamesPlayedPage.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../../include/UI/GamesPlayedPage.hpp"


static
const std::string getCurrentMonth(void)
{
	std::time_t currentTime;
	std::tm currentTm;
	std::time(&currentTime);

	if (localtime_s(&currentTm, &currentTime) != 0) {
		std::cerr << "Error: Unable to get the current time." << std::endl;
		return "";
	}
	
	int currentMonth = currentTm.tm_mon + 1;
	
	if (currentMonth >= 1 && currentMonth <= 9)
	{
		return "0" + std::to_string(currentMonth);
	}
	return std::to_string(currentMonth);
}

static
const std::string getCurrentYear(void)
{
	std::time_t currentTime;
	std::tm currentTm;
	std::time(&currentTime);

	if (localtime_s(&currentTm, &currentTime) != 0) {
		std::cerr << "Error: Unable to get the current time." << std::endl;
		return "";
	}
	return std::to_string(currentTm.tm_year + 1900);
}

namespace Stuckfish
{
//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnUIRender()
{
	float windowPosX = 20;
	float windowPosY = 20;
	std::string month = getCurrentMonth();
	std::string year = getCurrentYear();

	// raise an error if year/month is empty.


	ImVec2 windowPos(windowPosX, windowPosY);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_app._specs.width - windowPosX*2), static_cast<float>(_app._specs.height - windowPosY*2)), ImGuiCond_Always);

	ImGui::Begin(WindowTitlesToString(WindowTitle::GAMESPLAYED_PAGE), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

	// page title
	ImGui::PushFont(_app._robotoFontHeader);
	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y - 340));
	std::string pageTitleLabel = "Games played: " + month + '/' + year;
	ImGui::Text(pageTitleLabel.c_str()); // TODO: get the current year using a C++ library
	ImGui::PopFont();

	ImVec2 buttonSize(confirmButtonSizeX * 5, confirmButtonSizeY);
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	if (!_hasRetrievedGames)
	{
		// just use the current month automatically for now;
		_res = _logic.GamesPlayedWithinPeriod(_userdata.username, year, month);
		_hasRetrievedGames = true;
	}
	
	// only when switch between months will be supported.
	if (_res.statusCode == ResponseCode::NO_GAMES_FOUND)
	{
		ImGui::PushFont(_app._robotoFontHeader);
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y));
		ImGui::Text("No game found for the specified period !");
		ImGui::PopFont();
		ImGui::EndChild();
		ImGui::End();
		return;
	}

	// every other errors.
	if (_res.statusCode != ResponseCode::OK)
	{
		ImGui::PushFont(_app._robotoFontHeader);
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y));
		ImGui::Text("Unexpected error occured while fetching your games !");
		ImGui::PopFont();
		ImGui::EndChild();
		ImGui::End();
		return;
	}

	// reverse the list of games
	for (const auto& game : _res.gamesData) {
		std::string buttonLabel = game.whiteUsername + "(" + game.whiteRating + ") vs " +
								  game.blackUsername + "(" + game.blackRating + ") - "  +
								  game.result + " - " + game.timeClass;

		ImVec2 buttonPos = ImVec2((ImGui::GetWindowSize().x - buttonSize.x) / 2.0f, ImGui::GetCursorPosY());
		ImGui::SetCursorPos(buttonPos);
		if (ImGui::Button(buttonLabel.c_str(), buttonSize)) {
			_selectedGameData = game;
			std::cout << game.pgn;
			//OnUpdate();
		}
	}
	ImGui::EndChild();
	ImGui::End();
}

//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnUpdate()
{
	OnDetach();
}

//------------------------------------------------------------------------------
/**
*/
void GamesPlayedPage::OnAttach()
{}

//------------------------------------------------------------------------------
/**
* Consider writing OnDetach() directly in Page.hpp
*/
void GamesPlayedPage::OnDetach()
{
	std::vector<std::shared_ptr<Page>>& pageStack = _app.GetPageStack();

	if (!pageStack.empty())
		pageStack.erase(pageStack.begin());

	return;
}

}