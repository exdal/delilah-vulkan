#include "vk_physical_device.h"
#include "vk_core.h"
#include <utils/logger.h>

VkPhysicalDevice _vk::_physical_device::initialize(VkInstance instance) {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

    if (!device_count) {
        logger::logf("GPU doesn't support vulkan\n");
        return VK_NULL_HANDLE;
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    for (const auto &device : devices) {
        if (_vk::_core::is_suitable_device(device)) {
            return device;
        }
    }

    return VK_NULL_HANDLE;
}
