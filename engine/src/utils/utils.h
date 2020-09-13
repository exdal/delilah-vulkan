#pragma once
#include <string>

#define CHECK_SET(x, y) \
    if (x)              \
    x->y
#define SAFE_RELEASE(var) \
    if (var) {            \
        var->Release();   \
        var = nullptr;    \
    }                     \

#define RGBA(r, g, b, a) \
    { (float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f }


namespace utils {
    template <typename T>
    static void serialize(uint8_t *&data, T *val) {
        memcpy(val, data, sizeof(T));
        data += sizeof(T);
    }

    static void serialize_str(uint8_t *&data, std::string &str) {
        str.assign((const char *)(data + 2), *(uint16_t *)data);
        data += 2 + str.length();
    }

    uint32_t hash_str(uint8_t *str, int len);
} // namespace utils