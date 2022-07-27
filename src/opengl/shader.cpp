#include <cstdint>
#include <luna/opengl/shader.h>

#include <luna/shared/file_parser.h>

#include <iostream>

namespace luna
{
    shader_program::shader_program(const std::string& vertex_path, const std::string& fragment_path)
    {
        _id = glCreateProgram();

        _vertex_id = glCreateShader(GL_VERTEX_SHADER);
        _fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertex_source = parse_file(vertex_path);
        std::string fragment_source = parse_file(fragment_path);
        const char* vertex_c_str = vertex_source.c_str();
        const char* fragment_c_str = fragment_source.c_str();

        glShaderSource(_vertex_id, 1, &vertex_c_str, nullptr);
        glShaderSource(_fragment_id, 1, &fragment_c_str, nullptr);
    }

    void shader_program::compile()
    {
        int success;
        char info_log[512];

        glCompileShader(_vertex_id);
        glGetShaderiv(_vertex_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(_vertex_id, 512, nullptr, info_log);
            std::cout << "vertex compilation failed:\n" << info_log << "\n";
        }

        glCompileShader(_fragment_id);
        glGetShaderiv(_fragment_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(_fragment_id, 512, nullptr, info_log);
            std::cout << "fragment compilation failed:\n" << info_log << "\n";
        }
    }

    void shader_program::link()
    {
        glAttachShader(_id, _vertex_id);
        glAttachShader(_id, _fragment_id);
        glLinkProgram(_id);

        int success;
        char info_log[512];

        glGetProgramiv(_id, GL_LINK_STATUS, &success);

        if(!success)
        {
            glGetProgramInfoLog(_id, 512, nullptr, info_log);
            std::cout << "shader programm linking failed:\n" << info_log << "\n";
        }
    }

    void shader_program::use()
    {
        glUseProgram(_id);
    }

    void shader_program::uniform1i(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }

    void shader_program::uniform2i(const std::string& name, const glm::ivec2& values)
    {
        glUniform2i(glGetUniformLocation(_id, name.c_str()), values.x, values.y);
    }

    void shader_program::uniform3i(const std::string& name, const glm::ivec3& values)
    {
        glUniform3i(glGetUniformLocation(_id, name.c_str()), values.x, values.y, values.z);
    }

    void shader_program::uniform4i(const std::string& name, const glm::ivec4& values)
    {
        glUniform4i(glGetUniformLocation(_id, name.c_str()), values.x, values.y, values.z, values.w);
    }

    void shader_program::uniform1f(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
    }

    void shader_program::uniform2f(const std::string& name, const glm::vec2& values)
    {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), values.x, values.y);
    }

    void shader_program::uniform3f(const std::string& name, const glm::vec3& values)
    {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), values.x, values.y);
    }

    void shader_program::uniform4f(const std::string& name, const glm::vec4& values)
    {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), values.x, values.y);
    }
}