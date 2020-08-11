#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

enum WrappingStyle { 
    REPEAT = GL_REPEAT, 
    MIRRORED = GL_MIRRORED_REPEAT, 
    TO_EDGE = GL_CLAMP_TO_EDGE, 
    TO_BORDER = GL_CLAMP_TO_BORDER 
};

struct Texture {
    int32_t width;
    int32_t height;
    uint32_t id;
    uint32_t internal_format;
    uint32_t data_format;
};

namespace texture {
    Texture *create(const char *file, bool nearest = true, WrappingStyle wrap = REPEAT);
    Texture *create(uint32_t width, uint32_t height, bool nearest = true, uint32_t wrap = GL_REPEAT, uint32_t internal_format = GL_RGBA8, uint32_t data_format = GL_RGBA);
    void bind(Texture *texture, uint32_t slot = 0);
    void set_data(Texture *texture, void *data);
}