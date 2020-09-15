#include "vk_semaphores.h"
#include "vk_config.h"
#include <utils/logger.h>

void _vk::_semaphores::initialize(VulkanCore *core) {
    core->image_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    core->render_finish_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    core->fences.resize(MAX_FRAMES_IN_FLIGHT);
    core->fence_images.resize(core->swap_chain_images.size(), 0);

    VkSemaphoreCreateInfo semaphore_info{};
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info{};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(core->device, &semaphore_info, nullptr, &core->image_semaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(core->device, &semaphore_info, nullptr, &core->render_finish_semaphores[i]) != VK_SUCCESS ||
            vkCreateFence(core->device, &fence_info, nullptr, &core->fences[i]) != VK_SUCCESS) {
            logger::logf("failed to create semaphores!\n");
        }
    }
}
