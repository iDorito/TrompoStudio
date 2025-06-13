#include <glad/glad.h>
#include "App.h"
#include <spdlog/spdlog.h>
#include <iostream>

// --- Constructor y Destructor ---

App::App(int width, int height, const std::string& title)
    : m_window(nullptr), m_width(width), m_height(height), m_title(title) {
    spdlog::info("App creada.");
}

App::~App() {
    // Si la ventana todavía existe, la destruimos.
    if (m_window) {
        glfwDestroyWindow(m_window);
        spdlog::info("Ventana GLFW destruida.");
    }
    // Terminamos GLFW.
    glfwTerminate();
    spdlog::info("GLFW terminado.");
}

// --- Métodos Públicos ---

bool App::init() {
    // 1. Inicializar GLFW
    spdlog::info("Inicializando GLFW...");
    if (!glfwInit()) {
        spdlog::error("Fallo al inicializar GLFW.");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Crear la ventana
    spdlog::info("Creando la ventana: {} ({}x{})", m_title, m_width, m_height);
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (m_window == nullptr) {
        spdlog::error("Fallo al crear la ventana GLFW.");
        glfwTerminate();
        return false;
    }

    // 3. Establecer el contexto de OpenGL y configurar callbacks
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // 4. Inicializar GLAD
    spdlog::info("Inicializando GLAD...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Fallo al inicializar GLAD.");
        return false;
    }

    // Configurar el viewport inicial
    glViewport(0, 0, m_width, m_height);

    spdlog::info("Inicialización completada exitosamente.");
    return true;
}

void App::run() {
    spdlog::info("Iniciando bucle principal...");

    // Bucle principal de la aplicación
    while (!glfwWindowShouldClose(m_window)) {
        // 1. Procesar eventos (input, redimensionamiento, etc.)
        glfwPollEvents();

        // 2. Lógica de renderizado
        // Por ahora, solo limpiamos la pantalla con un color.
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- Aquí iría tu lógica de renderizado y actualización del juego ---

        // 3. Intercambiar buffers y mostrar el frame renderizado
        glfwSwapBuffers(m_window);
    }

    spdlog::info("Bucle principal terminado.");
}

// --- Métodos Privados (Callbacks) ---

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Se ajusta el viewport de OpenGL cuando la ventana cambia de tamaño.
    glViewport(0, 0, width, height);
    spdlog::info("Ventana redimensionada a: {}x{}", width, height);
}
