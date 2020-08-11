#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

void logger::clear() {
    FILE *f = fopen("log.txt", "w");
    fclose(f);
}

void logger::logf(const char *output, ...) {
    FILE *f = fopen("log.txt", "a");

    va_list args;
    va_start(args, output);
    vfprintf(f, output, args);
    va_end(args);

    fclose(f);
}
