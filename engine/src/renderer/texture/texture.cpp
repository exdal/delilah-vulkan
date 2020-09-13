/*#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 

#include "texture.h"
#include <utils/logger.h>

Texture *texture::create(const char *file, bool nearest, WrappingStyle wrap) {
    auto texture = new (Texture);
    int32_t nrc; // nr channels, we use this to detect image's data/internal format

    stbi_set_flip_vertically_on_load(true); // flipping our texture cause opengl

    uint8_t *image_data = stbi_load(file, &texture->width, &texture->height, &nrc, 4);

    if (!image_data) {
        logger::logf("Cannot load image %s\n", file);
        return nullptr;
    }

    if (nrc == 4) { // image supports ALPHA
        texture->internal_format = GL_RGBA8;
        texture->data_format = GL_RGBA;
    } else if (nrc == 3) { // image doesn't support ALPHA
        texture->internal_format = GL_RGB8;
        texture->data_format = GL_RGB;
    } else {
        logger::logf("Unknown image type detected: %d\n", nrc);
        return nullptr;
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    uint32_t wrap_type = (uint32_t)wrap;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);

    uint32_t filter_type = (nearest) ? GL_NEAREST : GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type);

    texture::set_data(texture, image_data);
    stbi_image_free(image_data);

    logger::logf("Successfully created texture %s - %d, %d.\n", file, texture->id, glGetError());

    return texture;
}

Texture *texture::create(uint32_t width, uint32_t height, bool nearest, uint32_t wrap, uint32_t internal_format, uint32_t data_format) {
    auto texture = new (Texture);
    
    texture->internal_format = internal_format;
    texture->data_format = data_format;
    texture->width = width;
    texture->height = height; 

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (nearest) ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (nearest) ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    logger::logf("Successfully created texture - %d, %d.\n", texture->id, glGetError());
    return texture;
}

void texture::bind(Texture *texture, uint32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void texture::set_data(Texture *texture, void *data) {
    glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_format, texture->width, texture->height, 0, texture->data_format, GL_UNSIGNED_BYTE, data);
}
*/