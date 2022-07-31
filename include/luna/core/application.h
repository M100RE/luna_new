#pragma once

#include <glad/glad.h>
#include <luna/core/window.h>
#include <memory>

namespace luna
{
    class application
    {
    private:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        public:std::unique_ptr<window> _window;
        private:
        bool _running{true};

        void internal_create_window(uint16_t width, uint16_t height, const std::string& title);
        void internal_close();
        void internal_update();
        bool internal_running() const;
    public:
        application();
        static application& get_instance();

        static void create_window(uint16_t width, uint16_t height, const std::string& title);
        static void close();
        static void update();

        static bool running();
    };
}