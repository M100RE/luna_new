#pragma once

#include <glad/glad.h>
#include <luna/opengl/buffers/index_buffer.h>
#include <luna/opengl/buffers/vertex_buffer.h>

namespace luna
{
    class vertex_array
    {
    private:
        GLuint _id;
        GLuint _attrib_index;
    public:
        vertex_array(GLboolean bound = true);
        void bind();
        void unbind();
        void add_data(GLint component_count, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset);
    };
}