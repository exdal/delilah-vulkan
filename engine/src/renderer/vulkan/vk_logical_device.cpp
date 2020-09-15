#include "vk_logical_device.h"
#include "vk_config.h"
#include "vk_core.h"
#include <utils/logger.h>
#include <set>

void _vk::_logical_device::initialize(VulkanCore *core) {
    QueueFamilyIndices indices = _vk::_core::find_queue_families(core->physical_device);

    std::vector<VkDeviceQueueCreateInfo> q_create_info_v;
    std::set<uint32_t> u_queue_families = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (auto queue_family : u_queue_families) {
        VkDeviceQueueCreateInfo q_createinfo{};
        q_createinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        q_createinfo.queueFamilyIndex = queue_family;
        q_createinfo.queueCount = 1;
        q_createinfo.pQueuePriorities = &queuePriority;
        q_create_info_v.push_back(q_createinfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = q_create_info_v.data();
    createInfo.queueCreateInfoCount = q_create_info_v.size();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = device_extensions.size();
    createInfo.ppEnabledExtensionNames = device_extensions.data();

    if (enable_vl) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        createInfo.ppEnabledLayerNames = validation_layers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(core->physical_device, &createInfo, nullptr, &core->device) != VK_SUCCESS) {
        logger::logf("failed to create logical device!");
        return;
    }

    vkGetDeviceQueue(core->device, indices.graphicsFamily.value(), 0, &core->graphics_queue);
    vkGetDeviceQueue(core->device, indices.presentFamily.value(), 0, &core->present_queue);
}
