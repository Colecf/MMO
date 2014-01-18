//
//  ColeTexture.h
//  MMO
//
//  Created by Cole Faust on 12/24/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeTexture__
#define __MMO__ColeTexture__

#include <iostream>
#include <SDL2/SDL.h>

class ColeTexture
{
public:
    ColeTexture(std::string path);
    ~ColeTexture();
    void render(int x, int y);
    void render(int x, int y, SDL_Rect clip);
protected:
    SDL_Texture *texture;
    SDL_Rect fullRect;
    int width, height;
};

#endif /* defined(__MMO__ColeTexture__) */
