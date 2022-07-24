#include <luna/opengl/buffers/index_buffer.h>

namespace luna
{
    index_buffer::index_buffer(GLuint* indices, GLuint size)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
        unbind();
    }

    void index_buffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void index_buffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}