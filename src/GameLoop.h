#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Pipe.h"
#include <iostream>
#include <string>
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
    double rotateAngle = 0.0;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    Mix_Chunk* jumpSound; //copyright by original flappy bird
    Mix_Chunk* hitSound; //copyright by original flappy bird
    Mix_Chunk* pointSound; //copyright by original flappy bird

    Mix_Music* music; //music from yt: (https://www.youtube.com/watch?v=8YHZOIna15Y)

    TTF_Font* font; // font from fonts.google: https://fonts.google.com/specimen/Press+Start+2P
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface;

    SDL_Texture* playerTexture; //copyright by original flappy bird
    SDL_Texture* backgroundTexture0; //original texture by flappy bird remade for parallax
    SDL_Texture* backgroundTexture1; //original texture by flappy bird remade for parallax
    SDL_Texture* pipeTexture; //copyright by original flappy bird
    SDL_Texture* textTexture;

    SDL_Rect srcPlayer, destPlayer;
    SDL_Rect srcBackground0, destBackground0;
    SDL_Rect srcBackground1, destBackground1;
    SDL_Rect scoreRect;

    Pipe pipes[3];

public:
    GameLoop();
    bool isOutOfBounds();
    void Gravity();
    void Jump();
    bool getJumpState();
    void getJumpTime();
    bool getIsRunning();
    void Update();
    void AnimateBird();
    void Initialize();
    void CreateWindow();
    void Event();
    void Render();
    void Clear();
    void resetGame();
};

