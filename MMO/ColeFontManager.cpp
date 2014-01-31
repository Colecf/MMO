//
//  ColeFontManager.cpp
//  MMO
//
//  Created by Cole Faust on 1/18/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "ColeFontManager.h"
#include <iostream>
#include "ResourcePath.h"

ColeFontManager::ColeFontManager()
{
    std::string fontname = getResourcePath()+"Vera.ttf";
    font = TTF_OpenFont(fontname.c_str(), 16);
    if (!font)
    {
        std::cout << "Unable to create font for ColeFontManager! " << TTF_GetError() << std::endl;
    }
    style = TTF_STYLE_NORMAL;
    color = {0, 0, 0, 255};
}

ColeTexture* ColeFontManager::createTextTexture(std::string message)
{
    if(!font)
        return NULL;
    SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
    ColeTexture *tex = new ColeTexture(surface);
    SDL_FreeSurface(surface);
    return tex;
}