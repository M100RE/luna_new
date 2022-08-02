#include <luna/opengl/renderer2d.h>
#include <luna/shared/log.h>
#include <math.h>

namespace luna
{
    polygon::polygon(GLfloat* vertices, GLuint vertices_size, GLuint* indices, GLuint indices_size)
        : _vbo{vertices, vertices_size}, _ibo{indices, indices_size}
    {
        _vao.add_data(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
        _elements = indices_size / sizeof(GLuint);
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

    polygon::polygon(polygon&& move) noexcept
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

    constexpr float angle(glm::vec2 previous_vertex, glm::vec2 current_vertex, glm::vec2 next_vertex)
    {
        previous_vertex -= current_vertex;
        next_vertex -= current_vertex;

        float previous_angle = glm::degrees(atan2(-previous_vertex.y, -previous_vertex.x)) + 180;
        float next_angle =  glm::degrees(atan2(-next_vertex.y, -next_vertex.x)) + 180;
        float sum = previous_angle - next_angle;
        if(sum < 0)
        {
            sum += 360;
        }
        return sum;
    }

    float triangle_area(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3)
    {
        float a = glm::distance(pos1, pos2);
        float b = glm::distance(pos2, pos3);
        float c = glm::distance(pos3, pos1);
        float s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    bool vertex_in_triangle(glm::vec2 previous_vertex, glm::vec2 current_vertex, glm::vec2 next_vertex, glm::vec2 point)
    {
        float first_third = triangle_area(point, current_vertex, next_vertex);
        float second_third = triangle_area(previous_vertex, point, next_vertex);
        float third_third = triangle_area(previous_vertex, current_vertex, point);

        float area_sum = first_third + second_third + third_third;
        float normal_area = triangle_area(previous_vertex, current_vertex, next_vertex);

        return area_sum <= normal_area + 0.01; 
    }

    int get_prev_vert(int current, std::vector<bool> finished)
    {
        if(current == 0)
        {
            current = finished.size();
        }
        for(int i = current - 1; true; i--)
        {
            if(i < 0)
            {
                i = finished.size() - 1;
            }
            if(!finished[i])
            {
                return i;
            }
        }
        return -1;
    }

    int get_next_vert(int current, std::vector<bool> finished)
    {
        if(current >= finished.size())
        {
            current = 0;
        }
        for(int i = current + 1; true; i++)
        {
            if(i >= finished.size())
            {
                i = 0;
            }
            if(!finished[i])
            {
                return i;
            }
        }
        return -1;
    }

    std::vector<GLuint> renderer2d::triangulate(std::vector<glm::vec2> positions)
    {
        int unfinished_verts = positions.size();
        int vertex_index = 0;
        std::vector<bool> finished(positions.size());
        std::vector<GLuint> indices;

        while(unfinished_verts > 3)
        {
            int prev_vert = get_prev_vert(vertex_index, finished);
            int next_vert = get_next_vert(vertex_index, finished);

            if(angle(positions[prev_vert], positions[vertex_index], positions[next_vert]) < 180)
            {
                bool valid_ear = true;
                for(int i = 0; i < positions.size(); i++)
                {
                    if(i != prev_vert && i != vertex_index && i != next_vert
                        && vertex_in_triangle(positions[prev_vert], positions[vertex_index], positions[next_vert], positions[i]))
                    {
                        valid_ear = false; 
                    }
                }
                if(valid_ear)
                {
                    finished[vertex_index] = true;
                    indices.push_back(prev_vert); 
                    indices.push_back(vertex_index); 
                    indices.push_back(next_vert); 
                    unfinished_verts--;
                }
            }
            vertex_index = get_next_vert(vertex_index, finished);
        }
        for(int i = 0; i < finished.size(); i++)
        {
            if(!finished[i])
            {
                indices.push_back(i);
            }
        }
        return indices;
    } 

    GLuint renderer2d::internal_create_polygon(std::vector<glm::vec2> positions, GLfloat angle, glm::vec4 color)
    {
        std::vector<GLuint> triangulated = triangulate(positions);
        GLuint* ibo_data = triangulated.data();

        GLfloat* vbo_data = vertex_bufferize(positions);
        static int count;

        count++;
        polygons.emplace_back(vbo_data, positions.size() * 2 * sizeof(GLfloat), ibo_data, triangulated.size() * sizeof(GLfloat));

        return polygons.size() - 1;
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
