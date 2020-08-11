#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <renderer/texture/texture.h>

struct VertexData {
    glm::vec2 pos;
    glm::vec2 texture_pos;
};

struct Renderer {
    glm::vec4 clear_color = glm::vec4(0.0f);
    std::vector<VertexData> vertex_data;
    std::vector<uint32_t> indicies;

    uint32_t vbo;
    uint32_t ebo;
    uint32_t vao;

    Texture *blank_texture;
}; 

namespace renderer {
    void initialize();
    void set_view(int w, int h);

    void draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float z_index);

    void new_frame();
    void end_frame();

    Renderer *get();
}