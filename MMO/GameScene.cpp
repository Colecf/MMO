//
//  GameScene.cpp
//  MMO
//
//  Created by Cole Faust on 3/8/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "GameScene.h"
#include "RenderManager.h"
#include "NetworkManager.h"
#include "ColeTileset.h"

GameScene::GameScene()
{
    p = NetworkManager::getInstance()->p;
    psx = RenderManager::getInstance()->getScreenX()/2/3;
    psy = RenderManager::getInstance()->getScreenY()/2/3;
}

void GameScene::onEvent(SDL_Event *e)
{
    ColeScene::onEvent(e);
}
void GameScene::render()
{
    ColeScene::render();
    ColeTileset::loadedSet->renderTile(psx, psy, "knight");
}