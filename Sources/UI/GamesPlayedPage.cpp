#include "GamesPlayedPage.hpp"

namespace Stuckfish
{
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

		ImVec2 buttonSize(confirmButtonSizeX*5, confirmButtonSizeY);
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 300));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
		
		// list of all games played in the specified month from which we can extract:
		// the player and his ELO and same for the opponent, the game status for the player (win/lose/draw)
		// the game time control (rapid, blitz, bullet)
		//std::cout << "\nUsername: " << _username << std;;
		_logic.GamesPlayedWithinPeriod(_userdata.username , "2024", "04");

		// games list
		if (ImGui::Button("Button 1", buttonSize))
		{
			std::cout << "1";
		}
		
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 260));
		if (ImGui::Button("Button 2", buttonSize))
		{
			// Handle button click
			std::cout << "2";
		}

		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 220));
		if (ImGui::Button("Button 3", buttonSize))
		{
			// Handle button click
			std::cout << "3";
		}
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void GamesPlayedPage::OnUpdate()
	{}
	
	void GamesPlayedPage::OnAttach()
	{}

	void GamesPlayedPage::OnDetach()
	{}
}