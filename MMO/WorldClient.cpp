//
//  WorldClient.cpp
//  MMO
//
//  Created by Cole Faust on 6/13/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "WorldClient.h"
#include "ColeTileset.h"
#include "BulletClient.h"

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
    
    std::list<std::shared_ptr<ColeScene>>::iterator it = children.begin();
    while(it != children.end()) {
        if ((*it)->tag == 1)
        {
            std::shared_ptr<BulletBase> b = std::dynamic_pointer_cast<BulletBase>(*it);
            if (b->ttl <= 0)
            {
                std::cout << "Erasing bullet!" << std::endl;
                it = children.erase(it);
            } else {
                it++;
            }
        } else {
            it++;
        }
    }
    
    ColeScene::render();
}