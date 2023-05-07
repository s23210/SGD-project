#include "GameLoop.h"

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    isRunning = false;
}

bool GameLoop::getIsRunning() {
    return isRunning;
}

void GameLoop::Initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            cout << "Window and renderer created!" << endl;
            isRunning = true;
            playerTexture = TextureManager::Texture("assets/bird1.png", renderer);
        } else {
            cout << "Error: " << "renderer not created!" << endl;
        }
    } else {
        cout << "Error: " << "window not created!" << endl;
    }
}

void GameLoop::Event() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            cout << "Mouse button down!" << endl;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    cout << "Spacebar pressed!" << endl;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}