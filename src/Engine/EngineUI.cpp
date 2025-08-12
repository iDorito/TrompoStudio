#ifndef ImGuiConfigFlags_DockingEnable
#define ImGuiConfigFlags_DockingEnable (1 << 6)
#endif

#include "EngineUI.h"
#include "imgui.h"

namespace Trompo {
	void EngineUI::Init()
	{
		IMGUI_CHECKVERSION(1, 88, 0); // Ensure ImGui version compatibility
		// Initialize ImGui context
		ImGui::CreateContext();
		// Setup Dear ImGui style
		m_io = &ImGui::GetIO(); (void)m_io;
		// Setup ImGui configuration flags

		m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
	}
}
