#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

static Camera *s_camera;

#define CAMERA_SPEED 200.0f

void camera::initialize(glm::vec2 pos, glm::vec2 size) {
    s_camera = new (Camera);
    memset(s_camera, 0, sizeof(Camera));

    s_camera->pos = pos;
    s_camera->aspect = size.x / size.y;
    s_camera->size = size;

    s_camera->view = {};
    s_camera->projection = {};
    s_camera->gui_projection = {};

    s_camera->frozen = true;
    s_camera->zoom = 1;

    update_matrices();
    update_gui_matrices();
}

void camera::update_matrices() {

    s_camera->projection = glm::ortho(
        (int)s_camera->pos.x * s_camera->zoom, 
        ((int)s_camera->size.x + (int)s_camera->pos.x) * s_camera->zoom, 
        ((int)s_camera->size.y + (int)s_camera->pos.y) * s_camera->zoom, (int)s_camera->pos.y * s_camera->zoom,
        -100.f, 100.f);

    s_camera->gui_projection = glm::ortho(0.f, s_camera->size.x, s_camera->size.y, 0.f, -100.f, 100.f);

    s_camera->view = glm::mat4(1.f);
}

void camera::update_gui_matrices() {
}

void camera::move(Movement side, double delta_time) {
    if (s_camera->frozen)
        return;

    auto velocity = (float)(CAMERA_SPEED * delta_time);
    switch (side) {
        case FORWARD:
            s_camera->pos.y -= velocity;
            break;
        case BACKWARD:
            s_camera->pos.y += velocity;
            break;
        case RIGHT:
            s_camera->pos.x += velocity;
            break;
        case LEFT:
            s_camera->pos.x -= velocity;
            break;
        default:
            break;
    }

    update_matrices();
}

void camera::freeze(bool state) {
    s_camera->frozen = state;
}

Camera *camera::get() {
    return s_camera;
}
