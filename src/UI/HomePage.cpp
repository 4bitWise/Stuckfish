/******************************************************************************
 * File:        UserInfosPage.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../../include/App/Stuckfish.hpp"

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
void HomePage::Render(void)
{
	bool isDisabled = (_event == HomePageEvent::ON_GAME_SELECTION);

	_event = (_event != HomePageEvent::ON_GAME_SELECTION) ? HomePageEvent::NONE : _event;

	
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(_app.specs.width, _app.specs.height));
	ImGui::Begin(WindowTitlesToString(WindowTitle::USERINFO_PAGE), NULL, ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoSavedSettings);

	RenderUsernameInputBox(isDisabled);

	if (_event == HomePageEvent::ON_GAME_SELECTION)
		RenderPopup();

	ImGui::End();
}

//------------------------------------------------------------------------------
/**
*/
void HomePage::Update()
{
	if (_event == HomePageEvent::ON_USERNAME_SUBMITTED)
	{
		if (_userData->username.empty())
		{
			_app.errorOccured = true;
			_app.errorMessage = ErrorsToString(Errors::EMPTY_USERNAME);
			return;
		}

		bool user_exists = _app.logic.IsChessDotComUser(_userData->username);

		if (!user_exists)
		{
			_app.errorOccured = true;
			_app.errorMessage = ErrorsToString(Errors::USERNAME_NOT_FOUND);
			return;
		}
		_event = HomePageEvent::ON_GAME_SELECTION;
	}

	return;
}

void HomePage::RenderPopup(void)
{
	Response res;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;
	ImVec2 popupSize(screenSize.x/2, screenSize.y/2);
	ImVec2 popupPos(screenSize.x * 0.5f - popupSize.x * 0.5f, screenSize.y * 0.5f - popupSize.y * 0.5f);
	std::string month = getCurrentMonth();
	std::string year = getCurrentYear();
	std::string pageTitleLabel = "Games played: " + month + '/' + year;

	ImGui::SetNextWindowPos(popupPos);
	ImGui::SetNextWindowSize(popupSize);
	ImGui::Begin(pageTitleLabel.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

	ImVec2 buttonSize(confirmButtonSizeX * 3, confirmButtonSizeY);
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	if (!_hasRetrievedGames)
	{
		// just use the current month automatically for now;
		res = _app.logic.GamesPlayedWithinPeriod(_userData->username, year, month);
		
		if (res.statusCode == ResponseCode::NO_GAMES_FOUND)
		{
			ImGui::PushFont(_app.robotoFontHeader);
			ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y));
			ImGui::Text("No game found for the specified period !");
			ImGui::PopFont();
			ImGui::EndChild();
			ImGui::End();
			return;
		}

		// every other errors.
		if (res.statusCode != ResponseCode::OK)
		{
			ImGui::PushFont(_app.robotoFontHeader);
			ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 170, windowMiddlePos.y));
			ImGui::Text("Unexpected error occured while fetching your games !");
			ImGui::PopFont();
			ImGui::EndChild();
			ImGui::End();
			return;
		}

		_gamesData = res.gamesData;
		_hasRetrievedGames = true;
	}


	// reverse the list of games
	for (const auto& game : _gamesData) {
		std::string buttonLabel = game.whiteUsername + "(" + game.whiteRating + ") vs " +
			game.blackUsername + "(" + game.blackRating + ") - " +
			game.result + " - " + game.timeClass;

		ImVec2 buttonPos = ImVec2((ImGui::GetWindowSize().x - buttonSize.x) / 2.0f, ImGui::GetCursorPosY());
		ImGui::SetCursorPos(buttonPos);
		if (ImGui::Button(buttonLabel.c_str(), buttonSize)) {
			_selectedGameData = std::make_shared<GamesData>(game);
			_event = HomePageEvent::NONE;
			_hasRetrievedGames = false;
		}
	}

	ImGui::EndChild();
	ImGui::End();
}

void HomePage::RenderUsernameInputBox(bool isDisabled)
{
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);
	ImVec2 buttonSize(confirmButtonSizeX, confirmButtonSizeY);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundingValue);
	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 200, windowMiddlePos.y - 90));
	ImGui::SetNextItemWidth(inputFieldWidth);
	
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));
	ImGui::InputTextWithHint("##input", "Chess.com username...", &_userData->username);
	ImGui::PopStyleVar();

	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 40));
	if (ImGui::Button(ButtonsToString(Buttons::CONFIRM), buttonSize) && !isDisabled) {
		_event = HomePageEvent::ON_USERNAME_SUBMITTED;
	}
	ImGui::PopStyleVar();
}

}