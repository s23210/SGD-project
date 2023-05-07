#include <string>
#include "GameLoop.h"
GameLoop* g = new GameLoop();

const int TICKS = 10;

int main(int argc, char* argv[]) {
    g->Initialize();
    auto prev_tick = SDL_GetTicks();
    int frame_dropped = 0;
    while (g->getIsRunning()) {
        if (!frame_dropped) {
            g->Render();
            g->Gravity();
            g->Event();
            g->Update();
        }

        auto curr_tick = SDL_GetTicks();

        if (curr_tick - prev_tick < TICKS) {
            SDL_Delay(TICKS - (curr_tick - prev_tick));
            frame_dropped = 0;
        } else {
            frame_dropped = 1;
        }

        prev_tick += TICKS;
    }
    g->Clear();
    return 0;
}
