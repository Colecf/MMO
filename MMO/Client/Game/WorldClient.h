//
//  WorldClient.h
//  MMO
//
//  Created by Cole Faust on 6/13/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__WorldClient__
#define __MMO__WorldClient__

#include <iostream>
#include <string>
#include "ColeScene.h"

#define WORLDSIZE 100

class World : public ColeScene
{
public:
    World();
    void setTile(int x, int y, int tileID);
    virtual void render();
private:
    int tiles[WORLDSIZE][WORLDSIZE];
};

#endif /* defined(__MMO__WorldClient__) */
