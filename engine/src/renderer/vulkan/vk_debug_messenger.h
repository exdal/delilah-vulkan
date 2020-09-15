#pragma once
#include <vulkan/vulkan.h>

namespace _vk::_debug_message {
    void initialize(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, PFN_vkDebugUtilsMessengerCallbackEXT fun_debug_info);
}