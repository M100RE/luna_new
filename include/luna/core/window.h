#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace luna
{
    class window
    {
    private:
        GLFWwindow* _window;
        uint16_t _width, _height;
    public:
        window(uint32_t width, uint32_t height, const std::string& title);

        [[nodiscard]] const GLFWwindow* window_ptr() const;
        [[nodiscard]] GLFWwindow* window_ptr();
        [[nodiscard]] bool window_should_close() const;   
        [[nodiscard]] uint32_t width() const;
        [[nodiscard]] uint32_t height() const;

        void change_dimensions(uint16_t width, uint16_t height);

        void set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height));

        void swap_buffers();
    };
}