#include "GameLoop.h"
GameLoop* g = new GameLoop();

int main(int argc, char* argv[]) {
    g->Initialize();
    while (g->getIsRunning()) {
        g->Render();
        g->Event();
    }
    g->Clear();
    return 0;
}
