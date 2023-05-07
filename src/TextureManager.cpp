#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* fileName, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}