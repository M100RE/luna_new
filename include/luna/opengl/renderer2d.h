#pragma once

#include <luna/opengl/buffers/vertex_array.h>
#include <luna/opengl/buffers/vertex_buffer.h>
#include <luna/opengl/buffers/index_buffer.h>
#include <luna/opengl/shader.h>

#include <glm/glm.hpp>
#include <sys/types.h>
#include <vector>

#include <iostream>


namespace luna
{
    struct vertex
    {
        glm::vec2 pos;
    };
    struct texture_vertex
    {
        glm::vec2 pos;
        glm::vec2 texture_coords;
    };

    class polygon
    {
    private:
        vertex_array _vao;
        vertex_buffer _vbo;
        index_buffer _ibo;

        GLsizei _elements;
    public:
        polygon(GLfloat* vertices, GLuint vertices_size, GLuint* indices, GLuint indices_size);

        void draw();
    };

    class renderer2d
    {
    private:

        shader_program shaders{"../basic.vs", "../basic.fs"};
        std::vector<polygon*> polygons;

        renderer2d();

        GLfloat* vertex_bufferize(std::vector<glm::vec2> positions);

        void internal_update_settings();
        void internal_add_texture(GLuint object, const std::string& texture_path);
        void internal_draw();
        GLuint internal_create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);
        GLuint internal_create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color);
        void internal_model_matrix(GLuint object, glm::mat3 model_mat);

    public:
        static renderer2d& get_instance();

        static std::vector<GLuint> triangulate(std::vector<glm::vec2> positions);

        static void update_settings();
        static void add_texture(GLuint object, const std::string& texture_path);
        static void draw();
        static GLuint create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);
        static GLuint create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color);
        static void model_matrix(GLuint object, glm::mat3 model_mat);
    };
}