//
//  World.cpp
//  MMO
//
//  Created by Cole Faust on 6/13/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#include "WorldServer.h"
#include "StrToInt.h"
#include <stdlib.h>

void World::generate()
{
    for (int x=0; x<WORLDSIZE; x++) {
        for (int y=0; y<WORLDSIZE; y++) {
            tiles[x][y] = 50 + (rand() % 4);
        }
    }
}
void World::loadFromFile(std::string filename)
{
    
}
void World::saveToFile(std::string filename)
{
    
}

std::string World::getNetworkMessage()
{
    std::string message = "world§";
    message += intToStr(WORLDSIZE);
    for (int x=0; x<WORLDSIZE; x++) {
        for (int y=0; y<WORLDSIZE; y++) {
            message += "§"+intToStr(tiles[x][y]);
        }
    }
    message += ";";
    return message;
}