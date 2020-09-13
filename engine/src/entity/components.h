#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <renderer/renderer.h>
#include <renderer/font/font.h>

//struct VertexData;

struct TextComponent {
    Font *font;
    std::string text;
};

struct TileComponent {
    glm::vec4 tile_info;
    Texture *texture;
};

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 size;
    float z_index;
    float rotation = 0;
};

struct ColorComponent {
    glm::vec4 color;

    operator glm::vec4 &() {
        return color;
    }
};

struct TextureComponent {
    Texture *texture;

    operator Texture *() {
        return texture;
    }
};