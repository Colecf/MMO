//
//  ColeFontManager.h
//  MMO
//
//  Created by Cole Faust on 1/18/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeFontManager__
#define __MMO__ColeFontManager__

#include <string>
#include <SDL2_ttf/SDL_ttf.h>
#include "ColeTexture.h"

class ColeFontManager
{
public:
    ColeTexture* createTextTexture(std::string message);
    static ColeFontManager* getInstance()
    {
        static ColeFontManager* instance;
        if(instance == NULL)
            instance = new ColeFontManager();
        return instance;
    }
private:
    ColeFontManager();
    ColeFontManager(ColeFontManager const&);  // Don't Implement
    void operator=(ColeFontManager const&); // Don't implement
    TTF_Font *font;
    SDL_Color color;
    int style;
};

#endif /* defined(__MMO__ColeFontManager__) */
