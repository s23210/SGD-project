#pragma once

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Pipe.h"
#include <iostream>
using namespace std;

class GameLoop {
private:
    const int HEIGHT = 640;
    const int WIDTH = 800;
    bool isRunning;

    int score = 0;
    double gravity = 0.5;
    int yPos = 256;
    double accelerator1 = 0;
    double accelerator2 = 0;
    bool isDead = false;
    bool isJumping = false;
    double jumpHeight = -7;
    double jumpTime = 0;
    double lastJump = 0;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

//    TTF_Font* font;
//    SDL_Color textColor = { 255, 255, 255 };
//    SDL_Surface* textSurface;

    SDL_Texture* playerTexture;
    SDL_Texture* backgroundTexture0;
    SDL_Texture* backgroundTexture1;
    SDL_Texture* pipeTexture;
//    SDL_Texture* textTexture;

    SDL_Rect srcPlayer, destPlayer;
    SDL_Rect srcBackground0, destBackground0;
    SDL_Rect srcBackground1, destBackground1;
    SDL_Rect scoreRect;

    Pipe pipes[3];

public:
    GameLoop();
    void Gravity();
    void Jump();
    bool getJumpState();
    void getJumpTime();
    bool getIsRunning();
    void Update();
    void Initialize();
    void Event();
    void Render();
    void Clear();
};

