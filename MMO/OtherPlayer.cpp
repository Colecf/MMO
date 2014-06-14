//
//  OtherPlayer.cpp
//  MMO
//
//  Created by Cole Faust on 6/9/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "OtherPlayer.h"
#include "ColeFontManager.h"
#include "RenderManager.h"

OtherPlayer::OtherPlayer(std::string theName, int theGameClass)
{
    name = theName;
    gameClass = theGameClass;
    nameTexture = ColeFontManager::getInstance()->createTextTexture(name);
}

void OtherPlayer::render()
{
    ColeScene::render();
    
    int scx = RenderManager::getInstance()->getScaledScreenX()/2-8;
    int scy = RenderManager::getInstance()->getScaledScreenY()/2-8;
    ColeTileset::loadedSet->renderTile(x, y, 190+gameClass);
    nameTexture->render(x, y+10);
}

std::string OtherPlayer::getName(){return name;}
int OtherPlayer::getClass(){return gameClass;}