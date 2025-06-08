// Main Libs
#include <iostream>

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Logging
#include <spdlog/spdlog.h>

//int main()
//{
//	std::cout << "Test" << std::endl;
//
//	return 0;
//}

// Prototype functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void glfw_init()
{
	/*
		Initializing GLFW
	*/
	spdlog::info("Initializing GLFW");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Declares major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Declares minor version.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Declares the profile we will be using
}

int glad_init(std::vector<GLFWwindow*> windows) {
	spdlog::info("Initializing GLAD");
	glfwMakeContextCurrent(windows[0]);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("Couldn't load GLAD");
		return -1;
	}

	return 0;
}

GLFWwindow* new_window(int width, int height, char* name)
{
	spdlog::info("Creating GLFW Window");
	GLFWwindow* new_window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (new_window == NULL) {
		spdlog::error("Failed to create GLFW Window");
		glfwTerminate();
		return NULL;
	}

	return new_window;
}

int main()
{
	// Init glfw
	glfw_init();

	// ---------------------------
	// Window vector
	// ---------------------------
	std::vector<GLFWwindow*> windows;

	spdlog::info("Creating GLFW Window");
	char w1_name[] = "Window1";
	auto window1 = new_window(800, 600, w1_name);

	// ---------------------------
	// Window 2
	// ---------------------------
	char w2_name[] = "Window2";
	auto window2 = new_window(800, 600, w2_name);

	windows.push_back(window1);
	windows.push_back(window2);

	glad_init(windows);

	for (auto w : windows) {
		int w_width, w_height;
		glfwGetWindowSize(w, &w_width, &w_height);

		glfwMakeContextCurrent(w);
		// Setting up viewport
		glViewport(0, 0, w_width, w_height);
		// Setting up callback for resize
		glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);
	}

	// ---------------------------
	// MAIN LOOP
	// ---------------------------
	// While window close event is not triggered for current window, it should not close.
	while (!windows.empty()) {
		// Polling all pending events
		glfwPollEvents();

		for (auto w_iterator = windows.begin(); w_iterator != windows.end();) {
			GLFWwindow* current_window = *w_iterator;

			if (glfwWindowShouldClose(current_window)) {
				spdlog::info("Closing window");
				glfwDestroyWindow(current_window);
				w_iterator = windows.erase(w_iterator);
			}
			else
			{
				// Initialize context
				glfwMakeContextCurrent(current_window);

				// Clear screen
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				// Swap buffer to last generated
				glfwSwapBuffers(current_window);

				w_iterator++;
			}
		}
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	spdlog::info("Window has been resized to: " + std::to_string(width) + "x" + std::to_string(height));
	glViewport(0, 0, width, height);
}
