#pragma once
#include "MyWindow.h"
#include <vector>
#include <memory>

namespace Trompo {
	class WindowManager {
		private:
			//Private variables
			std::vector<std::shared_ptr<MyWindow>> m_windows;
			unsigned m_next_window_id = 0;

		public:
			// Constructor
			WindowManager();
			// Destructor
			~WindowManager();

			// Init
			bool Init();
			//void Init(unsigned window_amount);
			
			// Creators
			MyWindow* createWindow(const char* title, unsigned width, unsigned height);
			MyWindow* createWindow(const char* title);
			MyWindow* createWindow();


			// Destroyers
			bool destroyWindow(GLFWwindow* w_handle);

			// Getters
			GLFWwindow* get_window_by_id(const unsigned window_id);
			std::vector<std::shared_ptr<MyWindow>> get_windows();
	};
};
