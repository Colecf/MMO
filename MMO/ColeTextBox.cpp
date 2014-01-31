//
//  ColeTextBox.cpp
//  MMO
//
//  Created by Cole Faust on 1/30/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "ColeTextBox.h"
#include "RenderManager.h"
#include "ColeTexture.h"

ColeTextBox::ColeTextBox(int width)
{
    int height = 20;
    SDL_Surface* bgSurface = RenderManager::getInstance()->createSDLSurface(width, height);
    SDL_Rect rect = {0, 0, width, height};
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 0, 0, 0));
    rect.x++;
    rect.y++;
    rect.w -= 2;
    rect.h -= 2;
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 255, 255, 255));
    ColeTexture *bg = new ColeTexture(bgSurface);
    SDL_FreeSurface(bgSurface);
    addChild(bg);
}