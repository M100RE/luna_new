#pragma once

#include <glad/glad.h>

namespace luna
{
    struct data_layout
    {
        GLuint offset;
    };
    class vertex_buffer
    {
    private:
        GLuint _id;
    public:
        vertex_buffer(GLuint size);
        vertex_buffer(const void* vertices, GLuint size);
        ~vertex_buffer();

        void bind();
        void unbind();
        void change_data(const void* vertices, GLuint size);
    };
}