#include "renderer.h"
#include <window/window.h>

static Renderer *s_renderer;

void renderer::initialize() {
    s_renderer = new (Renderer);
}

void renderer::set_view(int w, int h) {
    glViewport(0, 0, w, h);
}

void renderer::new_frame() {
    glClearColor(s_renderer->clear_color.x, s_renderer->clear_color.y, s_renderer->clear_color.z, s_renderer->clear_color.w);

    // clear with depth so we can use z-index
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::end_frame() {
    glfwSwapBuffers(window::get()->handle);
}