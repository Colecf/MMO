//
//  WorldClient.cpp
//  MMO
//
//  Created by Cole Faust on 6/13/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "WorldClient.h"
#include "ColeTileset.h"

World::World()
{
    for (int i=0; i<WORLDSIZE; i++) {
        for (int j=0; j<WORLDSIZE; j++) {
            tiles[i][j] = 50;
        }
    }
    
    x = y = -1*(WORLDSIZE/2*16);
}

void World::setTile(int x, int y, int tileID)
{
    if (x<0 || x >= WORLDSIZE || y<0 || y >=WORLDSIZE)
    {
        return;
    }
    
    tiles[x][y] = tileID;
}

void World::render()
{
    for (int tilex=0; tilex<WORLDSIZE; tilex++) {
        for (int tiley=0; tiley<WORLDSIZE; tiley++) {
            ColeTileset::loadedSet->renderTile(x+(tilex*16), y+(tiley*16), tiles[tilex][tiley]);
        }
    }
    ColeScene::render();
}