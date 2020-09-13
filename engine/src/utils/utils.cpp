#include "utils.h"

uint32_t utils::hash_str(uint8_t *str, int len) {
    if (!str)
        return 0;

    unsigned char *n = (unsigned char *)str;
    uint32_t acc = 0x55555555;

    if (len == 0) {
        while (*n)
            acc = (acc >> 27) + (acc << 5) + *n++;
    } else {
        for (int i = 0; i < len; i++) {
            acc = (acc >> 27) + (acc << 5) + *n++;
        }
    }
    return acc;
}
