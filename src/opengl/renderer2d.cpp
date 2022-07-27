#include <luna/opengl/renderer2d.h>
#include <iostream>

namespace luna
{
    //vertex_array renderer2d::vao;
    //vertex_buffer renderer2d::vbo(max_vertices* sizeof(vertex));
    //index_buffer renderer2d::ibo(nullptr, max_vertices * sizeof(GLint));

    renderer2d::renderer2d()
        : vbo(max_vertices * sizeof(vertices)), ibo(nullptr, max_vertices * sizeof(GLuint)),
        shaders("../basic.vs", "../basic.fs")
    {
        vao.add_data(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
        shaders.compile();
        shaders.link();
    }

    renderer2d& renderer2d::get_instance()
    {
        static renderer2d instance;
        return instance;
    }

    void renderer2d::internal_update_settings()
    {
        std::cout << "hello\n";
        //glPolygonMode(GL_FRONT_AND_BACK, (settings::wireframe) ? GL_LINE : GL_FILL);
    }

    GLuint renderer2d::internal_create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color)
    {
        vertex_count += 4;
        index_count += 6;

        std::vector<vertex> quad_vertices(4);
        quad_vertices[0].position = position;
        quad_vertices[1].position = {position.x + size.x, position.y};
        quad_vertices[2].position = {position.x + size.x, position.y + size.y};
        quad_vertices[3].position = {position.x, position.y + size.y};

        vertices.push_back(quad_vertices);

        unsigned int offset = indices.size();
        indices.push_back({
            0 + offset, 1 + offset, 2 + offset,
            3 + offset, 0 + offset, 2 + offset
        });

        return vertices.size() - 1;
    }

    int counter = 0;
    void renderer2d::internal_draw()
    {
        GLfloat vertices_ptr[2 * vertex_count];
        int count = 0;
        for(int i = 0; i < vertices.size(); i++)
        {
            for(int j = 0; j < vertices[i].size(); j++)
            {
                vertices_ptr[count] = vertices[i][j].position.x;
                vertices_ptr[count+1] = vertices[i][j].position.y;
                count += 2;
            }
        } 

        GLuint indices_ptr[index_count];

        count = 0;
        for(int i = 0; i < indices.size(); i++)
        {
            for(int j = 0; j < indices[i].size(); j++)
            {
                indices_ptr[count] = indices[i][j];
                count++;
            }
        }

        vao.bind();
        vbo.bind();
        vbo.change_data(vertices_ptr, sizeof(vertices_ptr));
        ibo.bind();
        ibo.change_data(indices_ptr, sizeof(indices_ptr));

        shaders.use();
        
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
    }


    void renderer2d::update_settings()
    {get_instance().internal_update_settings();}

    /*void renderer2d::add_texture(GLuint object, const std::string& texture_path)
    {get_instance().internal_add_texture(object, texture_path);}
    */

    void renderer2d::draw()
    {get_instance().internal_draw();}

    GLuint renderer2d::create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color)
    {return get_instance().internal_create_quad(position, size, angle, color);}
}