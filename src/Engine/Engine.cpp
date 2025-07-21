#include "Engine.h"
#include "../Application/WindowManager.h"
#include <../../dependencies/include/spdlog/spdlog.h>
#include <vector>

Engine::Engine() {
    // Constructor
}

Engine::~Engine() {
    // Destructor
}

void Engine::Run() {

    // Window Manager
    Trompo::WindowManager w_manager;
    if (!w_manager.Init()) {
        spdlog::error("Error initializing window manager");
        return;
    }

    // Main Loop
    while (!w_manager.get_windows().empty()) {
        glfwPollEvents();

        std::vector<GLFWwindow*> windows_to_close;
        
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
            w_manager.destroyWindow(w_handle);
        }

        for (const auto& w_ptr : w_manager.get_windows()) {
            if (w_ptr) {
                GLFWwindow* current_window = w_ptr->get_window();
                glfwMakeContextCurrent(current_window);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(current_window);
            }
        }
    }
    
    glfwTerminate();
}
