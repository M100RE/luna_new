#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

namespace luna
{
    class shader_program
    {
    private:
        GLuint _id;
        GLuint _vertex_id;
        GLuint _fragment_id;
    public:
        shader_program(const std::string& vertex_path, const std::string& fragment_path);
        void compile();
        void link();
        void use();
        void uniform1i(const std::string& name, int value);
        void uniform2i(const std::string& name, int value0, int value1);
        void uniform3i(const std::string& name, int value0, int value1, int value2);
        void uniform4i(const std::string& name, int value0, int value1, int value2, int value3);
        void uniform1f(const std::string& name, float value);
        void uniform2f(const std::string& name, glm::vec2 values);
        void uniform3f(const std::string& name, glm::vec3 values);
        void uniform4f(const std::string& name, glm::vec4 values);
        void uniform_mat2(const std::string& name, glm::mat2 mat);
        void uniform_mat3(const std::string& name, glm::mat3 mat);
        void uniform_mat4(const std::string& name, glm::mat4 mat);
    };
}