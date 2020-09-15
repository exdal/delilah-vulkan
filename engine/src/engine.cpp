#include "shaders.h"
#include "engine.h"
#include <GLFW/glfw3.h>
#include <renderer/camera/camera.h>
#include <utils/logger.h>
#include <algorithm>
#include <renderer/vulkan/vk_core.h>

#define FLAG_HAS(en, flag) (en & flag)

static Engine *s_engine;

void engine::initialize(const char *title, glm::vec2 window_size, int flags) {
    s_engine = new (Engine);
    logger::clear();
    logger::logf("### %s %s %s %d (%s) - Built at %s - (%ld, %d) ###\n", ENGINE_NAME, ENGINE_VERSION, ENGINE_BUILD, ENGINE_VERSION_REAL, ENGINE_BUILD_TYPE,
        ENGINE_BUILD_DATE, __cplusplus, __STDCPP_THREADS__);
    logger::logf("Initializing engine... -- (%d)\n", flags);

    s_engine->engine_state = flags;

    if (glfwInit() != GLFW_TRUE) {
        logger::logf("Cannot initialize GLFW.\n");
        return;
    }

    int8_t sample_count = 2;

    if (FLAG_HAS(flags, ENGINE_AA_X2))
        sample_count = 2;
    else if (FLAG_HAS(flags, ENGINE_AA_X4))
        sample_count = 4;
    else if (FLAG_HAS(flags, ENGINE_AA_X8))
        sample_count = 8;

    logger::logf("Creating window.\n");
    window::initialize(title, window_size.x, window_size.y, sample_count);
    logger::logf("Created window!\n");

    if (FLAG_HAS(flags, ENGINE_VSYNC))
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    /*s_engine->main_shader = shader::load(shaders::main_vertex, shaders::main_fragment);
    s_engine->blur_shader = shader::load(shaders::blur_v, shaders::blur_f);*/

    camera::initialize({ 0.f, 0.f }, { (float)window_size.x, (float)window_size.y });
    camera::update_matrices();


    logger::logf("Initializing renderer...\n", flags);
    _vk::_core::initialize(window::get());
    logger::logf("Renderer is initialized.\n", flags);

    logger::logf("Engine is initialized.\n");
}

void engine::update_keyboard_input(double delta_time) {
    if (glfwGetKey(window::get()->handle, GLFW_KEY_W) == GLFW_PRESS)
        camera::move(FORWARD, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_S) == GLFW_PRESS)
        camera::move(BACKWARD, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_A) == GLFW_PRESS)
        camera::move(LEFT, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_D) == GLFW_PRESS)
        camera::move(RIGHT, delta_time);
}

void engine::update_mouse_scroll(double xoffset, double yoffset) {
    camera::get()->zoom -= yoffset * 0.25f;
    camera::get()->zoom = std::max(camera::get()->zoom, 0.25f);
    camera::update_matrices();
}

void engine::update_mouse_input(int button, int action, int mods) {
}

void engine::update_mouse_position(glm::vec2 pos) {
}

void engine::poll() {
    glfwSwapBuffers(window::get()->handle);
    glfwPollEvents();
}

Engine *engine::get() {
    return s_engine;
}