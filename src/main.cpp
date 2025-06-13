#include "Application/App.h" // Asegúrate de que la ruta sea correcta
#include "Application/WindowManager.h"
#include <spdlog/spdlog.h>
#include <memory>

int main() {
    
    Trompo::WindowManager w_manager;

    if (!w_manager.Init()) {
        spdlog::error("Error initializing window manager");
        return -1;
    }

    const char* mytitle = "hello";
    auto second_window = w_manager.createWindow(mytitle);

    if (!second_window) {
        spdlog::error("Error creating second window");
    }

    while (!w_manager.get_windows().empty()) {
        glfwPollEvents();

        // Vector to kill windows on next loop
        std::vector<GLFWwindow*> windows_to_close;
        
        // main loop iterating through windows
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

    // El destructor de 'app' se llamará automáticamente aquí, limpiando todo.
    return 0;
}
