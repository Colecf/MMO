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

ColeScene::ColeScene()
{
    x = y = 0;
    
}

void ColeScene::render()
{
    penX += x;
    penY += y;
    std::list<ColeScene*>::iterator it;
    for (it = children.begin(); it != children.end(); it++)
        (*it)->render();
    penX -= x;
    penY -= y;
}

void ColeScene::addChild(ColeScene* child)
{
    children.push_back(child);
}