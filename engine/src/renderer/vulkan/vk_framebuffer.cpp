#include "vk_framebuffer.h"
#include <utils/logger.h>

void _vk::_framebuffer::initialize(VulkanCore *core) {
    core->framebuffers.resize(core->swap_chain_image_views.size());

    for (size_t i = 0; i < core->swap_chain_image_views.size(); i++) {
        VkImageView attachments[] = { core->swap_chain_image_views[i] };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = core->render_pass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = core->swap_chain_extent.width;
        framebufferInfo.height = core->swap_chain_extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(core->device, &framebufferInfo, nullptr, &core->framebuffers[i]) != VK_SUCCESS) {
            logger::logf("failed to create framebuffer!\n");
        }
    }
}
