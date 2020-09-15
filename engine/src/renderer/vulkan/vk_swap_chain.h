#pragma once
#include "vk_config.h"
#include "vk_core.h"

struct VulkanSwapChain {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

namespace _vk::_swap_chain {
    void initialize(VulkanCore *core);
    VulkanSwapChain query_swap_chain(VkPhysicalDevice device, VkSurfaceKHR surface);
    VkSurfaceFormatKHR get_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &formats);
    VkPresentModeKHR get_swap_present_mode(const std::vector<VkPresentModeKHR> &present_modes);
    VkExtent2D get_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, uint32_t width, uint32_t height);
}