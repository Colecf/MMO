//
//  ColeTexture.cpp
//  MMO
//
//  Created by Cole Faust on 12/24/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include "ColeTexture.h"
#include "RenderManager.h"

ColeTexture::ColeTexture()
{
    texture = NULL;
    x = 0;
    y = 0;
    angle = 0;
    fullRect = {0, 0, 0, 0};
}

ColeTexture::ColeTexture(std::string path) : ColeTexture()
{
    texture = RenderManager::getInstance()->loadTexture(path, &width, &height);
    fullRect = {0, 0, width, height};
}
ColeTexture::ColeTexture(SDL_Surface *surface) : ColeTexture()
{
    texture = RenderManager::getInstance()->createTextureFromSurface(surface);
    width = surface->w;
    height = surface->h;
    fullRect = {0, 0, width, height};
}

ColeTexture::~ColeTexture()
{
    SDL_DestroyTexture(texture);
}

void ColeTexture::render()
{
    int tempx = x+ColeScene::penX;
    int tempy = y+ColeScene::penY;
    SDL_Rect dstrect = {tempx, tempy, width, height};
    SDL_RenderCopyEx(RenderManager::getInstance()->renderer, texture, &fullRect, &dstrect, angle, NULL, SDL_FLIP_NONE);
}
void ColeTexture::render(SDL_Rect clip) { render(x, y, clip); }

void ColeTexture::render(int x, int y)
{
    x += ColeScene::penX;
    y += ColeScene::penY;
    SDL_Rect dstrect = {x, y, width, height};
    SDL_RenderCopy(RenderManager::getInstance()->renderer, texture, &fullRect, &dstrect);
}
void ColeTexture::render(int x, int y, SDL_Rect clip)
{
    x += ColeScene::penX;
    y += ColeScene::penY;
    SDL_Rect dstrect = {x, y, clip.w, clip.h};
    SDL_RenderCopy(RenderManager::getInstance()->renderer, texture, &clip, &dstrect);
}

int ColeTexture::getWidth() { return width; }
int ColeTexture::getHeight() { return height; }