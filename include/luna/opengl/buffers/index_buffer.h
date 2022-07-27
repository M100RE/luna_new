#pragma once

#include <glad/glad.h>
#include <vector>

namespace luna
{
    class index_buffer
    {
    private:
        GLuint _id;
    public:
        index_buffer(const void* indices, GLuint size);
        ~index_buffer();
        void bind();
        void unbind();
        void change_data(const void* indices, GLuint size);
    };
}