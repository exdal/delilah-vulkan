#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

enum Movement { FORWARD, BACKWARD, RIGHT, LEFT };

struct Camera {
    glm::vec2 pos;
    glm::vec2 size;

    float aspect;
    float zoom;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 gui_projection;

    bool frozen;
};

namespace camera {
    void initialize(glm::vec2 pos, glm::vec2 size);
    void update_matrices();
    void update_gui_matrices();
    void move(Movement side, double delta_time);
    void freeze(bool state);

    Camera *get();
}