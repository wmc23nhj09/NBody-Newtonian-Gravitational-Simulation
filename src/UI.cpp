#include "UI.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <imgui.h>
#include <iostream>

void UI::SetFlags(ImGuiWindowFlags& window_flags) {
	window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;      // Removes the top title bar
	window_flags |= ImGuiWindowFlags_NoResize;        // Disables dragging the edges
	window_flags |= ImGuiWindowFlags_NoMove;          // Disables moving the window
	window_flags |= ImGuiWindowFlags_NoCollapse;      // Disables the minimize button
	window_flags |= ImGuiWindowFlags_NoBackground;    // Makes the gray background transparent
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; // Keeps your game blocks interactive
	window_flags |= ImGuiSliderFlags_NoInput;		  // Stops Tab / Ctrl+Click abuse on sliders
};

void UI::DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags& window_flags, bool& BlockPropertyCreationMenu, float WINWIDTH, float WINHEIGHT, double& mass, float& rho) {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	ImGui::Begin("My Window", nullptr, window_flags);

	if (ImGui::Button("Block Creation Menu", ImVec2(120, 40))) {
		BlockPropertyCreationMenu = !BlockPropertyCreationMenu;
		std::cout << "Button clicked: "
			<< BlockPropertyCreationMenu
			<< std::endl;
	};

	if (BlockPropertyCreationMenu) {

		double minExponent = 15;
		double maxExponent = 30;
		ImGui::SetCursorPos(ImVec2(0.02f * WINWIDTH, 0.5f * WINHEIGHT));
		ImGui::PushItemWidth(0.865f * WINWIDTH);
		ImGui::SliderScalar("Mass", ImGuiDataType_Double, &mass, &minExponent, &maxExponent, "10^%.2f Kg");
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
};