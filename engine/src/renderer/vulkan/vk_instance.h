#pragma once
#include <vulkan/vulkan.h>

namespace _vk::_instance {
    VkInstance initialize(PFN_vkDebugUtilsMessengerCallbackEXT fun_debug_info);
}