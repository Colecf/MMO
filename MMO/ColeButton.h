//
//  ColeButton.h
//  MMO
//
//  Created by Cole Faust on 8/22/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeButton__
#define __MMO__ColeButton__

#include <iostream>
#include "ColeScene.h"
#include "ColeTexture.h"

class ColeButton : public ColeScene
{
public:
    ColeButton();
    void setText(std::string text);
    bool depressed;
    virtual void onEvent(SDL_Event *e);
    std::shared_ptr<ColeTexture> textTex;
private:
    void createBackground();
    void depress();
    void release();
    std::shared_ptr<ColeTexture> upTex;
    std::shared_ptr<ColeTexture> downTex;
    SDL_Rect rect;
};
#endif /* defined(__MMO__ColeButton__) */
