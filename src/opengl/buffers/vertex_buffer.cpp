#include <luna/opengl/buffers/vertex_buffer.h>
#include <luna/shared/log.h>

namespace luna
{
    vertex_buffer::vertex_buffer(GLuint size)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    vertex_buffer::vertex_buffer(const void* vertices, GLuint size)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    vertex_buffer::vertex_buffer(const vertex_buffer& copy)
    {
        LN_WARNING << "if any copy of this object runs out of scope, all objects are unusable, due to destructor, instead use move constructor";
        _id = copy._id;
    }

    vertex_buffer::vertex_buffer(vertex_buffer&& move)
    {
        _id = move._id;
        move._id = 0;
    }

    vertex_buffer::~vertex_buffer()
    {
        glDeleteBuffers(1, &_id);
    }

    void vertex_buffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void vertex_buffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void vertex_buffer::change_data(const void* vertices, GLuint size)
    {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
    }
}