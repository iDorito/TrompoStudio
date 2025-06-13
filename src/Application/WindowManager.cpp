#include "WindowManager.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

namespace Trompo {
	WindowManager::WindowManager()
	{
	}

	WindowManager::~WindowManager()
	{
		spdlog::info("Clearing windows pointers and terminating glfw");
		m_windows.clear();
		glfwTerminate();
	}


	bool WindowManager::Init() {
		if (!glfwInit()) {
			spdlog::error("Error initializing GLFW");
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		auto firstWindow = createWindow();
		if (!firstWindow) {
			spdlog::error("Error creating first window");
			return false;
		}

		return true;
	}

	MyWindow* WindowManager::createWindow(const char* title, unsigned width, unsigned height)
	{
		// Getting next ID
		unsigned new_id = ++m_next_window_id;
		// Initializing new MyWindow object as a shared pointer
		auto new_window = std::make_shared<MyWindow>(title, width, height, new_id);

		// Checking is not null
		if (new_window->get_window() == nullptr) {
			spdlog::error("Error creating new_window");
			return nullptr;
		}
		// Pushing to array
		m_windows.push_back(new_window);

		return new_window.get();
	}

	MyWindow* WindowManager::createWindow()
	{
		return createWindow("Trompo default title", WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
	}

	MyWindow* WindowManager::createWindow(const char* title)
	{
		return createWindow(title, WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
	}

	bool WindowManager::destroyWindow(GLFWwindow* w_handle)
	{
		if (!w_handle) {
			spdlog::warn("Attempted to destroy a null window handle."); // Buen log adicional
			return false;
		}

		auto it = std::remove_if(m_windows.begin(), m_windows.end(),
			[w_handle](const std::shared_ptr<MyWindow>& w_ptr) {
				// Comprueba si el puntero compartido es válido y si la ventana GLFW coincide
				return w_ptr && w_ptr->get_window() == w_handle;
			});

		if (it != m_windows.end()) {
			// Pasa w_handle (formateado con fmt::ptr) al log
			spdlog::info("WindowManager: Removing window with handle: {}", fmt::ptr(w_handle));
			// Al borrar el shared_ptr del vector, si es la última referencia,
			// se llamará al destructor de MyWindow, que a su vez llamará a glfwDestroyWindow.
			m_windows.erase(it, m_windows.end());
			return true;
		}

		// Pasa w_handle (formateado con fmt::ptr) al log
		spdlog::warn("WindowManager: Window handle {} not found for destruction.", fmt::ptr(w_handle));
		return false;
	}

	GLFWwindow* WindowManager::get_window_by_id(const unsigned window_id)
	{
		for (const auto& w_ptr : m_windows) {
			if (w_ptr->get_id() == window_id) {
				return w_ptr->get_window();
			}
		}
	}
	std::vector<std::shared_ptr<MyWindow>> WindowManager::get_windows()
	{
		return m_windows;
	}
}
