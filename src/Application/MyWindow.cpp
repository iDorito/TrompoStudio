#include "MyWindow.h"
#include <spdlog/spdlog.h>

namespace Trompo{
	MyWindow::MyWindow(const char* a_title, unsigned a_width, unsigned a_height, const unsigned a_id)
		: m_title(a_title), m_width(a_width), m_height(a_height), m_id(a_id) // Use initializer list to properly initialize member variables
	{
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

		if (!m_window) {
			spdlog::error("Window couldn't be created! id: {}", a_id);
		}
	}
	
	MyWindow::~MyWindow()
	{
		if (m_window) {
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
	}
	
	unsigned MyWindow::get_id() const
	{
		return m_id;
	}
	
	GLFWwindow* MyWindow::get_window()
	{
		return m_window;
	}
}


