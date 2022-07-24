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
        index_buffer(GLuint* indices, GLuint size);
        void bind();
        void unbind();
    };
}