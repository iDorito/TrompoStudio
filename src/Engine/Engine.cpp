#include "Engine.h"
#include "../Application/WindowManager.h"
#include "EngineUI.h"
#include <../../dependencies/include/spdlog/spdlog.h>
#include <vector>

namespace Trompo
{
    Engine::Engine() {
        // Constructor
        spdlog::info("Engine constructor called");
    }

    Engine::~Engine() {
        // Destructor
        spdlog::info("Engine destructor called");
        glfwTerminate();
    }

    void handleClosingWindows(Trompo::WindowManager &w_manager, std::vector<GLFWwindow*> &windows_to_close) {
        for (const auto w_ptr : w_manager.get_windows()) {
            if (w_ptr) {
                GLFWwindow* c_window = w_ptr->get_window();
                if (c_window && glfwWindowShouldClose(c_window)) {
                    windows_to_close.push_back(c_window);
                }
            }
        }

        for (GLFWwindow* w_handle : windows_to_close) {
            spdlog::info("Closing window");
            w_manager.destroyWin(w_handle);
        }
    }

    void Engine::Run() {
        Trompo::WindowManager w_manager;
        if (!w_manager.Init()) {
            spdlog::error("Error initializing window manager");
            return;
        }
        std::vector<GLFWwindow*> windows_to_close;

		Trompo::EngineUI engine_ui;
		engine_ui.Init();
		spdlog::info("Engine UI initialized");


        // Main Loop
        while (!w_manager.get_windows().empty()) {
            glfwPollEvents();
			handleClosingWindows(w_manager, windows_to_close);

            for (const auto& w_ptr : w_manager.get_windows()) {
                if (w_ptr) {
                    // Context
                    GLFWwindow* current_window = w_ptr->get_window();
                    glfwMakeContextCurrent(current_window);

                    // ImGui


                    // Clear
                    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);

                    // Draw
                    glfwSwapBuffers(current_window);
                }
            }
        }
    }
}


