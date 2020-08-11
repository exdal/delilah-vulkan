#pragma once
#include <cstdint>

namespace fsys {
    uint8_t *get(const char *path, int *sizeout);

    bool is_exists(const char *path);
}