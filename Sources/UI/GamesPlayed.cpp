#include "GamesPlayedPage.hpp"

namespace Stuckfish
{
	void GamesPlayedPage::OnUIRender()
	{
		float centeredWindowPosX = static_cast<float>(_app._specs.width / 2 - 390);
		float centeredWindowPosY = static_cast<float>(_app._specs.height / 2 - 120);

		ImVec2 windowPos(centeredWindowPosX, centeredWindowPosY);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_app._specs.width) / 2, static_cast<float>(_app._specs.height) / 2), ImGuiCond_Always);

		ImGui::Begin(WindowTitlesToString(WindowTitle::GAMESPLAYED_PAGE), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImVec2 contentRegion = ImGui::GetContentRegionAvail();
		ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

		ImGui::PushFont(_app._robotoFontHeader);
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 225, windowMiddlePos.y - 140));
		ImGui::Text("Please provide your Chess.com username");
		ImGui::PopFont();

		ImGui::End();
	}

	void GamesPlayedPage::OnUpdate()
	{}
	
	void GamesPlayedPage::OnAttach()
	{}

	void GamesPlayedPage::OnDetach()
	{}
}