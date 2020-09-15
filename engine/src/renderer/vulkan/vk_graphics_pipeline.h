#pragma once
#include "vk_config.h"
#include "vk_core.h"
#include <vulkan/vulkan.h>

namespace _vk::_graphics_pipeline {
    VkPipelineLayout initialize(VulkanCore *core, float min_depth, float max_depth);
}