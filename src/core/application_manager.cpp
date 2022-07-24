#include <luna/core/application_manager.h>
#include <iostream>

namespace luna
{
    void application_manager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height); 
    }

    application_manager::application_manager(uint32_t window_width, uint32_t window_height, const std::string& window_title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = std::make_unique<window>(window_width, window_height, window_title);
        _window->set_framebuffer_size_callback(framebuffer_size_callback);

        gladLoadGL();
        glViewport(0, 0, window_width, window_height);
    }

    void application_manager::update()
    {
        glfwPollEvents();
        _window->swap_buffers();

        if(_window->window_should_close())
        {
            _running = false;
        }
    }

    void application_manager::close_application()
    {
        _running = false;
    } 

    bool application_manager::running() const
    {
        return _running;
    }
}