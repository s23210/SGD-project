#ifndef SGD_PROJECT_GAMELOOP_H
#define SGD_PROJECT_GAMELOOP_H

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include <iostream>
using namespace std;

class GameLoop {
private:
    const int HEIGHT = 640;
    const int WIDTH = 800;
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Texture* playerTexture;
public:
    GameLoop();
    bool getIsRunning();
    void Initialize();
    void Event();
    void Render();
    void Clear();

};

#endif //SGD_PROJECT_GAMELOOP_H
