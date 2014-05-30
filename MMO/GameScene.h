//
//  GameScene.h
//  MMO
//
//  Created by Cole Faust on 3/8/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__GameScene__
#define __MMO__GameScene__

#include "ColeScene.h"
#include "Player.h"
#include "ColeTexture.h"

class GameScene : public ColeScene
{
public:
    GameScene();
    virtual void onEvent(SDL_Event *e);
    virtual void render();
private:
    int psx, psy; //Player sprite x and y
    std::shared_ptr<Player> p;
};

#endif /* defined(__MMO__GameScene__) */
