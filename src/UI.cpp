#include "UI.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <imgui.h>
#include <string>
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

void UI::DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags& window_flags, bool& BlockPropertyCreationMenu, bool& SimulationSettings, float WINWIDTH, float WINHEIGHT, double& mass, double& massCoefficient,float& rho, double& MetersPerPixel) {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	ImGui::Begin("My Window", nullptr, window_flags);

	ImGui::SetCursorPos(ImVec2(0, .6639 * WINHEIGHT));

	if (ImGui::Button(" Block \n Creation \n Menu", ImVec2(120, WINHEIGHT - .6639 * WINHEIGHT))) {
		BlockPropertyCreationMenu = !BlockPropertyCreationMenu;
	};

	if (BlockPropertyCreationMenu) {
		double minCoefficient = 1;
		double maxCoefficient = 10;
		ImGui::SetCursorPos(ImVec2(120, 0.67f * WINHEIGHT));
		ImGui::PushItemWidth(0.66f * WINWIDTH);
		ImGui::SliderScalar("Mass Coefficient", ImGuiDataType_Double, &massCoefficient, &minCoefficient, &maxCoefficient, " %.2f");
		

		double minExponent = 1;
		double maxExponent = 30;
		ImGui::NewLine();
		ImGui::PushItemWidth(0.66f * WINWIDTH);
		std::string text = "Mass: " + std::to_string(massCoefficient) + "^%.2f kg";
		ImGui::SliderScalar("Mass Exponent", ImGuiDataType_Double, &mass, &minExponent, &maxExponent, text.c_str());

	}

	ImGui::SetCursorPos(ImVec2(WINWIDTH - 160, 0));

	if (ImGui::Button(" Simulation \n Settings ", ImVec2(120, WINHEIGHT - .6639 * WINHEIGHT))) {
		SimulationSettings = !SimulationSettings;
	};

	if (SimulationSettings) {
		double minVal = 0;
		double maxVal = 10;
		ImGui::SetCursorPos(ImVec2(0.67f * WINWIDTH, 120));
		ImGui::PushItemWidth(0.15 * WINWIDTH);
		ImGui::SliderScalar("MetersPerPixel", ImGuiDataType_Double, &MetersPerPixel, &minVal, &maxVal, "10^%.0f M/px");
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
};