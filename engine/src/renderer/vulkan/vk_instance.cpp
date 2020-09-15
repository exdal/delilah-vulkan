#include "vk_instance.h"
#include "vk_config.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <utils/logger.h>

static std::vector<const char *> get_required_extensions() {
    uint32_t glfw_extc = 0;
    const char **glfw_ext;
    glfw_ext = glfwGetRequiredInstanceExtensions(&glfw_extc);

    std::vector<const char *> extensions(glfw_ext, glfw_ext + glfw_extc);

    if (enable_vl) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

static bool check_for_vls() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers;
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for (auto name : validation_layers) {
        bool found = false;

        for (const auto &props : available_layers) {
            if (strcmp(name, props.layerName) == 0) {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

VkInstance _vk::_instance::initialize(PFN_vkDebugUtilsMessengerCallbackEXT fun_debug_info) {
    VkInstance instance = nullptr;

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = VK_APP_NAME;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = VK_ENGINE_NAME;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = get_required_extensions();
    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_info{};
    if (enable_vl) {
        createInfo.enabledLayerCount = validation_layers.size();
        createInfo.ppEnabledLayerNames = validation_layers.data();

        debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT; // what the fuck
        debug_info.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_info.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_info.pfnUserCallback = fun_debug_info;

        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_info;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        logger::logf("[ERROR]: Cannot create VKINST\n");
        return nullptr;
    }
    return instance;
}
