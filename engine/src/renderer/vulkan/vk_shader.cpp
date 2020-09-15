#include "vk_shader.h"
#include <utils/logger.h>
#include <filesys/filesys.h>

VkShaderModule _vk::_shader::initialize_module(VkDevice device, const char *path) {
    int size = 0;
    uint8_t *data = fsys::get(path, &size);

    if (!data)
        return 0;

    VkShaderModule shaderModule;

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = (const uint32_t *)data;

    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        logger::logf("failed to create shader module!\n");
    }

    return shaderModule;
}