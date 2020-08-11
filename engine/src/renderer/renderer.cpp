#include "renderer.h"
#include <window/window.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <engine.h>
#include <utils\logger.h>

static Renderer *s_renderer;

void renderer::initialize() {
    s_renderer = new (Renderer);

    s_renderer->vertex_data.push_back({ { -0.5f, -0.5f }, { 0, 0 } });
    s_renderer->vertex_data.push_back({ { 0.5f, -0.5f }, { 1, 0 } });
    s_renderer->vertex_data.push_back({ { 0.5f, 0.5f }, { 1, 1 } });
    s_renderer->vertex_data.push_back({ { -0.5f, 0.5f }, { 0, 1 } });

    // first triangle
    s_renderer->indicies.push_back(0);
    s_renderer->indicies.push_back(1);
    s_renderer->indicies.push_back(3);

    // second triangle
    s_renderer->indicies.push_back(1);
    s_renderer->indicies.push_back(2);
    s_renderer->indicies.push_back(3);

    // generate our opengl objects
    glGenVertexArrays(1, &s_renderer->vao);
    glGenBuffers(1, &s_renderer->vbo);
    glGenBuffers(1, &s_renderer->ebo);
    glBindVertexArray(s_renderer->vao); // bind it to vao

    // bind our vertex data into the opengl shader
    glBindBuffer(GL_ARRAY_BUFFER, s_renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, s_renderer->vertex_data.size() * sizeof(VertexData), &s_renderer->vertex_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_renderer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_renderer->indicies.size() * sizeof(uint32_t), &s_renderer->indicies[0], GL_STATIC_DRAW);

    // vertex position attrib @ 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)offsetof(VertexData, pos));

    // texture coordinates attrib @ 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)offsetof(VertexData, texture_pos));

    // we are done with it, so unbind the data
    glBindVertexArray(0);

    // end of ogl objects, so we init our blank texture
    s_renderer->blank_texture = texture::create(1, 1);
    uint32_t wt_data = 0xffffffff;
    texture::set_data(s_renderer->blank_texture, &wt_data);
    texture::bind(s_renderer->blank_texture);
}

void renderer::set_view(int w, int h) {
    glViewport(0, 0, w, h);
}

void renderer::draw_rect(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float z_index) {
    glBindVertexArray(s_renderer->vao);

    texture::bind(s_renderer->blank_texture);

    auto transform = glm::mat4(1.f);
    transform = glm::translate(transform, glm::vec3(pos.x + size.x / 2, pos.y + size.y / 2, z_index));
    transform = glm::scale(transform, glm::vec3(size.x, size.y, 1));
    shader::set_mat4(engine::get()->main_shader, "u_model", transform);
    shader::set_vec4(engine::get()->main_shader, "u_color", color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void renderer::new_frame() {
    glClearColor(s_renderer->clear_color.x, s_renderer->clear_color.y, s_renderer->clear_color.z, s_renderer->clear_color.w);

    // clear with depth so we can use z-index
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::end_frame() {
    glfwSwapBuffers(window::get()->handle);
}

Renderer *renderer::get() {
    return s_renderer;
}
