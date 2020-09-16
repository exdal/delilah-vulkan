#include "vk_core.h"
#include "vk_instance.h"
#include "vk_debug_messenger.h"
#include "vk_physical_device.h"
#include "vk_logical_device.h"
#include "vk_swap_chain.h"
#include "vk_shader.h"
#include "vk_graphics_pipeline.h"
#include "vk_render_pass.h"
#include "vk_framebuffer.h"
#include "vk_command_pool.h"
#include "vk_semaphores.h"
#include <vector>
#include <utils/logger.h>
#include <vulkan/vulkan.h>
#include <string>
#include <set>

static VulkanCore *s_core;

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
    logger::logf("[ERROR]: %s\n", pCallbackData->pMessage);
    return VK_FALSE;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void _vk::_core::initialize(Window *window) {
    s_core = new (VulkanCore);

    s_core->instance = _vk::_instance::initialize(debug_callback);
    _vk::_debug_message::initialize(s_core->instance, s_core->debug_messenger, debug_callback);

    init_surface(window);

    s_core->physical_device = _vk::_physical_device::initialize(s_core->instance);
    _vk::_logical_device::initialize(s_core);

    // create the swap chain

    _vk::_swap_chain::initialize(s_core);

    // create image views

    init_image_views();

    // init render pass

    _vk::_render_pass::initialize(s_core);

    // init shaders & pipielines

    s_core->vertex_shader = _vk::_shader::initialize_module(s_core->device, "res/shaders/v.spv");
    s_core->fragment_shader = _vk::_shader::initialize_module(s_core->device, "res/shaders/f.spv");
    
    s_core->pipeline_layout = _vk::_graphics_pipeline::initialize(s_core, 0, 1.f);

    /*vkDestroyShaderModule(s_core->device, s_core->vertex_shader, nullptr);
    vkDestroyShaderModule(s_core->device, s_core->fragment_shader, nullptr);*/

    // create frame buffers

    _vk::_framebuffer::initialize(s_core);

    // create command pools

    _vk::_command_pool::initialize(s_core);

    // create idk

    _vk::_semaphores::initialize(s_core);
}

void _vk::_core::clean() {
    _vk::_swap_chain::clean(s_core);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(s_core->device, s_core->render_finish_semaphores[i], nullptr);
        vkDestroySemaphore(s_core->device, s_core->image_semaphores[i], nullptr);
        vkDestroyFence(s_core->device, s_core->fences[i], nullptr);
    }

    vkDestroyCommandPool(s_core->device, s_core->command_pool, nullptr);

    vkDestroyDevice(s_core->device, nullptr);

    if (enable_vl) {
        DestroyDebugUtilsMessengerEXT(s_core->instance, s_core->debug_messenger, nullptr);
    }

    vkDestroySurfaceKHR(s_core->instance, s_core->surface, nullptr);
    vkDestroyInstance(s_core->instance, nullptr);
}

void _vk::_core::resize() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window::get()->handle, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window::get()->handle, &width, &height);
        glfwWaitEvents();
    }

    _vk::_swap_chain::recreate(s_core);
    init_image_views();
    _vk::_render_pass::initialize(s_core);
    s_core->pipeline_layout = _vk::_graphics_pipeline::initialize(s_core, 0, 1.f);
    _vk::_framebuffer::initialize(s_core);
    _vk::_command_pool::initialize(s_core);
}

void _vk::_core::init_surface(Window *window) {
    if (glfwCreateWindowSurface(s_core->instance, window->handle, nullptr, &s_core->surface) != VK_SUCCESS) {
        logger::logf("Failed to create VKSURFACEKHR\n");
    }
}

void _vk::_core::init_image_views() {
    s_core->swap_chain_image_views.resize(s_core->swap_chain_images.size());
    for (size_t i = 0; i < s_core->swap_chain_images.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = s_core->swap_chain_images[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = s_core->swap_chain_image_format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(s_core->device, &createInfo, nullptr, &s_core->swap_chain_image_views[i]) != VK_SUCCESS) {
            logger::logf("failed to create image views!\n");
        }
    }
}

bool _vk::_core::check_device_ext_support(VkPhysicalDevice device) {
    uint32_t count = 0;

    vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);
    std::vector<VkExtensionProperties> available_props(count);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &count, available_props.data());

    std::set<std::string> req_ext(device_extensions.begin(), device_extensions.end());
    for (const auto &prop : available_props) {
        req_ext.erase(prop.extensionName);
    }

    return req_ext.empty();
}

bool _vk::_core::is_suitable_device(VkPhysicalDevice device) {
    QueueFamilyIndices indices = find_queue_families(device);

    bool ext_ok = check_device_ext_support(device);
    bool swap_chain_adequate = false;

    if (ext_ok) {
        VulkanSwapChain vsc = _vk::_swap_chain::query_swap_chain(device, s_core->surface);
        swap_chain_adequate = !vsc.formats.empty() && !vsc.present_modes.empty();
    }

    return indices.isComplete() && ext_ok && swap_chain_adequate;
}

QueueFamilyIndices _vk::_core::find_queue_families(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    uint32_t count = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
    std::vector<VkQueueFamilyProperties> families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());

    int i = 0;
    for (const auto &family : families) {
        if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, s_core->surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }

    return indices;
}

VulkanCore *_vk::_core::get() {
    return s_core;
}
