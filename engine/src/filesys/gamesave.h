#pragma once
#include <cstdint>

// pack it to 1 bytes each so we dont have to add paddings
#pragma pack(push, 1)
struct GameSave {
    uint8_t engine_state;
    int32_t refresh_rt;
};
#pragma pack(pop)

namespace gamesave {
    void write(GameSave save, const char *path);
    GameSave load(const char *path);
}