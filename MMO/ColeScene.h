//
//  ColeScene.h
//  MMO
//
//  Created by Cole Faust on 1/24/14.
//  Copyright (c) 2014 Cole Faust. All rights reserved.
//

#ifndef __MMO__ColeScene__
#define __MMO__ColeScene__

#include <list>

class ColeScene
{
public:
    ColeScene();
    virtual void render();
    void addChild(ColeScene* child);
    int x, y;
    static int penX, penY;
private:
    std::list<ColeScene*> children;
};

#endif /* defined(__MMO__ColeScene__) */
