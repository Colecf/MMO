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
#include "SDL2.h"
#include <memory>

class ColeScene
{
public:
    static std::shared_ptr<ColeScene> currentScene;
    ColeScene();
    virtual void render();
    virtual void onEvent(SDL_Event *e);
    void addChild(std::shared_ptr<ColeScene> child);
    void removeChild(std::shared_ptr<ColeScene> child);
    SDL_Point getAbsoluteCoords();
    int x, y;
    static int penX, penY;
private:
    std::list<std::shared_ptr<ColeScene>> children;
    ColeScene *parent;
};

#endif /* defined(__MMO__ColeScene__) */
