#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#ifndef VK_APP_NAME
#define VK_APP_NAME "Delilah Application"
#endif

#ifndef VK_ENGINE_NAME
#define VK_ENGINE_NAME "Delilah Engine"
#endif

// Validation Layer Support

static const std::vector<const char *> validation_layers = { "VK_LAYER_KHRONOS_validation" };
static const std::vector<const char *> device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

#ifdef NDEBUG
static const bool enable_vl = false;
#else
static const bool enable_vl = true;
#endif