//
//  BulletClient.cpp
//  MMO
//
//  Created by Cole Faust on 6/18/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "BulletClient.h"
#include "ColeTileset.h"

void BulletClient::setPos(int newX, int newY)
{
    BulletBase::x = newX;
    BulletBase::y = newY;
    ColeScene::x = newX;
    ColeScene::y = newY;
}

void BulletClient::update()
{
    ColeScene::update();
    BulletBase::update();
    ColeScene::x = BulletBase::x;
    ColeScene::y = BulletBase::y;
}

void BulletClient::render()
{
    ColeTileset::loadedSet->renderTile(BulletBase::x, BulletBase::y, bulletType);
    ColeScene::render();
}