#include "vk_config.h"
#include "vk_renderer.h"
#include <utils/logger.h>
#include <stdexcept>

static VulkanRenderer *s_renderer;

void renderer::initialize() {
    s_renderer = new (VulkanRenderer);
}

void renderer::draw_frame() {
    VulkanCore *core = _vk::_core::get();

    vkWaitForFences(core->device, 1, &core->fences[s_renderer->current_frame], VK_TRUE, UINT64_MAX);

    uint32_t image_index = 0;
    VkResult result = vkAcquireNextImageKHR(core->device, core->swap_chain, UINT64_MAX, core->image_semaphores[s_renderer->current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        _vk::_core::resize();
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("failed to acquire swap chain image!");

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (core->fence_images[image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(core->device, 1, &core->fence_images[image_index], VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    core->fence_images[image_index] = core->fences[s_renderer->current_frame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { core->image_semaphores[s_renderer->current_frame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &core->command_buffers[image_index];

    VkSemaphore signalSemaphores[] = { core->render_finish_semaphores[s_renderer->current_frame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(core->device, 1, &core->fences[s_renderer->current_frame]);

    if (vkQueueSubmit(core->graphics_queue, 1, &submitInfo, core->fences[s_renderer->current_frame]) != VK_SUCCESS) {
        logger::logf("failed to submit draw command buffer!\n");
        return;
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { core->swap_chain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &image_index;
    presentInfo.pResults = nullptr;

    vkQueueWaitIdle(core->graphics_queue);

    result = vkQueuePresentKHR(core->present_queue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _vk::_core::get()->resized) {
        _vk::_core::get()->resized = false;
        _vk::_core::resize();
    }
    else if (result != VK_SUCCESS)
        throw std::runtime_error("failed to present swap chain image!");

    vkQueueWaitIdle(core->present_queue);
    s_renderer->current_frame = (s_renderer->current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
