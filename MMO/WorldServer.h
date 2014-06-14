//
//  World.h
//  MMO
//
//  Created by Cole Faust on 6/13/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__World__
#define __MMO__World__

#include <string>
#include "SDL2_net.h"
#include "Player.h"
#define WORLDSIZE 100

class World
{
public:
    void generate();
    void loadFromFile(std::string filename);
    void saveToFile(std::string filename);
    std::string getNetworkMessage();
private:
    int tiles[WORLDSIZE][WORLDSIZE];
};

#endif /* defined(__MMO__World__) */
