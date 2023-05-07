#ifndef SGD_PROJECT_TEXTUREMANAGER_H
#define SGD_PROJECT_TEXTUREMANAGER_H

#include "GameLoop.h"

class TextureManager {
public:
    static SDL_Texture* Texture(const char* fileName, SDL_Renderer* renderer);
//    static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle);
};

#endif //SGD_PROJECT_TEXTUREMANAGER_H
