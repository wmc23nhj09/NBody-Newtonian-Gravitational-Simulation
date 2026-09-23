#pragma once
#include <imgui.h>
#include <SDL3/SDL.h>

class UI {
public:
	void SetFlags(ImGuiWindowFlags& window_flags);

	void DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags& window_flags, bool& BlockPropertyCreationMenu, float WINWIDTH, float WINHEIGHT, double& mass, float& rho);
};