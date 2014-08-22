//
//  BulletBase.cpp
//  MMO
//
//  Created by Cole Faust on 6/14/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "BulletBase.h"
#include <math.h>

BulletBase::BulletBase()
{
    x = y = angle = speed = ttl = bulletType = 0;
}

void BulletBase::update()
{
    x += speed*cos(angle);
    y += speed*sin(angle);
    ttl -= speed;
}