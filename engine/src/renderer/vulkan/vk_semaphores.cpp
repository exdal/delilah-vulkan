#include "vk_semaphores.h"
#include <utils/logger.h>

void _vk::_semaphores::initialize(VulkanCore *core) {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(core->device, &semaphoreInfo, nullptr, &core->image_semp) != VK_SUCCESS ||
        vkCreateSemaphore(core->device, &semaphoreInfo, nullptr, &core->render_finished_semp) != VK_SUCCESS) {
        logger::logf("failed to create semaphores!\n");
    }
}
