#pragma once
#include <cstdint>

struct GameSave {
    uint8_t engine_state;
};

namespace gamesave {
    void write(GameSave save, const char *path);
    GameSave load(const char *path);
}