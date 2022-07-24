#pragma once

#include <glad/glad.h>
#include <luna/core/window.h>
#include <memory>

namespace luna
{
    class application_manager
    {
    private:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    protected:
        std::unique_ptr<window> _window;
        bool _running{true};
    public:
        application_manager(uint32_t window_width, uint32_t window_height, const std::string& title);
        void close_application();
        void update();

        bool running() const;
    };
}