#include <luna/opengl/renderer2d.h>
#include <luna/shared/log.h>


namespace luna
{
    polygon::polygon(GLfloat* vertices, GLuint vertices_size, GLuint* indices, GLuint indices_size)
        : _vbo{vertices, vertices_size}, _ibo{indices, indices_size}
    {
        _vao.add_data(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
        _elements = 6;
        _vao.unbind();
        _vbo.unbind();
        _ibo.unbind();
    }

    polygon::polygon(const polygon& copy)
        : _vao{copy._vao}, _vbo{copy._vbo}, _ibo{copy._ibo},
        _elements{copy._elements}
    {
        LN_WARNING << "if any copy of this object runs out of scope, all objects are unusable, due to destructor, instead use move constructor";
    }

    polygon::polygon(polygon&& move)
        : _vao{std::move(move._vao)}, _vbo{std::move(move._vbo)}, _ibo{std::move(move._ibo)},
        _elements{move._elements}
    {}

    void polygon::draw()
    {
        _vao.bind();
        _ibo.bind();

        glDrawElements(GL_TRIANGLES, _elements, GL_UNSIGNED_INT, 0);
    }

    void GLAPIENTRY debug_callback( GLenum source,
                                    GLenum type,
                                    GLuint id,
                                    GLenum severity,
                                    GLsizei length,
                                    const GLchar* message,
                                    const void* userParam)
    {
        LN_ERROR << message;
    }

    renderer2d::renderer2d()
    {
        shaders.compile();
        shaders.link();

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debug_callback, 0);

    }

    renderer2d& renderer2d::get_instance()
    {
        static renderer2d instance;
        return instance;
    }

    GLfloat* renderer2d::vertex_bufferize(std::vector<glm::vec2> positions)
    {
        GLfloat* vbo_ptr = new GLfloat[positions.size() * 4];

        uint8_t counter = 0;
        for(int i = 0; i < positions.size(); i++)
        {
            vbo_ptr[counter] = positions[i].x;
            vbo_ptr[counter+1] = positions[i].y;

            counter += 2;
        }

        return vbo_ptr;
    }

    std::vector<GLuint> renderer2d::triangulate(std::vector<glm::vec2> positions)
    {
        int unfinished_verts = positions.size();
        int vertex_index = 0;

        //while(unfinished_verts > 3)
        while(vertex_index < 4)
        {
            int prev_vert = (vertex_index == 0) ? positions.size() - 1 : vertex_index - 1;
            int post_vert = (vertex_index == positions.size() - 1) ? 0 : vertex_index + 1;
            std::cout << prev_vert << "|" << post_vert << "\n";
            vertex_index++;
        }
        return {0};
    } 

    GLuint renderer2d::internal_create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color)
    {
        GLuint indices[] = 
        {
            0, 1, 2,
            0, 3, 2
        };
        GLfloat vertices[] = 
        {
            -0.5, -0.5,
            0.5, -0.5,
            0.5, 0.5,
            -0.5, 0.5
        };  
        //polygon* shape = new polygon(vertices, sizeof(vertices), indices, sizeof(indices));
        polygon shape(vertices, sizeof(vertices), indices, sizeof(indices));
        //polygons.push_back(std::move(shape));
        polygons.push_back(shape);

        /*init_new_shape();
        vaos[vaos.size()-1].bind();
        //GLfloat* vbo_data = vertex_bufferize(positions);
        vertex_buffer vbo(vertices, sizeof(vertices));
        vbos.push_back(vbo);

        /*std::vector<GLuint> triangulated = triangulate(positions);
        GLuint* ibo_data = triangulated.data();

        index_buffer ibo(indices, sizeof(indices));
        ibos.push_back(ibo);

        vaos.back().add_data(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
        vbos.back().unbind();
        ibos.back().unbind();
        vaos.back().unbind();

        return vaos.size() - 1;
        */
        return 0;
    }

    void renderer2d::internal_draw()
    {
        for(int i = 0; i < polygons.size(); i++)
        {
            shaders.use();
            //polygons[i]->draw();
            polygons[i].draw();
        }
    }

    /*void renderer2d::update_settings()
    {get_instance().internal_update_settings();}
    */

    /*void renderer2d::add_texture(GLuint object, const std::string& texture_path)
    {get_instance().internal_add_texture(object, texture_path);}
    */

    void renderer2d::draw()
    {get_instance().internal_draw();}

    GLuint renderer2d::create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color)
    {return get_instance().internal_create_polygon(positions, angle, color);}

    /*GLuint renderer2d::create_quad(glm::vec2 position, glm::vec2 size, GLfloat angle, glm::vec4 color)
    {return get_instance().internal_create_quad(position, size, angle, color);}
    */

    /*void renderer2d::model_matrix(GLuint object, glm::mat3 model_mat)
    {get_instance().internal_model_matrix(object, model_mat);}
    */
}
