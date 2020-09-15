#pragma once
#include "vk_config.h"
#include <vulkan/vulkan.h>

namespace _vk::_physical_device {
    VkPhysicalDevice initialize(VkInstance instance);
}
