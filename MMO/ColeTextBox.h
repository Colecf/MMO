//
//  ColeTextBox.h
//  MMO
//
//  Created by Cole Faust on 1/30/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeTextBox__
#define __MMO__ColeTextBox__

#include <iostream>
#include "ColeScene.h"
#include "ColeTexture.h"

class ColeTextBox : public ColeScene
{
public:
    ColeTextBox(int width);
    std::string containedText;
    virtual void onEvent(SDL_Event *e);
    bool enabled;
    void redisplay();
private:
    int cursorPos;
    bool active;
    SDL_Rect rect;
    std::shared_ptr<ColeTexture> textTexture;
};

#endif /* defined(__MMO__ColeTextBox__) */
