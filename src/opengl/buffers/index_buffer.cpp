#include <luna/opengl/buffers/index_buffer.h>
#include <luna/shared/log.h>

namespace luna
{
    index_buffer::index_buffer(const void* indices, GLuint size)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
    }

    index_buffer::index_buffer(const index_buffer& copy)
    {
        LN_WARNING << "if any copy of this object runs out of scope, all objects are unusable, due to destructor, instead use move constructor";
        _id = copy._id;
    }

    index_buffer::index_buffer(index_buffer&& move)
    {
        _id = move._id;
        move._id = 0;
    }

    index_buffer::~index_buffer()
    {
        glDeleteBuffers(1, &_id);
    }

    void index_buffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void index_buffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void index_buffer::change_data(const void* indices, GLuint size)
    {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices);
    }
}