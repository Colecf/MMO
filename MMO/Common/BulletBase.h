//
//  BulletBase.h
//  MMO
//
//  Created by Cole Faust on 6/14/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__BulletBase__
#define __MMO__BulletBase__

#include <iostream>
#ifdef SERVER
#include <memory>
#include "Player.h"
#endif

class BulletBase
{
public:
    BulletBase();
    virtual void update();
    double x, y, angle, speed, ttl;
    int bulletType;
#ifdef CLIENT
    std::string owner;
#else
    std::shared_ptr<Player> owner;
#endif
};

#endif /* defined(__MMO__BulletBase__) */
