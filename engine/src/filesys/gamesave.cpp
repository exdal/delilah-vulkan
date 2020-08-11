#include "gamesave.h"
#include "filesys.h"
#include <utils/logger.h>
#include <stdio.h>

void gamesave::write(GameSave save, const char *path) {
    logger::logf("Saving current state of the game and engine...\n");
    FILE *f = fopen(path, "wb");
    fwrite(&save, sizeof(GameSave), 1, f);
    fclose(f);
    logger::logf("Current state is saved.\n");
}

GameSave gamesave::load(const char *path) {
    int size;   
    return *(GameSave*)fsys::get(path, &size); 
}
