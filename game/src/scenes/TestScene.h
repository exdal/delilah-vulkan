#pragma once
#include <renderer/scene/scene.h>
#include <array>

struct Font;
struct Texture;
struct FrameBuffer;
struct TestScene : Scene {
    void initialize() override;
    void deinitialize() override;
    void update() override;
    void on_mouse_down(int button, int action, int mods) override;
    void on_mouse_pos_update(double xpos, double ypos) override;
    Texture *texture;
};