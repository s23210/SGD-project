#include <string>
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
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                              SDL_WINDOW_RESIZABLE);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            cout << "Window and renderer created!" << endl;
            isRunning = true;
            playerTexture = TextureManager::Texture("assets/bird1.png", renderer);
            backgroundTexture0 = TextureManager::Texture("assets/background1.png", renderer);
            backgroundTexture1 = TextureManager::Texture("assets/background2.png", renderer);
            pipeTexture = TextureManager::Texture("assets/pipe-green.png", renderer);

//            font = TTF_OpenFont("assets/`PressStart2P-Regular.ttf", 24);

            for (int i = 0; i < 3; i++) {
                pipes[i].x = 800 + i * 290;
            }

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

            scoreRect.x = 0;
            scoreRect.y = 0;
            scoreRect.w = 100;
            scoreRect.h = 100;
        } else {
            cout << "Error: " << "renderer not created!" << endl;
        }
    } else {
        cout << "Error: " << "window not created!" << endl;
    }
}

void GameLoop::Gravity() {
    if (getJumpState()) {
        accelerator1 = accelerator1 + 0.035;
        accelerator2 = accelerator2 + 0.035;
        jumpHeight = jumpHeight + gravity;
        yPos = yPos + gravity + accelerator1 + accelerator2 + jumpHeight;
        destPlayer.y = yPos;
        if (jumpHeight > 0) {
            isJumping = false;
            jumpHeight = -7;
        }
    } else {
        accelerator1 = accelerator1 + 0.035;
        accelerator2 = accelerator2 + 0.035;
        yPos = yPos + gravity + accelerator1 + accelerator2;
        destPlayer.y = yPos;
    }
}

bool GameLoop::getJumpState() {
    return isJumping;
}

void GameLoop::Jump() {
    if (jumpTime - lastJump > 80) {
        accelerator1 = 0;
        accelerator2 = 0;
        isJumping = true;
        lastJump = jumpTime;
//        yPos = yPos + jumpHeight;
//        destPlayer.y = yPos;
    } else {
        Gravity();
    }
}

void GameLoop::getJumpTime() {
    jumpTime = SDL_GetTicks();
}

void GameLoop::Event() {
    getJumpTime();
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            cout << "Mouse button down!" << endl;
            if (!getJumpState()) {
                Jump();
            } else {
                Gravity();
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
//                    cout << "Spacebar pressed!" << endl;
                    if (!getJumpState()) {
                        Jump();
                    } else {
                        Gravity();
                    }
                    break;
                case SDLK_UP:
                    cout << "Up arrow pressed!" << endl;
                    if (!getJumpState()) {
                        Jump();
                    } else {
                        Gravity();
                    }
                    break;
                case SDLK_w:
                    cout << "W pressed!" << endl;
                    if (!getJumpState()) {
                        Jump();
                    } else {
                        Gravity();
                    }
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void GameLoop::Update() {
    destBackground1.x -= 2;
    destBackground0.x -= 3;

    if (destBackground0.x <= -800)
        destBackground0.x = 0;

    if (destBackground1.x <= -800)
        destBackground1.x = 0;

    for (auto &pipe: pipes) {
        pipe.Update();
        if (pipe.HasCollided(destPlayer)) {
            isDead = true;
//            isRunning = false;
//            system("Rundll32.exe user32.dll,LockWorkStation"); //funny comment xD
            return;
        }
        if (pipe.HasPassed(destPlayer)) {
            score++;
            // "Score: 0"
//            textSurface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), textColor);
        }
    }
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture1, &srcBackground1, &destBackground1);
    SDL_RenderCopy(renderer, backgroundTexture0, &srcBackground0, &destBackground0);

    if (isDead) {
        //add game over screen
        cout << "Game over!" << endl << "Score: " << score << endl;
        SDL_RenderCopy(renderer, playerTexture, &srcPlayer, &destPlayer);
        //frozen screen
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
        isRunning = false;
    } else {
        for (auto &pipe: pipes) {
            pipe.Render(renderer, pipeTexture);
        }

        SDL_RenderCopy(renderer, playerTexture, &srcPlayer, &destPlayer);
//        SDL_RenderCopy(renderer, textTexture, NULL, &scoreRect);
    }
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
//    SDL_FreeSurface(textSurface);

//    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(backgroundTexture0);
    SDL_DestroyTexture(backgroundTexture1);
    SDL_DestroyTexture(pipeTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}