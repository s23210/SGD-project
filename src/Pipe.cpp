#include "Pipe.h"

const int GAP = 150;

Pipe::Pipe() {
    pipeWidth = 80;
    pipeHeight = 440;
    isPassed = false;
     y = (rand() % 12) * 20 + 200;

    srcRect = {0, 0, 125, 500};
    topRect = {x, y - pipeHeight - GAP, pipeWidth, pipeHeight};
    bottomRect = {x, y, pipeWidth, pipeHeight};
}

void Pipe::Update() {
    x = x - 2;
    if (x < -pipeWidth) {
        x = 800;
        // from 200 to 440
        // 12 * 20 = 240
        // 240 + 200 = 440
        y = (rand() % 12) * 20 + 200;
        isPassed = false;
    }
    topRect = {x, y - pipeHeight - GAP, pipeWidth, pipeHeight};
    bottomRect = {x, y, pipeWidth, pipeHeight};
}

bool Pipe::HasCollided(SDL_Rect playerRect) {
    return SDL_HasIntersection(&playerRect, &topRect) || SDL_HasIntersection(&playerRect, &bottomRect);
}

bool Pipe::HasPassed(SDL_Rect playerRect) {
    if (playerRect.x > x + pipeWidth && !isPassed) {
        isPassed = true;
        return true;
    }
    return false;
}

void Pipe::Render(SDL_Renderer *renderer, SDL_Texture *pipeTexture) {
    SDL_RenderCopy(renderer, pipeTexture, &srcRect, &bottomRect);
    SDL_RenderCopyEx(renderer, pipeTexture, &srcRect, &topRect, 0, nullptr, SDL_FLIP_VERTICAL);
}