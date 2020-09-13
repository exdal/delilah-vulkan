#include <Windows.h>
#include <game/game.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    game::initialize("Delilah");
    game::run();
    game::deinitialize();
}