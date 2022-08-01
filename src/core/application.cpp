#include <luna/core/application.h>
#include <luna/shared/log.h>

namespace luna
{
    void application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        get_instance()._window->change_dimensions(width, height);
        glViewport(0, 0, width, height);
    }

    application::application()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    }

    application& application::get_instance()
    {
        static application instance; 
        return instance;
    }

    void application::internal_create_window(uint16_t width, uint16_t height, const std::string& title)
    {
        _window = std::make_unique<window>(width, height, title);
        _window->set_framebuffer_size_callback(framebuffer_size_callback);

        gladLoadGL();
        glViewport(0, 0, width, height);
    }

    void application::internal_update()
    {
        glfwPollEvents();
        _window->swap_buffers();

        if(_window->window_should_close())
        {
            _running = false;
        }
    }

    void application::internal_close()
    {
        _running = false;
    } 

    bool application::internal_running() const
    {
        return _running;
    }

    void application::create_window(uint16_t width, uint16_t height, const std::string& title)
    {get_instance().internal_create_window(width, height, title);}

    void application::close()
    {get_instance().internal_close();}

    void application::update()
    {get_instance().internal_update();}

    bool application::running()
    {return get_instance().internal_running();}
}