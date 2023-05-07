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
            backgroundTexture0 = TextureManager::Texture("assets/background1.png", renderer);
            backgroundTexture1 = TextureManager::Texture("assets/background2.png", renderer);

            //source dimensions
            srcPlayer.h = 24;
            srcPlayer.w = 34;
            srcPlayer.x = srcPlayer.y = 0;
            //destination dimensions
            destPlayer.h = 24;
            destPlayer.w = 34;
            destPlayer.x = 10;
            destPlayer.y = 0;

            srcBackground0.h = srcBackground1.h = 640;
            srcBackground0.w = srcBackground1.w = 1600;
            srcBackground0.x = srcBackground0.y = srcBackground1.x = srcBackground1.y = 0;
            destBackground0.h = destBackground1.h = 640;
            destBackground0.w = destBackground1.w = 1600;
            destBackground0.x = destBackground0.y = destBackground1.x = destBackground1.y = 0;
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
                    destPlayer.y -= 50;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void GameLoop::Update() {

    destPlayer.y += 2;

    destBackground1.x -= 2;
    destBackground0.x -= 3;

    if(destBackground0.x <= -800)
        destBackground0.x = 0;

    if(destBackground1.x <= -800)
        destBackground1.x = 0;

    timer++;
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture1, &srcBackground1, &destBackground1);
    SDL_RenderCopy(renderer, backgroundTexture0, &srcBackground0, &destBackground0);

    SDL_RenderCopy(renderer, playerTexture, &srcPlayer, &destPlayer);
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}