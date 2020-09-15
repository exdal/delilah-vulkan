#include "vk_graphics_pipeline.h"
#include "vk_shader.h"
#include <utils/logger.h>

VkPipelineLayout _vk::_graphics_pipeline::initialize(VulkanCore *core, float min_depth, float max_depth) {
    VkPipelineLayout layout;

    VkPipelineShaderStageCreateInfo v_pipeline_shader_info{};
    v_pipeline_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    v_pipeline_shader_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    v_pipeline_shader_info.module = core->vertex_shader;
    v_pipeline_shader_info.pName = "main";

    VkPipelineShaderStageCreateInfo f_pipeline_shader_info{};
    f_pipeline_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    f_pipeline_shader_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    f_pipeline_shader_info.module = core->fragment_shader;
    f_pipeline_shader_info.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { v_pipeline_shader_info, f_pipeline_shader_info };

    VkPipelineVertexInputStateCreateInfo v_input_info{};
    v_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    v_input_info.vertexBindingDescriptionCount = 0;
    v_input_info.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo input_assembly{};
    input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)core->swap_chain_extent.width;
    viewport.height = (float)core->swap_chain_extent.height;
    viewport.minDepth = min_depth;
    viewport.maxDepth = max_depth;

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = core->swap_chain_extent;

    VkPipelineViewportStateCreateInfo viewport_state{};
    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState color_blend_attachment{};
    color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    color_blend_attachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo blending{};
    blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blending.logicOpEnable = VK_FALSE;
    blending.logicOp = VK_LOGIC_OP_COPY;
    blending.attachmentCount = 1;
    blending.pAttachments = &color_blend_attachment;
    blending.blendConstants[0] = 0.0f;
    blending.blendConstants[1] = 0.0f;
    blending.blendConstants[2] = 0.0f;
    blending.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo pip_layout_info{};
    pip_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pip_layout_info.setLayoutCount = 0;
    pip_layout_info.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(core->device, &pip_layout_info, nullptr, &layout) != VK_SUCCESS) {
        logger::logf("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipeline_info{};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shaderStages;
    pipeline_info.pVertexInputState = &v_input_info;
    pipeline_info.pInputAssemblyState = &input_assembly;
    pipeline_info.pViewportState = &viewport_state;
    pipeline_info.pRasterizationState = &rasterizer;
    pipeline_info.pMultisampleState = &multisampling;
    pipeline_info.pColorBlendState = &blending;
    pipeline_info.layout = layout;
    pipeline_info.renderPass = core->render_pass;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(core->device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &core->graphics_pipeline) != VK_SUCCESS) {
        logger::logf("failed to create graphics pipeline!\n");
    }

    return layout;
}
