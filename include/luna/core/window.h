#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace luna
{
    class window
    {
    private:
        GLFWwindow* _window;
        uint32_t _width;
        uint32_t _height;
    public:
        window(uint32_t width, uint32_t height, const std::string& title);

        const GLFWwindow* window_ptr() const;
        GLFWwindow* window_ptr();
        bool window_should_close() const;   
        uint32_t width() const;
        uint32_t height() const;

        void set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height));

        void swap_buffers();
    };
}