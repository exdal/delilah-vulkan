#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

struct VKRenderer {
    VkInstance instance = nullptr;
    VkDevice device = nullptr;
    VkPhysicalDevice gpu = nullptr;
    VkPhysicalDeviceProperties gpu_props;

    uint32_t graphics_family_index = 0;

    std::vector<const char *> instance_layers;
    std::vector<const char *> instance_extensions;
    std::vector<const char *> device_extensions;

    VkDebugReportCallbackEXT debug_report;
    VkDebugReportCallbackCreateInfoEXT debug_callback_create_info = {};

    bool msaa = false;
    int32_t msaa_count;
    uint32_t msaa_quality;
    bool windowed;
};

namespace vkrenderer {
    bool initialize(int width, int height, bool windowed);
    void shutdown();
    void resize(int width, int height);
    void clear(const glm::vec4 &color);
    void present(int32_t syncInterval = 0, int32_t presentFlag = 0);
} // namespace dx11renderer