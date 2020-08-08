#include "engine.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define FLAG_HAS(en, flag) (en &= flag == flag)

Engine::Engine(const char *title, glm::vec2 window_size, int flags) {
    if (glfwInit() != GLFW_TRUE) {
        //logger::logf("Cannot initialize GLFW.\n");
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

    m_window = new Window(title, window_size.x, window_size.y, sample_count);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // error
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
}

void Engine::poll() {
    glfwPollEvents();
}
