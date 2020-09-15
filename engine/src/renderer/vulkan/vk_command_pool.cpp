#include "vk_command_pool.h"
#include <utils/logger.h>

void _vk::_command_pool::initialize(VulkanCore *core) {
    QueueFamilyIndices queueFamilyIndices = _vk::_core::find_queue_families(core->physical_device);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(core->device, &poolInfo, nullptr, &core->command_pool) != VK_SUCCESS) {
        logger::logf("failed to create command pool!\n");
    }

    core->command_buffers.resize(core->framebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = core->command_pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = core->command_buffers.size();

    if (vkAllocateCommandBuffers(core->device, &allocInfo, core->command_buffers.data()) != VK_SUCCESS) {
        logger::logf("failed to allocate command buffers!\n");
    }

    for (size_t i = 0; i < core->command_buffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(core->command_buffers[i], &beginInfo) != VK_SUCCESS) {
            logger::logf("failed to begin recording command buffer!\n");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = core->render_pass;
        renderPassInfo.framebuffer = core->framebuffers[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = core->swap_chain_extent;

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(core->command_buffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(core->command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, core->graphics_pipeline);

        vkCmdDraw(core->command_buffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(core->command_buffers[i]);

        if (vkEndCommandBuffer(core->command_buffers[i]) != VK_SUCCESS) {
            logger::logf("failed to record command buffer!\n");
        }
    }
}
