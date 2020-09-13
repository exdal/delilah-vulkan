#pragma once
#include <glm/glm.hpp>
#include <entt.hpp>
#include <vector>

struct Entity;
struct FrameBuffer;
struct Scene {
    Scene(){};
    virtual void initialize() = 0;
    virtual void deinitialize() = 0;
    virtual void update() = 0;

    virtual void on_mouse_down(int button, int action, int mods) = 0;
    virtual void on_mouse_pos_update(double xpos, double ypos) = 0;

    entt::registry registry;
    std::vector<Entity *> entities;
    std::vector<Entity *> text_entities;
};

namespace scene {
    template <class T>
    T *create() {
        auto scene = new (T);

        scene->registry.create();
        return scene;
    }

    void render(Scene *scene);
}