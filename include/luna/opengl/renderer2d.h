#pragma once

#include <luna/opengl/buffers/vertex_array.h>
#include <luna/opengl/buffers/vertex_buffer.h>
#include <luna/opengl/buffers/index_buffer.h>
#include <luna/opengl/shader.h>

#include <glm/glm.hpp>
#include <vector>

#include <iostream>


namespace luna
{
    struct vertex
    {
        glm::vec2 position;
    };
    class renderer2d
    {
    private:
        renderer2d();

        glm::mat4 projection;
        glm::mat4 view;

        const GLint max_vertices = 1000;
        std::vector<std::vector<vertex>> vertices;
        std::vector<std::vector<GLuint>> indices;
        GLint vertex_count;
        GLint index_count;

        shader_program shaders;
        vertex_array vao;
        vertex_buffer vbo;
        index_buffer ibo;

        void internal_update_settings();
        void internal_add_texture(GLuint object, const std::string& texture_path);
        void internal_draw();
        GLuint internal_create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);
    public:
        static renderer2d& get_instance();

        static void update_settings();
        static void add_texture(GLuint object, const std::string& texture_path);
        static void draw();
        static GLuint create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);
    };
}