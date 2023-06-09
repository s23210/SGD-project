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
    cout << "Window and renderer created!" << endl;
    TTF_Init();
    cout << "TTF initialized!" << endl;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Error: " << Mix_GetError() << endl;
    } else {
        cout << "Audio initialized!" << endl;
        jumpSound = Mix_LoadWAV("assets/jump.wav");
        hitSound = Mix_LoadWAV("assets/hit.wav");
        pointSound = Mix_LoadWAV("assets/point.wav");
        music = Mix_LoadMUS("assets/music.mp3");
        Mix_VolumeMusic((MIX_MAX_VOLUME * 60) / 100);
        Mix_PlayMusic(music, -1);
        Mix_Volume(-1, (SDL_MIX_MAXVOLUME * 50 ) / 100);

        if (jumpSound == NULL || hitSound == NULL || pointSound == NULL || music == NULL) {
            cout << "Error: " << Mix_GetError() << endl;
        }
    }

    isRunning = true;
    playerTexture = TextureManager::Texture("assets/spritesheet.png", renderer);

    backgroundTexture0 = TextureManager::Texture("assets/background1.png", renderer);
    backgroundTexture1 = TextureManager::Texture("assets/background2.png", renderer);
    pipeTexture = TextureManager::Texture("assets/pipe-green.png", renderer);

    font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 24);
    textSurface = TTF_RenderText_Solid(font, "Score: 0", textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

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

    scoreRect.x = 10;
    scoreRect.y = 10;

    scoreRect.w = textSurface->w;
    scoreRect.h = textSurface->h;
}

void GameLoop::CreateWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            Initialize();
        } else {
            cout << "Error: " << "renderer not created!" << endl;
        }
    } else {
        cout << "Error: " << "window not created!" << endl;
    }
}

void GameLoop::Gravity() {
    if (isDead) {
        return;
    }
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
        if (rotateAngle >= -30)
            rotateAngle = rotateAngle - 0.6;

    } else {
        accelerator1 = accelerator1 + 0.035;
        accelerator2 = accelerator2 + 0.035;
        yPos = yPos + gravity + accelerator1 + accelerator2;
        destPlayer.y = yPos;
        if (rotateAngle <= 45)
            rotateAngle = rotateAngle + 0.4;
    }
}

bool GameLoop::isOutOfBounds() {
    return destPlayer.y < 0 || destPlayer.y > HEIGHT - destPlayer.h || destPlayer.x < 0 ||
           destPlayer.x > WIDTH - destPlayer.w;
}

bool GameLoop::getJumpState() {
    return isJumping;
}

void GameLoop::Jump() {
    if (isDead) {
        return;
    }

    Mix_PlayChannel(-1, jumpSound, 0);

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

void GameLoop::resetGame() {
    yPos = 256;
    destPlayer.y = yPos;
    accelerator1 = 0;
    accelerator2 = 0;
    rotateAngle = 0;
    score = 0;
    isDead = false;
    lastJump = 0;
    isJumping = false;
    jumpTime = 0;
    jumpHeight = -7;
    gravity = 0.5;

    for (int i = 0; i < 3; i++) {
        pipes[i].x = 800 + i * 290;
    }

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    textSurface = TTF_RenderText_Solid(font, "Score: 0", textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void GameLoop::Event() {
    getJumpTime();
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
//            cout << "Mouse button down!" << endl;
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
//                    cout << "Up arrow pressed!" << endl;
                    if (!getJumpState()) {
                        Jump();
                    } else {
                        Gravity();
                    }
                    break;
                case SDLK_w:
//                    cout << "W pressed!" << endl;
                    if (!getJumpState()) {
                        Jump();
                    } else {
                        Gravity();
                    }
                    break;
                    case SDLK_RETURN:
                        resetGame();
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void GameLoop::AnimateBird() {
    Uint32 ticks = SDL_GetTicks();
    Uint32 sprite = (ticks / 100) % 4;
    srcPlayer.x = sprite * 34;

}

void GameLoop::Update() {
    if (isDead) {
        return;
    }

    AnimateBird();

    destBackground1.x -= 2;
    destBackground0.x -= 3;

    if (destBackground0.x <= -800)
        destBackground0.x = 0;

    if (destBackground1.x <= -800)
        destBackground1.x = 0;

    for (auto &pipe: pipes) {
        pipe.Update();
        if (pipe.HasCollided(destPlayer) || isOutOfBounds()) {
            Mix_PlayChannel(-1, hitSound, 0);
            isDead = true;
//            isRunning = false;
//            system("Rundll32.exe user32.dll,LockWorkStation"); //funny comment xD
            return;
        }
        if (pipe.HasPassed(destPlayer)) {
            Mix_PlayChannel(-1, pointSound, 0);
            score++;
            textSurface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            scoreRect.w = textSurface->w;
            scoreRect.h = textSurface->h;
        }
    }
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture1, &srcBackground1, &destBackground1);
    SDL_RenderCopy(renderer, backgroundTexture0, &srcBackground0, &destBackground0);

    SDL_RenderCopyEx(renderer, playerTexture, &srcPlayer, &destPlayer, rotateAngle, NULL, SDL_FLIP_NONE);
    for (auto &pipe: pipes) {
        pipe.Render(renderer, pipeTexture);
    }

    SDL_RenderCopy(renderer, textTexture, NULL, &scoreRect);
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    SDL_FreeSurface(textSurface);

    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(backgroundTexture0);
    SDL_DestroyTexture(backgroundTexture1);
    SDL_DestroyTexture(pipeTexture);

    Mix_FreeChunk(hitSound);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(pointSound);
    Mix_FreeMusic(music);

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}