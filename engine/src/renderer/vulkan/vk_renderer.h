#pragma once
#include "vk_core.h"

struct VulkanRenderer {
    uint32_t current_frame = 0;
};

namespace renderer {
    void initialize();
    void draw_frame();
}