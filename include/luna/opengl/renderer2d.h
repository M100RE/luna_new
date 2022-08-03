#pragma once

#include <luna/opengl/buffers/vertex_array.h>
#include <luna/opengl/buffers/vertex_buffer.h>
#include <luna/opengl/buffers/index_buffer.h>
#include <luna/opengl/shader.h>

#include <glm/glm.hpp>
#include <vector>

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
        polygon(const polygon& copy) noexcept;
        polygon(polygon &&move) noexcept;

        ~polygon() = default;

        void draw();
    };

    class renderer2d
    {
    private:
        shader_program shaders{"../basic.vs", "../basic.fs"};
        std::vector<polygon> polygons;

        renderer2d();

        [[nodiscard]] static GLfloat* vertex_bufferize(std::vector<glm::vec2> positions);
        [[nodiscard]] constexpr static float angle(glm::vec2 previous_vertex, glm::vec2 current_vertex, glm::vec2 next_vertex) noexcept;
        [[nodiscard]] static float triangle_area(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3);
        [[nodiscard]] static bool vertex_in_triangle(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec2 point);
        [[nodiscard]] static uint16_t previous_vertex(uint16_t current_vertex, const std::vector<bool>& finished_vertices);
        [[nodiscard]] static uint16_t next_vertex(uint16_t current_vertex, const std::vector<bool>& finished_vertices);
        [[nodiscard]] static std::vector<GLuint> triangulate(std::vector<glm::vec2> positions);

        void internal_update_settings();
        void internal_add_texture(GLuint object, const std::string& texture_path);
        void internal_draw();
        GLuint internal_create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);
        GLuint internal_create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color);
        void internal_model_matrix(GLuint object, glm::mat3 model_mat);

    public:
        static renderer2d& get_instance();

        static void update_settings();
        static void add_texture(GLuint object, const std::string& texture_path);
        static void draw();

        [[nodiscard("index of quad might be useful")]]
        static GLuint create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color);

        [[nodiscard("index of polygon might be useful")]] 
        static GLuint create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color);

        static void model_matrix(GLuint object, glm::mat3 model_mat);
    };
}