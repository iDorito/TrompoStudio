#pragma once

#include "imgui.h"

namespace Trompo
{
	class EngineUI
	{
	public:
		EngineUI() = default;
		~EngineUI() = default;

		void Init();
		ImGuiIO* GetIO() { return m_io; }

	private:
		ImGuiIO* m_io = nullptr;
	};
}