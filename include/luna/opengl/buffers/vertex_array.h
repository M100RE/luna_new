#pragma once

#include <glad/glad.h>

namespace luna
{
    class vertex_array
    {
    private:
        GLuint _id;
        GLuint _attrib_index;
    public:
        vertex_array(GLboolean bound = true);
        ~vertex_array();
        void bind();
        void unbind();
        void add_data(GLint component_count, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset);
    };
}