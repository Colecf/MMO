//
//  ColeScene.cpp
//  MMO
//
//  Created by Cole Faust on 1/24/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "ColeScene.h"

int ColeScene::penX;
int ColeScene::penY;
std::shared_ptr<ColeScene> ColeScene::currentScene;

ColeScene::ColeScene()
{
    x = y = tag = 0;
    parent = NULL;
}

void ColeScene::render()
{
    penX += x;
    penY += y;
    std::list<std::shared_ptr<ColeScene>>::iterator it;
    for (it = children.begin(); it != children.end(); it++)
        (*it)->render();
    penX -= x;
    penY -= y;
}

void ColeScene::update()
{
    std::list<std::shared_ptr<ColeScene>>::iterator it;
    for (it = children.begin(); it != children.end(); it++)
        (*it)->update();
}

void ColeScene::onEvent(SDL_Event *e)
{
    std::list<std::shared_ptr<ColeScene>>::iterator it;
    for (it = children.begin(); it != children.end(); it++)
        (*it)->onEvent(e);
}

void ColeScene::addChild(std::shared_ptr<ColeScene> child)
{
    child->parent = this;
    children.push_back(child);
}

void ColeScene::removeChild(std::shared_ptr<ColeScene> child)
{
    children.remove(child);
}

SDL_Point ColeScene::getAbsoluteCoords()
{
    SDL_Point toReturn;
    toReturn.x = 0;
    toReturn.y = 0;
    ColeScene *current = this;
    do
    {
        toReturn.x += current->x;
        toReturn.y += current->y;
        current = current->parent;
    } while (current != NULL);
    
    return toReturn;
}