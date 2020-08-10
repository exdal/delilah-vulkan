#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Renderer {
    glm::vec4 clear_color = glm::vec4(0.0f);
};

namespace renderer {
    void initialize();
    void set_view(int w, int h);

    void new_frame();
    void end_frame();
}