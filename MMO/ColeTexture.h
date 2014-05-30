//
//  ColeTexture.h
//  MMO
//
//  Created by Cole Faust on 12/24/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeTexture__
#define __MMO__ColeTexture__

#include <string>
#include <SDL2/SDL.h>
#include "ColeScene.h"
#include <memory>

class ColeTexture : public ColeScene
{
public:
    ColeTexture();
    ColeTexture(std::string path);
    ColeTexture(SDL_Surface *surface);
    ~ColeTexture();
    void render();
    void render(SDL_Rect clip);
    void render(int x, int y);
    void render(int x, int y, SDL_Rect clip);
    int getWidth();
    int getHeight();
protected:
    SDL_Texture *texture;
    SDL_Rect fullRect;
    int width, height;
};

#endif /* defined(__MMO__ColeTexture__) */
