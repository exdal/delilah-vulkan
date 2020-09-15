#pragma once
#include <vulkan/vulkan.h>

namespace _vk::_shader {
    VkShaderModule initialize_module(VkDevice device, const char* path);
}