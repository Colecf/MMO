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
#include "OtherPlayer.h"
#include <list>

class GameScene : public ColeScene
{
public:
    GameScene(std::string name, std::shared_ptr<Player> thePlayer);
    virtual void onEvent(SDL_Event *e);
    virtual void render();
private:
    OtherPlayer* getOtherPlayerByName(std::string name);
    int scx, scy; //Screen center x and y
    std::shared_ptr<Player> p;
    std::list<OtherPlayer*> otherPlayers;
};

#endif /* defined(__MMO__GameScene__) */
