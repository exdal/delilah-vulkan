#include "vk_swap_chain.h"
#include <algorithm>
#include <utils/logger.h>

void _vk::_swap_chain::initialize(VulkanCore *core) {
    VulkanSwapChain vsc = query_swap_chain(core->physical_device, core->surface);

    auto image_count = vsc.capabilities.minImageCount + 1;
    if (vsc.capabilities.maxImageCount > 0 && image_count > vsc.capabilities.maxImageCount) {
        image_count = vsc.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = core->surface;

    VkSurfaceFormatKHR surface_format = _vk::_swap_chain::get_swap_surface_format(vsc.formats);
    VkExtent2D extent = _vk::_swap_chain::get_swap_extent(vsc.capabilities, window::get()->width, window::get()->height);

    core->swap_chain_extent = extent;
    core->swap_chain_image_format = surface_format.format;

    createInfo.minImageCount = image_count;
    createInfo.imageFormat = surface_format.format;
    createInfo.imageColorSpace = surface_format.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = _vk::_core::find_queue_families(core->physical_device);
    uint32_t family_indices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = family_indices;
    } else
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

    createInfo.preTransform = vsc.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = _vk::_swap_chain::get_swap_present_mode(vsc.present_modes);
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(core->device, &createInfo, nullptr, &core->swap_chain) != VK_SUCCESS) {
        logger::logf("failed to create swap chain!\n");
        return;
    }

    vkGetSwapchainImagesKHR(core->device, core->swap_chain, &image_count, nullptr);
    core->swap_chain_images.resize(image_count);
    vkGetSwapchainImagesKHR(core->device, core->swap_chain, &image_count, core->swap_chain_images.data());
}

VulkanSwapChain _vk::_swap_chain::query_swap_chain(VkPhysicalDevice device, VkSurfaceKHR surface) {
    VulkanSwapChain vsc;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &vsc.capabilities);

    // formats
    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
    if (format_count) {
        vsc.formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, vsc.formats.data());
    }

    // present modes
    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);
    if (present_mode_count) {
        vsc.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, vsc.present_modes.data());
    }

    return vsc;
}

VkSurfaceFormatKHR _vk::_swap_chain::get_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &formats) {
    for (const auto &format : formats) {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return format;
    }
    return formats[0];
}

VkPresentModeKHR _vk::_swap_chain::get_swap_present_mode(const std::vector<VkPresentModeKHR> &present_modes) {
    for (const auto &mode : present_modes) {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return mode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D _vk::_swap_chain::get_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, uint32_t width, uint32_t height) {
    if (capabilities.currentExtent.width != UINT32_MAX)
        return capabilities.currentExtent;
    else {
        VkExtent2D extend = { width, height };

        extend.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, extend.width));
        extend.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, extend.height));

        return extend;
    }
}
