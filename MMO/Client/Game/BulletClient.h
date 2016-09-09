//
//  BulletClient.h
//  MMO
//
//  Created by Cole Faust on 6/18/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__BulletClient__
#define __MMO__BulletClient__

#include "BulletBase.h"
#include "ColeScene.h"

class BulletClient : public ColeScene, public BulletBase
{
public:
    void update();
    void render();
    void setPos(int newX, int newY);
};

#endif /* defined(__MMO__BulletClient__) */
