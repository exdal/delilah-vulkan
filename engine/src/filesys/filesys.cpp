#include "filesys.h"
#include <utils/logger.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t *fsys::get(const char *path, int *sizeout) {
    uint8_t *data = nullptr;

    FILE *f = fopen(path, "rb");
    if (!f)
        return nullptr;

    fseek(f, 0, SEEK_END);
    *sizeout = ftell(f);
    rewind(f);

    data = (uint8_t *)malloc(*sizeout);

    if (!data)
        logger::logf("Out of memory in fs.");

    fread(data, *sizeout, 1, f);
    fclose(f);

    return data;
}

bool fsys::is_exists(const char *path) {
    if (FILE *f = fopen(path, "r")) {
        fclose(f);
        return true;
    } else
        return false;
}
