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
    int timer = 0;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    SDL_Texture* playerTexture;
    SDL_Texture* backgroundTexture0;
    SDL_Texture* backgroundTexture1;

    SDL_Rect srcPlayer, destPlayer;
    SDL_Rect srcBackground0, destBackground0;
    SDL_Rect srcBackground1, destBackground1;

public:
    GameLoop();
    bool getIsRunning();
    void Update();
    void Initialize();
    void Event();
    void Render();
    void Clear();

};

#endif //SGD_PROJECT_GAMELOOP_H
