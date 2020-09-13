#include "engine.h"
#include <renderer/renderer.h>
#include <renderer/camera/camera.h>
#include <utils/logger.h>
#include <window/window.h>

#define FLAG_HAS(en, flag) (en & flag)

static Engine *s_engine;

bool engine::initialize(Window *window, int flags) {
    s_engine = new (Engine);
    logger::logf("### %s %s %s %d (%s) - Built at %s - (%ld, %d) ###\n", ENGINE_NAME, ENGINE_VERSION, ENGINE_BUILD, ENGINE_VERSION_REAL, ENGINE_BUILD_TYPE,
        ENGINE_BUILD_DATE, __cplusplus, __STDCPP_THREADS__);
    logger::logf("Initializing engine... -- (%d)\n", flags);

    s_engine->engine_state = flags;

    int8_t sample_count = 0;

    if (FLAG_HAS(flags, ENGINE_AA_X0))
        sample_count = 0;
    else if (FLAG_HAS(flags, ENGINE_AA_X2))
        sample_count = 2;
    else if (FLAG_HAS(flags, ENGINE_AA_X4))
        sample_count = 4;
    else if (FLAG_HAS(flags, ENGINE_AA_X8))
        sample_count = 8;

    /*if (FLAG_HAS(flags, ENGINE_VSYNC))
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    if (sample_count > 0)
        glEnable(GL_MULTISAMPLE);

    // alpha channel flag
    if (FLAG_HAS(flags, ENGINE_BLEND)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_GREATER);
    //glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    
    s_engine->main_shader = shader::load(shaders::main_vertex, shaders::main_fragment);
    s_engine->blur_shader = shader::load(shaders::blur_v, shaders::blur_f);
    */
    camera::initialize({ 0.f, 0.f }, { (float)window->width, (float)window->height });
    camera::update_matrices();

    logger::logf("Initializing renderer...\n", flags);
#if ENGINE_DX11
    if (!renderer::initialize(window->hWnd, window->width, window->height, window->windowed)) {
        logger::logf("Cannot initialize renderer.\n", flags);
        return false;
    }
#elif ENGINE_VULKAN
    if (!renderer::initialize(window->width, window->height, window->windowed)) {
        logger::logf("Cannot initialize renderer.\n", flags);
        return false;
    }
#endif // ENGINE_DX11

    
    logger::logf("Renderer is initialized.\n", flags);

    logger::logf("Engine is initialized.\n");
    return true;
}

void engine::update_keyboard_input(double delta_time) {
    /*if (glfwGetKey(window::get()->handle, GLFW_KEY_W) == GLFW_PRESS)
        camera::move(FORWARD, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_S) == GLFW_PRESS)
        camera::move(BACKWARD, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_A) == GLFW_PRESS)
        camera::move(LEFT, delta_time);
    if (glfwGetKey(window::get()->handle, GLFW_KEY_D) == GLFW_PRESS)
        camera::move(RIGHT, delta_time);*/
}

void engine::update_mouse_scroll(double xoffset, double yoffset) {
}

void engine::update_mouse_input(int button, int action, int mods) {
}

void engine::update_mouse_position(glm::vec2 pos) {
}

void engine::poll() {
#if ENGINE_VULKAN
    glfwSwapBuffers(window::get()->handle);
    glfwPollEvents();
#endif
}

Engine *engine::get() {
    return s_engine;
}