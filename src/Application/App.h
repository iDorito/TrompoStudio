#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <memory>

class App {
public:
    // Constructor: Inicializa la aplicación con las dimensiones y el título de la ventana.
    App(int width, int height, const std::string& title);

    // Destructor: Se asegura de que los recursos se liberen correctamente.
    ~App();

    // Inicia GLFW, crea la ventana y configura OpenGL (GLAD).
    // Devuelve 'true' si todo fue exitoso, 'false' si hubo un error.
    bool init();

    // Contiene el bucle principal de la aplicación.
    void run();

private:
    // Puntero a la ventana de GLFW. Usamos un puntero único para gestionar su ciclo de vida.
    GLFWwindow* m_window;

    // Dimensiones y título de la ventana.
    int m_width;
    int m_height;
    std::string m_title;

    // Función de callback estática para el reajuste del tamaño de la ventana.
    // GLFW necesita una función estática o global para los callbacks.
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
