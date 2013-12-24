//
//  RenderManager.h
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#ifndef __MMO__RenderManager__
#define __MMO__RenderManager__

#include <iostream>
#include <SDL2/SDL.h>

class RenderManager
{
public:
    SDL_Surface* loadSurface(std::string path);
    void updateScreen();
    void init(SDL_Window* window);
    void cleanup();
    static RenderManager* getInstance()
    {
        static RenderManager* instance;
        if(instance == NULL)
            instance = new RenderManager();
        return instance;
    }
    SDL_Surface *screen;
private:
    RenderManager() {};
    RenderManager(RenderManager const&);  // Don't Implement
    void operator=(RenderManager const&); // Don't implement
    
    SDL_Window *window;
};

#endif /* defined(__MMO__RenderManager__) */
