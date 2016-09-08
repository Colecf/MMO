//
//  ColeTextBox.cpp
//  MMO
//
//  Created by Cole Faust on 1/30/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "ColeTextBox.h"
#include "RenderManager.h"
#include "ColeFontManager.h"
#include <iostream>

ColeTextBox::ColeTextBox(int width)
{
    enabled = true;
    cursorPos = 0;
    active = false;
    int height = 20;
    SDL_Surface* bgSurface = RenderManager::getInstance()->createSDLSurface(width, height);
    rect = {0, 0, width, height};
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 0, 0, 0));
    rect.x++;
    rect.y++;
    rect.w -= 2;
    rect.h -= 2;
    SDL_FillRect(bgSurface, &rect, SDL_MapRGB(bgSurface->format, 255, 255, 255));
    std::shared_ptr<ColeTexture> bg = std::make_shared<ColeTexture>(bgSurface);
    SDL_FreeSurface(bgSurface);
    addChild(bg);
}

void ColeTextBox::redisplay()
{
    if (containedText.length() > 0)
    {
        removeChild(textTexture);
        textTexture = ColeFontManager::getInstance()->createTextTexture(containedText);
        addChild(textTexture);
        textTexture->x = 1;
        
    } else if (textTexture != NULL)
    {
        removeChild(textTexture);
    }
}

void ColeTextBox::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
    if (!enabled)
    {
        return;
    }
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Point coords = getAbsoluteCoords();
        if (e->button.x >= coords.x && e->button.y >= coords.y && e->button.x <= coords.x+rect.w
            && e->button.y <= coords.y+rect.h && !active)
        {
            active = true;
            SDL_StartTextInput();
            SDL_SetTextInputRect(&rect);
        } else if ((e->button.x < coords.x || e->button.y < coords.y || e->button.x > coords.x+rect.w
                   || e->button.y > coords.y+rect.h) && active)
        {
            active = false;
            SDL_StopTextInput();
        }
    }
    if (e->type == SDL_TEXTINPUT && active)
    {
        containedText += e->edit.text;
        cursorPos++;
        redisplay();
    }
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKSPACE && containedText.length()>0 && active)
    {
        containedText = containedText.substr(0, containedText.length()-1);
        cursorPos--;
        redisplay();
    }
}

std::string ColeTextBox::getContainedText() { return containedText; }
void ColeTextBox::setContainedText(std::string newText)
{
    containedText = newText;
    redisplay();
    redisplay(); //TODO: Sometimes it won't redisplay unless you do it twice
                 // One example is when I try to set it to "Username" as a default
}