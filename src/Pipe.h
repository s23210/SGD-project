#pragma once

#include "TextureManager.h"
#include <ctime>
#include <iostream>

class Pipe {
private:
    SDL_Rect srcRect, topRect, bottomRect;
public:
    int pipeWidth;
    int pipeHeight;
    bool isPassed;
    int x, y;

    Pipe();
    void Update();
    void Render(SDL_Renderer* renderer, SDL_Texture* pipeTexture);
    bool HasCollided(SDL_Rect playerRect);
    bool HasPassed(SDL_Rect playerRect);
};