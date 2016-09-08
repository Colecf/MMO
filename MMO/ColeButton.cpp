//
//  ColeButton.cpp
//  MMO
//
//  Created by Cole Faust on 8/22/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "ColeButton.h"
#include "RenderManager.h"
#include "ColeFontManager.h"
#include "ColeDefines.h"

ColeButton::ColeButton()
{
    depressed = false;
    rect = {0, 0, 0, 0};
}

void ColeButton::setText(std::string text)
{
    removeChild(textTex);
    textTex = ColeFontManager::getInstance()->createTextTexture(text);
    textTex->x = 1;
    textTex->y = 0;
    rect.w = textTex->getWidth()+2;
    rect.h = textTex->getHeight()+1;
    createBackground();
    
    addChild(textTex);
}

void ColeButton::createBackground() {
    SDL_Surface* bgSurface = RenderManager::getInstance()->createSDLSurface(rect.w, rect.h);
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 30, 30, 30));
    rect.x++;
    rect.y++;
    rect.h -= 2;
    rect.w -= 2;
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 100, 100, 100));
    upTex = std::make_shared<ColeTexture>(bgSurface);
    
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 50, 50, 50));
    downTex = std::make_shared<ColeTexture>(bgSurface);
    
    SDL_FreeSurface(bgSurface);
    
    addChild(upTex);
}

void ColeButton::depress()
{
    removeChild(upTex);
    removeChild(downTex);
    removeChild(textTex);
    addChild(downTex);
    addChild(textTex);
    depressed = true;
}
void ColeButton::release()
{
    removeChild(upTex);
    removeChild(downTex);
    removeChild(textTex);
    addChild(upTex);
    addChild(textTex);
    depressed = false;
}

void ColeButton::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
    
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Point coords = getAbsoluteCoords();
        if (e->button.x >= coords.x && e->button.y >= coords.y && e->button.x <= coords.x+rect.w
            && e->button.y <= coords.y+rect.h)
        {
            depress();
        }
    }
    
    if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Point coords = getAbsoluteCoords();
        if (e->button.x >= coords.x && e->button.y >= coords.y && e->button.x <= coords.x+rect.w
            && e->button.y <= coords.y+rect.h && depressed)
        {
            Uint32 myEventType = SDL_RegisterEvents(1); //TODO: Should probably only call this once
            if (myEventType != ((Uint32)-1)) {
                SDL_Event event;
                SDL_zero(event);
                event.type = myEventType;
                event.user.code = BUTTON_PRESSED;
                event.user.data1 = &tag;
                SDL_PushEvent(&event);
            }
        }
        release();
    }
}