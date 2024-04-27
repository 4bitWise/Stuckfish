#include <UserCredentials.hpp>

namespace Stuckfish
{
	void UserCredentials::OnUIRender()
	{
		float windowWidth = (_app._specs.width / 2) - 390;
		float windowHeight = (_app._specs.height / 2) - 120;

		ImVec2 buttonSize(200, 35);
		ImVec2 windowPos(windowWidth, windowHeight);

		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_app._specs.width) / 2, static_cast<float>(_app._specs.height) / 2), ImGuiCond_Always);

		ImGui::Begin("Background", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImVec2 contentRegion = ImGui::GetContentRegionAvail();

		// Calculate the middle position of the window
		ImVec2 windowMiddlePos = ImVec2(contentRegion.x / 2.0f, contentRegion.y / 2.0f);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

		ImGui::PushFont(_app._robotoFontHeader);
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 225, windowMiddlePos.y - 140));
		ImGui::Text("Please provide your Chess.com username");
		ImGui::PopFont();

		// input field
		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - 200, windowMiddlePos.y - 90));
		ImGui::SetNextItemWidth(400);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));
		_textChanged = ImGui::InputTextWithHint("##input", "Chess.com username...", &_useraccount);
		ImGui::PopStyleVar();

		ImGui::SetCursorPos(ImVec2(windowMiddlePos.x - (buttonSize.x / 2.0f), windowMiddlePos.y - 40));
		if (ImGui::Button("Confirm", buttonSize)) {
			// Handle confirmation here
			// Handle empty value error (Exceptions.hpp)
			// Handle case when value can't be found (Exceptions.hpp)
			std::cout << "Username: " << _useraccount << std::endl;
		}
		ImGui::PopStyleVar();
		ImGui::End();
	}
}