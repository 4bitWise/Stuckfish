/******************************************************************************
 * File:        UserInfosPage.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../../include/App/Stuckfish.hpp"

namespace Stuckfish
{
//------------------------------------------------------------------------------
/**
*/
void HomePage::Render(void)
{
	_event = HomePageEvent::NONE;

	float centeredWindowPosX =  static_cast<float>(_app.specs.width / 2 - 390);
	float centeredWindowPosY = static_cast<float>(_app.specs.height / 2 - 120);

	ImVec2 buttonSize(confirmButtonSizeX, confirmButtonSizeY);
	ImVec2 windowPos(centeredWindowPosX, centeredWindowPosY);

	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_app.specs.width) / 2, static_cast<float>(_app.specs.height) / 2), ImGuiCond_Always);
	ImGui::Begin(WindowTitlesToString(WindowTitle::USERINFO_PAGE), NULL, ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundingValue);

	// page title
	ImGui::PushFont(_app.robotoFontHeader);
	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 225, windowMiddlePos.y - 140));
	ImGui::Text("Please provide your Chess.com username");
	ImGui::PopFont();

	// input field
	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 200, windowMiddlePos.y - 90));
	ImGui::SetNextItemWidth(inputFieldWidth);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));
	ImGui::InputTextWithHint("##input", "Chess.com username...", &_userData->username);
	ImGui::PopStyleVar();

	ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 40));
	if (ImGui::Button(ButtonsToString(Buttons::CONFIRM), buttonSize)) {
		_event = HomePageEvent::ON_USERNAME_SUBMITTED;
	}
	ImGui::PopStyleVar();
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
	}

	return;
}

}