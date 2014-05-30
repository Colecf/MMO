//
//  ColeTileset.h
//  MMO
//
//  Created by Cole Faust on 12/28/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeTileset__
#define __MMO__ColeTileset__

#include <iostream>
#include <map>
#include "ColeTexture.h"

class ColeTileset : public ColeTexture
{
public:
    ColeTileset(std::string path);
    void renderTile(int x, int y, std::string tileName);
    static std::shared_ptr<ColeTileset> loadedSet;
protected:
    std::map<std::string, SDL_Rect> tileNames;
};

#endif /* defined(__MMO__ColeTileset__) */
