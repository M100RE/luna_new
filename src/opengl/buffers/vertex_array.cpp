#include <luna/opengl/buffers/vertex_array.h>

namespace luna
{
    vertex_array::vertex_array(GLboolean bound)
    {
        glGenVertexArrays(1, &_id);
        if(bound)
        {
            bind();
        }
    }

    void vertex_array::bind()
    {
        glBindVertexArray(_id);
    }

    void vertex_array::unbind()
    {
        glBindVertexArray(_id);
    }

    void vertex_array::add_data(GLint component_count, GLenum type, GLboolean normalized, GLsizei stride, int offset)
    {
        switch(type)
        {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_INT_2_10_10_10_REV:
            case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(_attrib_index, component_count, type, stride, (void*)offset);
            break;
            default:
            glVertexAttribPointer(_attrib_index, component_count, type, normalized, stride, (void*)offset);
        }
        glEnableVertexAttribArray(_attrib_index);
        _attrib_index++;
    } 
}