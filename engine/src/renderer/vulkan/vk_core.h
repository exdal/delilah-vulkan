#pragma once
#include <optional>
#include <vulkan/vulkan.h>
#include <window/window.h>
#include <vector>

struct VulkanCore {
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swap_chain;

    std::vector<VkImage> swap_chain_images;
    std::vector<VkImageView> swap_chain_image_views;

    VkFormat swap_chain_image_format;
    VkExtent2D swap_chain_extent;

    VkShaderModule vertex_shader;
    VkShaderModule fragment_shader;

    VkPipelineLayout pipeline_layout;
    VkRenderPass render_pass;
    VkPipeline graphics_pipeline = nullptr;

    std::vector<VkFramebuffer> framebuffers;

    VkCommandPool command_pool;
    std::vector<VkCommandBuffer> command_buffers;

    VkSemaphore image_semp;
    VkSemaphore render_finished_semp;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

namespace _vk::_core {
    void initialize(Window *window);
    void init_surface(Window *window);
    void init_image_views();

    bool check_device_ext_support(VkPhysicalDevice device);
    bool is_suitable_device(VkPhysicalDevice device);
    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);

    VulkanCore *get();
}