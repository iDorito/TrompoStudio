#pragma once  
#include <GLFW/glfw3.h>  

// Constants  
constexpr unsigned WINDOW_DEFAULT_WIDTH = 800;  
constexpr unsigned WINDOW_DEFAULT_HEIGHT = 600;  

namespace Trompo {  
    class MyWindow {  
        private:  
            // Main Vars  
            GLFWwindow* m_window;  
            const char* m_title;  
            unsigned m_width;  
            unsigned m_height;  
            const unsigned m_id;  

        public:  
            // Constructor  
            MyWindow(const char* a_title = "My Window", 
                        unsigned a_width = WINDOW_DEFAULT_WIDTH,
                        unsigned a_height = WINDOW_DEFAULT_HEIGHT,
                        const unsigned a_id = 0);
            
            ~MyWindow();  

            unsigned get_id() const;  
            GLFWwindow* get_window();  
    };  
}