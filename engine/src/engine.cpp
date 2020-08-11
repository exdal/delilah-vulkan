#include "engine.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <renderer/renderer.h>
#include <renderer/camera/camera.h>
#include <utils/logger.h>

#define FLAG_HAS(en, flag) (en &= flag == flag)

static Engine *s_engine;

void engine::initialize(const char *title, glm::vec2 window_size, int flags) {
    s_engine = new (Engine);
    logger::clear();
    logger::logf("Initializing engine... -- (%d)\n", flags);

    if (glfwInit() != GLFW_TRUE) {
        logger::logf("Cannot initialize GLFW.\n");
        return;
    }

    int8_t sample_count = 0;

    if (FLAG_HAS(flags, ENGINE_AA_X0))
        sample_count = 0;
    else if (FLAG_HAS(flags, ENGINE_AA_X2))
        sample_count = 2;
    else if (FLAG_HAS(flags, ENGINE_AA_X4))
        sample_count = 4;
    else if (FLAG_HAS(flags, ENGINE_AA_X8))
        sample_count = 8;

    logger::logf("Creating window.\n");
    window::initialize(title, window_size.x, window_size.y, sample_count);
    logger::logf("Created window!\n");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logger::logf("Cannot initialize GLAD.\n");
        return;
    }

    if (FLAG_HAS(flags, ENGINE_VSYNC))
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

    s_engine->main_shader = shader::load("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

    camera::initialize({ 0.f, 0.f }, { (float)window_size.x, (float)window_size.y });
    camera::update_matrices();

    renderer::set_view(window_size.x, window_size.y);
    logger::logf("a last error: %d\n", glGetError());
    logger::logf("Initializing renderer...\n", flags);
    renderer::initialize();
    logger::logf("Renderer is initialized.\n", flags);

    shader::use(s_engine->main_shader);
    shader::set_int(s_engine->main_shader, "u_texture", 0);

    logger::logf("Engine is initialized.\n");
}

void engine::update_mouse_input(int button, int action, int mods) {
}

void engine::poll() {
    glfwPollEvents();
}

Engine *engine::get() {
    return s_engine;
}